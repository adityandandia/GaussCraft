"""
backend/metrics.py

Quality, calibration, and reliability metrics for the Gaussian Splat pipeline.

Covers:
  - COLMAP reprojection error + track-length reliability (from points3D.txt)
  - Physical scale calibration (ArUco marker, triangulated via COLMAP poses)
  - MAD-based adaptive outlier cutoffs (replaces fixed % thresholds)
  - k-distance elbow method for adaptive DBSCAN eps
  - Rotation (quaternion) degeneracy filter
  - Color (SH DC term) local-consistency filter
  - PSNR / SSIM / LPIPS against held-out camera views

Every function is defensive: if an optional dependency or input file is
missing, it returns None / logs a warning instead of raising, so a missing
metric never breaks the pipeline run.
"""

import numpy as np
from pathlib import Path


# ═══════════════════════════════════════════════════════════════
# 1. COLMAP SPARSE MODEL — reprojection error + track length
# ═══════════════════════════════════════════════════════════════

def parse_colmap_points3d(points3d_txt: Path):
    """
    Parses COLMAP's points3D.txt.
    Line format: POINT3D_ID X Y Z R G B ERROR TRACK[](IMAGE_ID, POINT2D_IDX)...
    """
    points = []
    if not points3d_txt.exists():
        print(f"  [metrics] points3D.txt not found at {points3d_txt} — skipping COLMAP stats.")
        return points

    with open(points3d_txt, "r") as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split()
            point_id = int(parts[0])
            xyz = tuple(float(v) for v in parts[1:4])
            error = float(parts[7])
            track_tokens = parts[8:]
            track_length = len(track_tokens) // 2  # (IMAGE_ID, POINT2D_IDX) pairs
            points.append({"id": point_id, "xyz": xyz, "error": error, "track_length": track_length})
    return points


def colmap_reprojection_and_reliability(points3d_txt: Path):
    """
    Returns aggregate reprojection-error + observation-count reliability
    stats, plus the raw per-point list (for tagging individual Gaussians
    later if you want a per-point reliability heatmap in the viewer).
    Returns None if points3D.txt is missing.
    """
    points = parse_colmap_points3d(points3d_txt)
    if not points:
        return None

    errors = np.array([p["error"] for p in points])
    tracks = np.array([p["track_length"] for p in points])

    return {
        "reprojection_error_mean": float(np.mean(errors)),
        "reprojection_error_median": float(np.median(errors)),
        "reprojection_error_p90": float(np.percentile(errors, 90)),
        "num_sparse_points": len(points),
        "track_length_mean": float(np.mean(tracks)),
        "track_length_median": float(np.median(tracks)),
        # % of sparse points seen by fewer than 3 cameras — classic
        # "weakly-observed / uncertain region" flag.
        "low_observation_point_pct": float(100.0 * np.mean(tracks < 3)),
    }


# ═══════════════════════════════════════════════════════════════
# 2. PHYSICAL SCALE CALIBRATION — ArUco marker, triangulated
# ═══════════════════════════════════════════════════════════════

def _quat_to_rotmat(qw, qx, qy, qz):
    n = np.sqrt(qw * qw + qx * qx + qy * qy + qz * qz)
    qw, qx, qy, qz = qw / n, qx / n, qy / n, qz / n
    return np.array([
        [1 - 2 * (qy**2 + qz**2),     2 * (qx * qy - qz * qw),     2 * (qx * qz + qy * qw)],
        [2 * (qx * qy + qz * qw),     1 - 2 * (qx**2 + qz**2),     2 * (qy * qz - qx * qw)],
        [2 * (qx * qz - qy * qw),     2 * (qy * qz + qx * qw),     1 - 2 * (qx**2 + qy**2)],
    ])


def _parse_colmap_cameras(cameras_txt: Path):
    cams = {}
    with open(cameras_txt) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split()
            cam_id = int(parts[0])
            cams[cam_id] = {
                "model": parts[1],
                "width": int(parts[2]),
                "height": int(parts[3]),
                "params": [float(p) for p in parts[4:]],
            }
    return cams


def _parse_colmap_images(images_txt: Path):
    """Returns {image_name: {"R": 3x3, "t": (3,), "camera_id": int}}."""
    images = {}
    with open(images_txt) as f:
        lines = [l.strip() for l in f if l.strip() and not l.strip().startswith("#")]
    for i in range(0, len(lines), 2):  # every 2nd line is POINTS2D — skip it
        parts = lines[i].split()
        qw, qx, qy, qz = (float(v) for v in parts[1:5])
        tx, ty, tz = (float(v) for v in parts[5:8])
        cam_id = int(parts[8])
        name = parts[9]
        images[name] = {"R": _quat_to_rotmat(qw, qx, qy, qz), "t": np.array([tx, ty, tz]), "camera_id": cam_id}
    return images


def _undistort_to_normalized(px, py, cam):
    """Pixel coords -> normalized camera coords, using COLMAP's intrinsics."""
    import cv2
    model, p = cam["model"], cam["params"]
    if model in ("PINHOLE",):
        fx, fy, cx, cy = p[0], p[1], p[2], p[3]
        K = np.array([[fx, 0, cx], [0, fy, cy], [0, 0, 1]])
        dist = np.zeros(4)
    elif model in ("OPENCV",):
        fx, fy, cx, cy, k1, k2, p1, p2 = p[:8]
        K = np.array([[fx, 0, cx], [0, fy, cy], [0, 0, 1]])
        dist = np.array([k1, k2, p1, p2])
    else:
        # SIMPLE_PINHOLE / SIMPLE_RADIAL fallback — treat as pinhole, ignore radial term.
        f, cx, cy = p[0], p[1], p[2]
        K = np.array([[f, 0, cx], [0, f, cy], [0, 0, 1]])
        dist = np.zeros(4)

    pts = np.array([[[px, py]]], dtype=np.float64)
    norm = cv2.undistortPoints(pts, K, dist)
    return float(norm[0, 0, 0]), float(norm[0, 0, 1])


def _triangulate_dlt(proj_matrices, points_norm):
    """Linear DLT triangulation from >=2 views (normalized camera coords)."""
    A = []
    for P, (x, y) in zip(proj_matrices, points_norm):
        A.append(x * P[2] - P[0])
        A.append(y * P[2] - P[1])
    A = np.array(A)
    _, _, VT = np.linalg.svd(A)
    X = VT[-1]
    return X[:3] / X[3]


def estimate_scale_mm_per_unit(images_dir: Path, sparse_txt_dir: Path, marker_length_mm: float = 100.0):
    """
    Detects a printed ArUco marker (DICT_4X4_50, known physical side length
    in mm) across the captured frames, triangulates its 4 corners in COLMAP
    scene units using the recovered camera poses/intrinsics, and returns:

        scale_mm_per_unit = marker_length_mm / reconstructed_side_in_scene_units

    Multiply any COLMAP/FastGS-unit distance by this factor to get mm.
    Returns None (scale stays ambiguous) if no marker is found in >=2 frames
    or if opencv-contrib (cv2.aruco) isn't installed — this is intentional:
    we never fabricate a scale, we only report one we can prove.

    NOTE: place a printed ArUco marker (DICT_4X4_50, ID 0) of known side
    length in view of at least 2 frames during capture. Pass its real
    printed size via `marker_length_mm`.
    """
    try:
        import cv2
    except ImportError:
        print("  [metrics] OpenCV not available — skipping scale calibration.")
        return None
    if not hasattr(cv2, "aruco"):
        print("  [metrics] cv2.aruco unavailable (need opencv-contrib-python) — skipping scale calibration.")
        return None

    cameras_txt = sparse_txt_dir / "cameras.txt"
    images_txt = sparse_txt_dir / "images.txt"
    if not cameras_txt.exists() or not images_txt.exists():
        print("  [metrics] cameras.txt/images.txt missing — skipping scale calibration.")
        return None

    cams = _parse_colmap_cameras(cameras_txt)
    poses = _parse_colmap_images(images_txt)

    aruco_dict = cv2.aruco.getPredefinedDictionary(cv2.aruco.DICT_4X4_50)
    detector = cv2.aruco.ArucoDetector(aruco_dict, cv2.aruco.DetectorParameters())

    # corner_observations[corner_idx] = list of (proj_matrix, (x_norm, y_norm))
    corner_observations = {0: [], 1: [], 2: [], 3: []}

    for img_path in sorted(Path(images_dir).glob("*.jpg")):
        name = img_path.name
        if name not in poses:
            continue
        img = cv2.imread(str(img_path))
        if img is None:
            continue
        corners, ids, _ = detector.detectMarkers(img)
        if ids is None or len(corners) == 0:
            continue

        pose = poses[name]
        cam = cams[pose["camera_id"]]
        P = np.hstack([pose["R"], pose["t"].reshape(3, 1)])  # world->cam extrinsics = normalized-coord proj matrix

        c = corners[0].reshape(4, 2)
        for k in range(4):
            xn, yn = _undistort_to_normalized(c[k][0], c[k][1], cam)
            corner_observations[k].append((P, (xn, yn)))

    if any(len(corner_observations[k]) < 2 for k in range(4)):
        print("  [metrics] Marker seen in fewer than 2 frames for at least one corner — skipping scale calibration.")
        return None

    corners_3d = []
    for k in range(4):
        Ps = [obs[0] for obs in corner_observations[k]]
        pts = [obs[1] for obs in corner_observations[k]]
        corners_3d.append(_triangulate_dlt(Ps, pts))
    corners_3d = np.array(corners_3d)

    side_lengths_units = [np.linalg.norm(corners_3d[i] - corners_3d[(i + 1) % 4]) for i in range(4)]
    reconstructed_side_units = float(np.mean(side_lengths_units))
    if reconstructed_side_units < 1e-9:
        print("  [metrics] Degenerate marker triangulation — skipping scale calibration.")
        return None

    scale_mm_per_unit = marker_length_mm / reconstructed_side_units
    return {
        "scale_mm_per_unit": scale_mm_per_unit,
        "scale_cm_per_unit": scale_mm_per_unit / 10.0,
        "marker_length_mm": marker_length_mm,
        "reconstructed_marker_side_units": reconstructed_side_units,
        "num_frames_used": len(corner_observations[0]),
    }


# ═══════════════════════════════════════════════════════════════
# 3. MAD-BASED ADAPTIVE OUTLIER CUTOFF
# ═══════════════════════════════════════════════════════════════

def mad_zscore_mask(values: np.ndarray, z_thresh: float = 3.5):
    """
    Robust outlier mask via Median Absolute Deviation.
    Modified z-score = 0.6745 * (x - median) / MAD.
    z_thresh=3.5 is the standard Iglewicz & Hoaglin recommendation.
    Returns bool mask: True = keep. Adapts to the data's actual spread
    instead of always dropping a fixed top/bottom percentage.
    """
    values = np.asarray(values, dtype=np.float64)
    median = np.median(values)
    mad = np.median(np.abs(values - median))
    if mad < 1e-12:
        return np.ones(len(values), dtype=bool)  # degenerate spread — nothing is an outlier
    modified_z = 0.6745 * (values - median) / mad
    return np.abs(modified_z) < z_thresh


# ═══════════════════════════════════════════════════════════════
# 4. K-DISTANCE ELBOW — adaptive DBSCAN eps
# ═══════════════════════════════════════════════════════════════

def k_distance_elbow_eps(xyz: np.ndarray, k: int = 15):
    """
    Adaptive DBSCAN eps via the k-distance elbow method (Ester et al. 1996).
    For each point, distance to its k-th nearest neighbour; sort ascending;
    find the point of max curvature (Kneedle-style) — that's the density
    threshold separating dense clusters from sparse noise. Replaces the
    hardcoded 2% * scene_extent constant.
    """
    from scipy.spatial import cKDTree
    tree = cKDTree(xyz)
    dists, _ = tree.query(xyz, k=k + 1)  # +1: includes the point itself at dist 0
    kth_dists = np.sort(dists[:, -1])

    n = len(kth_dists)
    x = np.linspace(0, 1, n)
    y = (kth_dists - kth_dists.min()) / (kth_dists.max() - kth_dists.min() + 1e-12)

    line_vec = np.array([x[-1] - x[0], y[-1] - y[0]])
    line_vec = line_vec / np.linalg.norm(line_vec)
    pts = np.stack([x - x[0], y - y[0]], axis=1)
    proj_len = pts @ line_vec
    proj_pts = np.outer(proj_len, line_vec)
    perp_dist = np.linalg.norm(pts - proj_pts, axis=1)

    elbow_idx = int(np.argmax(perp_dist))
    eps = float(kth_dists[elbow_idx])
    return eps, elbow_idx


# ═══════════════════════════════════════════════════════════════
# 5. ROTATION (quaternion) DEGENERACY FILTER
# ═══════════════════════════════════════════════════════════════

def rotation_degeneracy_mask(rot_data: np.ndarray, z_thresh: float = 3.5):
    """
    Flags Gaussians with degenerate rotation quaternions.
    FastGS stores rot_0..rot_3 as an unnormalized quaternion (w,x,y,z).
    A near-zero-norm quaternion is numerically unstable / an optimizer
    failure — the orientation is meaningless. We MAD-filter on quaternion
    norm as the direct, cheap signal for "wrongly-oriented" points.
    Returns (keep_mask, norms).
    """
    norms = np.linalg.norm(rot_data, axis=1)
    keep_mask = mad_zscore_mask(norms, z_thresh=z_thresh)
    return keep_mask, norms


# ═══════════════════════════════════════════════════════════════
# 6. COLOR (SH DC term) LOCAL CONSISTENCY FILTER
# ═══════════════════════════════════════════════════════════════

def color_consistency_mask(xyz: np.ndarray, sh_dc: np.ndarray, k: int = 12, z_thresh: float = 3.5):
    """
    Flags Gaussians whose base color (SH DC term = view-independent RGB)
    is a local outlier vs. its k nearest spatial neighbours. Real surfaces
    have locally consistent color; a Gaussian with a wildly different color
    than its neighbourhood is usually a reconstruction artifact (color
    bleeding / mis-textured floater). Returns (keep_mask, color_dist).
    """
    from scipy.spatial import cKDTree
    tree = cKDTree(xyz)
    _, idx = tree.query(xyz, k=k + 1)  # includes self at column 0
    neighbour_idx = idx[:, 1:]

    neighbour_mean_color = sh_dc[neighbour_idx].mean(axis=1)
    color_dist = np.linalg.norm(sh_dc - neighbour_mean_color, axis=1)

    keep_mask = mad_zscore_mask(color_dist, z_thresh=z_thresh)
    return keep_mask, color_dist


# ═══════════════════════════════════════════════════════════════
# 7. PSNR / SSIM / LPIPS on held-out camera views
# ═══════════════════════════════════════════════════════════════

def compute_render_quality_metrics(output_dir: Path, iteration: int = 10000):
    """
    Reads rendered-vs-ground-truth image pairs for the held-out test split
    and computes PSNR, SSIM, LPIPS, averaged across the held-out views.

    ASSUMPTION: FastGS follows the same directory convention as the
    original 3D Gaussian Splatting codebase it's derived from, i.e. when
    trained with `--eval` it writes:
        output_dir/test/ours_<iteration>/renders/*.png
        output_dir/test/ours_<iteration>/gt/*.png
    If your FastGS fork uses different paths, adjust `renders_dir`/`gt_dir`
    below accordingly. If the folders don't exist, this returns None
    instead of crashing the pipeline.
    """
    renders_dir = output_dir / "test" / f"ours_{iteration}" / "renders"
    gt_dir = output_dir / "test" / f"ours_{iteration}" / "gt"

    if not renders_dir.exists() or not gt_dir.exists():
        print(f"  [metrics] No held-out test renders found at {renders_dir} — "
              f"PSNR/SSIM/LPIPS skipped. (Requires FastGS run with --eval.)")
        return None

    try:
        import cv2
        from skimage.metrics import structural_similarity as ssim
    except ImportError as e:
        print(f"  [metrics] Missing dependency for render-quality metrics: {e}")
        return None

    lpips_model = None
    try:
        import lpips
        import torch
        lpips_model = lpips.LPIPS(net="vgg")
    except ImportError:
        print("  [metrics] lpips package not installed — PSNR/SSIM will still be computed, LPIPS skipped.")

    render_files = sorted(renders_dir.glob("*.png"))
    if not render_files:
        print(f"  [metrics] No rendered images found in {renders_dir}.")
        return None

    psnr_vals, ssim_vals, lpips_vals = [], [], []

    for render_path in render_files:
        gt_path = gt_dir / render_path.name
        if not gt_path.exists():
            continue

        img_r = cv2.imread(str(render_path)).astype(np.float64) / 255.0
        img_g = cv2.imread(str(gt_path)).astype(np.float64) / 255.0
        if img_r.shape != img_g.shape:
            continue

        mse = np.mean((img_r - img_g) ** 2)
        psnr = 999.0 if mse < 1e-12 else 20 * np.log10(1.0 / np.sqrt(mse))
        psnr_vals.append(psnr)

        ssim_val = ssim(img_r, img_g, channel_axis=2, data_range=1.0)
        ssim_vals.append(ssim_val)

        if lpips_model is not None:
            t_r = torch.from_numpy(img_r).permute(2, 0, 1).unsqueeze(0).float() * 2 - 1
            t_g = torch.from_numpy(img_g).permute(2, 0, 1).unsqueeze(0).float() * 2 - 1
            with torch.no_grad():
                lpips_vals.append(float(lpips_model(t_r, t_g).item()))

    if not psnr_vals:
        print("  [metrics] No matching render/GT pairs found — skipping render-quality metrics.")
        return None

    result = {
        "psnr_mean": float(np.mean(psnr_vals)),
        "ssim_mean": float(np.mean(ssim_vals)),
        "num_held_out_views": len(psnr_vals),
    }
    if lpips_vals:
        result["lpips_mean"] = float(np.mean(lpips_vals))
    else:
        result["lpips_mean"] = None
    return result
