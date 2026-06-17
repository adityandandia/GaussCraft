import subprocess
import os
import struct
import numpy as np
from pathlib import Path

def run_step(command, cwd):
    print(f"\n[RUNNING]: {' '.join(command)}")
    result = subprocess.run(command, cwd=cwd, stdout=None, stderr=subprocess.STDOUT)
    if result.returncode != 0:
        raise RuntimeError(f"Step failed: {command[0]}")

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
    x_idx, y_idx, z_idx = properties.index('x'), properties.index('y'), properties.index('z')
    xs, ys, zs = data[:, x_idx], data[:, y_idx], data[:, z_idx]
    cx, cy, cz = xs.mean(), ys.mean(), zs.mean()
    sx, sy, sz = xs.std(), ys.std(), zs.std()
    mask = (
        (np.abs(xs - cx) < 3 * sx) &
        (np.abs(ys - cy) < 3 * sy) &
        (np.abs(zs - cz) < 3 * sz)
    )
    cleaned = data[mask]
    print(f"  After outlier removal: {len(cleaned)} / {num_vertices} kept")
    if 'opacity' in properties:
        op_idx = properties.index('opacity')
        cleaned = cleaned[cleaned[:, op_idx] > -5.0]
        print(f"  After opacity filter: {len(cleaned)} points")
    with open(output_path, "wb") as f:
        for line in header_lines:
            line_str = line.decode('utf-8').strip()
            if line_str.startswith("element vertex"):
                f.write(f"element vertex {len(cleaned)}\n".encode('utf-8'))
            else:
                f.write(line)
        for row in cleaned:
            f.write(struct.pack(f'{num_props}f', *row))
    print(f"  Saved cleaned splat to {output_path}")

def run_pipeline(job_id: str, video_path: Path, session_dir: Path, jobs: dict):
    try:
        images_dir = session_dir / "images"
        db_path = session_dir / "database.db"
        sparse_dir = session_dir / "sparse"
        output_dir = session_dir / "output"

        # 1. FFmpeg
        run_step([
            "ffmpeg", "-i", str(video_path),
            "-qscale:v", "1", "-vf", "fps=2",
            str(images_dir / "%04d.jpg")
        ], session_dir)

        # 2. COLMAP
        run_step(["colmap", "feature_extractor",
            "--database_path", str(db_path),
            "--image_path", str(images_dir)
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

        # 3. FastGS
        fastgs_dir = Path("/home/cave/3dapp/FastGS")
        os.makedirs(output_dir, exist_ok=True)
        run_step([
            "python", "train.py",
            "-s", str(session_dir),
            "-m", str(output_dir),
            "--iterations", "7000"
        ], fastgs_dir)

        # 4. Clean splat
        raw_ply = output_dir / "point_cloud" / "iteration_7000" / "point_cloud.ply"
        cleaned_ply = session_dir / "point_cloud.ply"
        clean_splat(raw_ply, cleaned_ply)

        # 5. Mark done
        jobs[job_id] = "done"
        print(f"\n[DONE] Pipeline finished for {job_id}")
        print(f"[OUTPUT] Cleaned PLY: {cleaned_ply}")
        return cleaned_ply

    except Exception as e:
        jobs[job_id] = "failed"
        print(f"\n[FAILED] Pipeline error for {job_id}: {e}")
        raise
