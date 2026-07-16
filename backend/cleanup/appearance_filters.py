import numpy as np
from pathlib import Path
from backend.cleanup import audit_log


def filter_color_consistency(data: np.ndarray, properties: list, xyz_indices: list,
                              output_path: Path, k: int = 12, std_threshold: float = 2.5) -> np.ndarray:
    """
    Flags Gaussians whose color (SH DC term) deviates sharply from their
    local spatial neighbours' average color — catches color-bleed/ghost
    artifacts that pass geometric filters but look visually wrong.
    Independent of Stages 1-4; safe to run as an optional extra pass.
    """
    from scipy.spatial import cKDTree

    dc_props = [p for p in properties if p.startswith("f_dc_")]
    if len(dc_props) < 3:
        print("  [Color Filter] No f_dc_* SH color properties found — skipping.")
        return data

    print("  [Optional] Color-Consistency Filter...")
    dc_indices = [properties.index(p) for p in dc_props[:3]]
    colors = data[:, dc_indices]
    xyz = data[:, xyz_indices]

    tree = cKDTree(xyz)
    _, neighbor_idx = tree.query(xyz, k=k + 1)  # includes self
    neighbor_idx = neighbor_idx[:, 1:]  # drop self

    neighbor_mean_color = colors[neighbor_idx].mean(axis=1)
    color_dev = np.linalg.norm(colors - neighbor_mean_color, axis=1)

    dev_median = np.median(color_dev)
    dev_std = np.std(color_dev)
    threshold = dev_median + std_threshold * dev_std

    mask = color_dev <= threshold
    cleaned = data[mask]
    removed = int(np.sum(~mask))

    print(f"    -> Removed {removed} color-inconsistent Gaussians (threshold={threshold:.4f}).")
    audit_log.log_removal(
        output_path.parent,
        "Optional - Color Consistency Filter",
        "SH color deviates from local neighbour mean",
        removed,
        threshold=float(threshold)
    )

    return cleaned
   
def filter_rotation_sanity(data: np.ndarray, properties: list, output_path: Path,
                            norm_tolerance: float = 0.15) -> np.ndarray:
    """
    Flags Gaussians with degenerate/invalid rotation quaternions (rot_0..rot_3).
    A valid unit quaternion should have norm ≈ 1; FastGS occasionally emits
    near-zero or wildly unnormalized quaternions on unstable Gaussians.
    Independent check — doesn't touch Stages 1-4.
    """
    rot_props = [p for p in properties if p.startswith("rot_")]
    if len(rot_props) < 4:
        print(f"  [Rotation Filter] WARNING: expected rot_0..rot_3, found {rot_props} — skipping filter, 0 Gaussians removed.")
        return data

    print("  [Optional] Rotation Sanity Filter...")
    rot_indices = [properties.index(p) for p in sorted(rot_props)[:4]]
    quats = data[:, rot_indices]

    norms = np.linalg.norm(quats, axis=1)
    mask = np.abs(norms - 1.0) <= norm_tolerance

    cleaned = data[mask]
    removed = int(np.sum(~mask))

    print(f"    -> Removed {removed} Gaussians with degenerate rotation quaternions "
          f"(|norm-1| > {norm_tolerance}).")
    audit_log.log_removal(
        output_path.parent,
        "Optional - Rotation Sanity Filter",
        "quaternion norm outside tolerance of unit length",
        removed,
        threshold=float(norm_tolerance)
    )

    return cleaned
