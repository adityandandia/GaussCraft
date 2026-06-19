import subprocess
import os
import shutil
import struct
import numpy as np
from pathlib import Path
import sys

# Bring Open3D back for aggressive spatial filtering
sys.modules['open3d.ml'] = type(sys)('open3d.ml')
import open3d as o3d

def run_step(command, cwd):
    print(f"\n[RUNNING]: {' '.join(command)}")
    result = subprocess.run(
        command, cwd=cwd,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True
    )
    if result.stdout:
        print(result.stdout[-3000:])  # last 3000 chars to avoid flooding
    if result.returncode != 0:
        raise RuntimeError(f"Step failed: {command[0]}")

def copy_sparse_txt(dense_dir: Path):
    """
    Copy cameras.txt / images.txt / points3D.txt from dense_dir/sparse/
    into dense_dir/sparse/0/ which is where FastGS expects them.
    """
    sparse_src = dense_dir / "sparse"
    sparse_dst = dense_dir / "sparse" / "0"
    os.makedirs(sparse_dst, exist_ok=True)
    for txt_file in sparse_src.glob("*.txt"):
        shutil.copy(txt_file, sparse_dst / txt_file.name)
        print(f"  Copied {txt_file.name} → sparse/0/")
        
    for required in ["cameras.txt", "images.txt", "points3D.txt"]:
        p = sparse_dst / required
        print(f"  {'OK' if p.exists() else 'MISSING'} {required}")
        if not p.exists():
            raise RuntimeError(f"FastGS prerequisite missing: {required}")

def get_clean_indices_open3d(data: np.ndarray, properties: list) -> np.ndarray:
    """Uses Open3D aggressively to find and destroy spatial floaters."""
    x_idx = properties.index('x')
    y_idx = properties.index('y')
    z_idx = properties.index('z')

    xyz = data[:, [x_idx, y_idx, z_idx]].astype(np.float64)

    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(xyz)

    # AGGRESSIVE TWEAK: Lower std_ratio (0.5) and nb_neighbors (20) kills far more floaters
    pcd_sor, ind_sor = pcd.remove_statistical_outlier(nb_neighbors=20, std_ratio=0.5)
    print(f"  [Open3D] Aggressive Spatial Outliers Removed: {len(xyz) - len(ind_sor)}")

    mask = np.zeros(len(data), dtype=bool)
    mask[ind_sor] = True
    return mask

def clean_splat(input_path: Path, output_path: Path):
    print(f"\n[CLEANING SPLAT]: {input_path}")
    with open(input_path, "rb") as f:
        header_lines = []
        while True:
            line = f.readline()
            header_lines.append(line)
            if line.strip() == b"end_header":
                break
        num_vertices = 0
        properties = []
        for line in header_lines:
            line_str = line.decode('utf-8').strip()
            if line_str.startswith("element vertex"):
                num_vertices = int(line_str.split()[-1])
            if line_str.startswith("property float"):
                properties.append(line_str.split()[-1])
        num_props = len(properties)
        print(f"  Loaded {num_vertices} vertices, {num_props} properties")
        data = []
        for _ in range(num_vertices):
            raw = f.read(4 * num_props)
            vals = struct.unpack_from(f'{num_props}f', raw)
            data.append(vals)

    data = np.array(data)

    # ───────────────────────────────────────────────────────────
    # THREE-STAGE AGGRESSIVE FILTER (OPEN3D + OPACITY + SCALE)
    # ───────────────────────────────────────────────────────────
    
    # 1. OPEN3D SPATIAL FILTER (Kills the floating islands)
    mask = get_clean_indices_open3d(data, properties)
    cleaned = data[mask]
    
    # 2. OPACITY FILTER (Kills the fog)
    if 'opacity' in properties:
        op_idx = properties.index('opacity')
        opacities = cleaned[:, op_idx]
        
        # Dynamically drop the bottom 10% (the most transparent points)
        op_threshold = np.percentile(opacities, 10) 
        cleaned = cleaned[opacities > op_threshold]
        print(f"  [Native] After Opacity filter: {len(cleaned)} points kept")

    # 3. SCALE FILTER (Kills the stretched spikes/floaters)
    if all(s in properties for s in ['scale_0', 'scale_1', 'scale_2']):
        s0 = properties.index('scale_0')
        s1 = properties.index('scale_1')
        s2 = properties.index('scale_2')
        
        # Find the maximum scale value for each Gaussian
        max_scales = np.max(cleaned[:, [s0, s1, s2]], axis=1)
        
        # Dynamically drop the top 2% largest splats (the massive spikes)
        scale_threshold = np.percentile(max_scales, 98)
        cleaned = cleaned[max_scales < scale_threshold]
        print(f"  [Native] After Scale filter: {len(cleaned)} points kept")

    with open(output_path, "wb") as f:
        for line in header_lines:
            line_str = line.decode('utf-8').strip()
            if line_str.startswith("element vertex"):
                f.write(f"element vertex {len(cleaned)}\n".encode('utf-8'))
            else:
                f.write(line)
        for row in cleaned:
            f.write(struct.pack(f'{num_props}f', *row))
    print(f"  Saved pristine splat to {output_path}")

def run_pipeline(job_id: str, video_path: Path, session_dir: Path, jobs: dict):
    try:
        images_dir = session_dir / "images"
        db_path = session_dir / "database.db"
        sparse_dir = session_dir / "sparse"
        dense_dir = session_dir / "dense"
        output_dir = session_dir / "output"

        # FIXED: Bumped fps from 2 to 6 so COLMAP doesn't lose tracking
        run_step([
            "ffmpeg", "-i", str(video_path),
            "-qscale:v", "1", "-vf", "fps=6",
            str(images_dir / "%04d.jpg")
        ], session_dir)

        # FIXED: Added --ImageReader.camera_model PINHOLE so FastGS doesn't crash
        run_step(["colmap", "feature_extractor",
            "--database_path", str(db_path),
            "--image_path", str(images_dir),
            "--ImageReader.camera_model", "PINHOLE"
        ], session_dir)
        
        run_step(["colmap", "sequential_matcher",
            "--database_path", str(db_path)
        ], session_dir)
        os.makedirs(sparse_dir / "0", exist_ok=True)
        run_step(["colmap", "mapper",
            "--database_path", str(db_path),
            "--image_path", str(images_dir),
            "--output_path", str(sparse_dir),
            "--Mapper.init_min_num_inliers", "10"
        ], session_dir)
        run_step(["colmap", "model_converter",
            "--input_path", str(sparse_dir / "0"),
            "--output_path", str(sparse_dir / "0"),
            "--output_type", "TXT"
        ], session_dir)

        os.makedirs(dense_dir, exist_ok=True)
        run_step(["colmap", "image_undistorter",
            "--image_path", str(images_dir),
            "--input_path", str(sparse_dir / "0"),
            "--output_path", str(dense_dir),
            "--output_type", "COLMAP"
        ], session_dir)

        run_step(["colmap", "model_converter",
            "--input_path", str(dense_dir / "sparse"),
            "--output_path", str(dense_dir / "sparse"),
            "--output_type", "TXT"
        ], session_dir)

        copy_sparse_txt(dense_dir)

        fastgs_dir = Path("/home/cave/3dapp/FastGS")
        os.makedirs(output_dir, exist_ok=True)
        run_step([
            "python3", "train.py",
            "-s", str(dense_dir),
            "-m", str(output_dir),
            "--iterations", "7000"
        ], fastgs_dir)

        raw_ply = output_dir / "point_cloud" / "iteration_7000" / "point_cloud.ply"
        cleaned_ply = session_dir / "point_cloud.ply"
        clean_splat(raw_ply, cleaned_ply)

        jobs[job_id] = "done"
        print("[DONE] Pipeline finished for " + job_id)
        print("[OUTPUT] Cleaned PLY: " + str(cleaned_ply))
        return cleaned_ply

    except Exception as e:
        jobs[job_id] = "failed"
        print("[FAILED] Pipeline error for " + job_id + ": " + str(e))
        raise

def run_pipeline_from_images(job_id: str, session_dir: Path, jobs: dict):
    try:
        images_dir = session_dir / "images"
        db_path = session_dir / "database.db"
        sparse_dir = session_dir / "sparse"
        dense_dir = session_dir / "dense"
        output_dir = session_dir / "output"

        # FIXED: Added --ImageReader.camera_model PINHOLE here as well
        run_step(["colmap", "feature_extractor",
            "--database_path", str(db_path),
            "--image_path", str(images_dir),
            "--ImageReader.camera_model", "PINHOLE"
        ], session_dir)
        
        run_step(["colmap", "sequential_matcher",
            "--database_path", str(db_path)
        ], session_dir)
        os.makedirs(sparse_dir / "0", exist_ok=True)
        run_step(["colmap", "mapper",
            "--database_path", str(db_path),
            "--image_path", str(images_dir),
            "--output_path", str(sparse_dir),
            "--Mapper.init_min_num_inliers", "10"
        ], session_dir)
        run_step(["colmap", "model_converter",
            "--input_path", str(sparse_dir / "0"),
            "--output_path", str(sparse_dir / "0"),
            "--output_type", "TXT"
        ], session_dir)

        os.makedirs(dense_dir, exist_ok=True)
        run_step(["colmap", "image_undistorter",
            "--image_path", str(images_dir),
            "--input_path", str(sparse_dir / "0"),
            "--output_path", str(dense_dir),
            "--output_type", "COLMAP"
        ], session_dir)

        run_step(["colmap", "model_converter",
            "--input_path", str(dense_dir / "sparse"),
            "--output_path", str(dense_dir / "sparse"),
            "--output_type", "TXT"
        ], session_dir)

        copy_sparse_txt(dense_dir)

        fastgs_dir = Path("/home/cave/3dapp/FastGS")
        os.makedirs(output_dir, exist_ok=True)
        run_step([
            "python3", "train.py",
            "-s", str(dense_dir),
            "-m", str(output_dir),
            "--iterations", "7000"
        ], fastgs_dir)

        raw_ply = output_dir / "point_cloud" / "iteration_7000" / "point_cloud.ply"
        cleaned_ply = session_dir / "point_cloud.ply"
        clean_splat(raw_ply, cleaned_ply)

        jobs[job_id] = "done"
        print("[DONE] Pipeline finished for " + job_id)
        print("[OUTPUT] Cleaned PLY: " + str(cleaned_ply))
        return cleaned_ply

    except Exception as e:
        jobs[job_id] = "failed"
        print("[FAILED] Pipeline error for " + job_id + ": " + str(e))
        raise
