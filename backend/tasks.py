import subprocess
import os
import shutil
import struct
import numpy as np
from pathlib import Path
import sys

# Open3D for statistical fog removal
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
        print(result.stdout[-3000:])  
    if result.returncode != 0:
        raise RuntimeError(f"Step failed: {command[0]}")

def copy_sparse_txt(dense_dir: Path):
    sparse_src = dense_dir / "sparse"
    sparse_dst = dense_dir / "sparse" / "0"
    os.makedirs(sparse_dst, exist_ok=True)
    for txt_file in sparse_src.glob("*.txt"):
        shutil.copy(txt_file, sparse_dst / txt_file.name)
        
    for required in ["cameras.txt", "images.txt", "points3D.txt"]:
        p = sparse_dst / required
        if not p.exists():
            raise RuntimeError(f"FastGS prerequisite missing: {required}")

# ───────────────────────────────────────────────────────────
# THE RADIAL "CENTER-OF-MASS" CLEANER (Safe for Cables)
# ───────────────────────────────────────────────────────────
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
        
        data = []
        for _ in range(num_vertices):
            raw = f.read(4 * num_props)
            vals = struct.unpack_from(f'{num_props}f', raw)
            data.append(vals)

    data = np.array(data)
    
    x = properties.index('x')
    y = properties.index('y')
    z = properties.index('z')
    o_idx = properties.index('opacity')

    # --- STAGE 1: THE RADIAL CROP (Kill the outer explosion) ---
    print("  [Stage 1] Calculating Center of Mass...")
    xyz = data[:, [x, y, z]]
    
    # Find the median center to ignore extreme outliers
    center = np.median(xyz, axis=0)
    
    # Calculate distance of every point from the center
    distances = np.linalg.norm(xyz - center, axis=1)
    
    # Keep only the inner 75% of the scene (tight bounding sphere around the object)
    # Adjust this to 80 or 85 if it crops the edges of your cable!
    radius_limit = np.percentile(distances, 75) 
    radial_mask = distances < radius_limit
    
    cleaned_data = data[radial_mask]
    print(f"    -> Radial Crop: Deleted {len(data) - len(cleaned_data)} outer background points.")

    # --- STAGE 2: OPACITY (Kill the invisible fog) ---
    print("  [Stage 2] Removing Transparent Fog...")
    raw_opacity = cleaned_data[:, o_idx]
    # Keep points in the top 85% of opacity
    op_threshold = np.percentile(raw_opacity, 15)
    op_mask = raw_opacity > op_threshold
    cleaned_data = cleaned_data[op_mask]
    print(f"    -> Opacity Filter: Deleted {np.sum(~op_mask)} ghost points.")

    # --- STAGE 3: OPEN3D SOR (Kill the sparse floating clouds inside the sphere) ---
    print("  [Stage 3] Open3D Statistical Outlier Removal...")
    xyz_coords = cleaned_data[:, [x, y, z]].astype(np.float64)
    pcd = o3d.geometry.PointCloud()
    pcd.points = o3d.utility.Vector3dVector(xyz_coords)
    
    # nb_neighbors: How many points must be nearby
    # std_ratio: Lower means more aggressive deleting
    pcd_sor, ind_sor = pcd.remove_statistical_outlier(nb_neighbors=40, std_ratio=1.0)
    
    sor_mask = np.zeros(len(cleaned_data), dtype=bool)
    sor_mask[ind_sor] = True
    final_data = cleaned_data[sor_mask]
    print(f"    -> SOR: Deleted {len(cleaned_data) - len(final_data)} isolated floaters.")

    print(f"  [SUCCESS] Preserved {len(final_data)} core object splats out of {num_vertices} original.")

    # Save output
    with open(output_path, "wb") as f:
        for line in header_lines:
            line_str = line.decode('utf-8').strip()
            if line_str.startswith("element vertex"):
                f.write(f"element vertex {len(final_data)}\n".encode('utf-8'))
            else:
                f.write(line)
        for row in final_data:
            f.write(struct.pack(f'{num_props}f', *row))
    print(f"  Saved Pristine Splat to {output_path}")

# ───────────────────────────────────────────────────────────
# PIPELINE EXECUTION
# ───────────────────────────────────────────────────────────
def run_pipeline(job_id: str, video_path: Path, session_dir: Path, jobs: dict):
    try:
        images_dir = session_dir / "images"
        db_path = session_dir / "database.db"
        sparse_dir = session_dir / "sparse"
        dense_dir = session_dir / "dense"
        output_dir = session_dir / "output"

        # Downscale video to help FastGS process it completely
        run_step([
            "ffmpeg", "-i", str(video_path),
            "-qscale:v", "1", 
            "-vf", "fps=6,scale=800:800:force_original_aspect_ratio=decrease",
            str(images_dir / "%04d.jpg")
        ], session_dir)

        # COLMAP BOOST: Double the max_num_features to 16384 to find the black cable
        run_step(["colmap", "feature_extractor",
            "--database_path", str(db_path),
            "--image_path", str(images_dir),
            "--ImageReader.camera_model", "OPENCV",
            "--SiftExtraction.estimate_affine_shape", "1",
            "--SiftExtraction.max_num_features", "16384" 
        ], session_dir)
        
        # Perfect 360 loop closure
        run_step(["colmap", "exhaustive_matcher",
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
        
        # 10k iterations to solidify the downscaled geometry
        run_step([
            "python3", "train.py",
            "-s", str(dense_dir),
            "-m", str(output_dir),
            "--iterations", "10000"
        ], fastgs_dir)

        raw_ply = output_dir / "point_cloud" / "iteration_10000" / "point_cloud.ply"
        cleaned_ply = session_dir / "point_cloud.ply"
        clean_splat(raw_ply, cleaned_ply)

        jobs[job_id] = "done"
        return cleaned_ply

    except Exception as e:
        jobs[job_id] = "failed"
        raise

def run_pipeline_from_images(job_id: str, session_dir: Path, jobs: dict):
    # Identical logic applied here for image uploads
    try:
        images_dir = session_dir / "images"
        db_path = session_dir / "database.db"
        sparse_dir = session_dir / "sparse"
        dense_dir = session_dir / "dense"
        output_dir = session_dir / "output"

        run_step(["colmap", "feature_extractor",
            "--database_path", str(db_path),
            "--image_path", str(images_dir),
            "--ImageReader.camera_model", "OPENCV",
            "--SiftExtraction.estimate_affine_shape", "1",
            "--SiftExtraction.max_num_features", "16384"
        ], session_dir)
        
        run_step(["colmap", "exhaustive_matcher",
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
            "--iterations", "10000"
        ], fastgs_dir)

        raw_ply = output_dir / "point_cloud" / "iteration_10000" / "point_cloud.ply"
        cleaned_ply = session_dir / "point_cloud.ply"
        clean_splat(raw_ply, cleaned_ply)

        jobs[job_id] = "done"
        return cleaned_ply

    except Exception as e:
        jobs[job_id] = "failed"
        raise
