import numpy as np
from pathlib import Path
from backend.cleanup import audit_log


def filter_opacity_mad(data: np.ndarray, opacity_index: int, output_path: Path, z_threshold: float = -3.0) -> np.ndarray:
    """
    Filters Gaussian opacities using a robust MAD (Median Absolute Deviation) threshold.
    Replaces fixed-percentile blind drops.
    """
    print("  [Stage 2] Opacity Filter (MAD Adaptive)...")

    raw_opacity = data[:, opacity_index]
    # FastGS outputs raw pre-activation opacities; convert via sigmoid to [0, 1] space
    opacity_sigmoid = 1.0 / (1.0 + np.exp(-raw_opacity))

    median_op = np.median(opacity_sigmoid)
    mad = np.median(np.abs(opacity_sigmoid - median_op))

    # Guard against a zero MAD value in perfectly uniform distributions
    if mad == 0:
        mad = 1e-6

    # Standard modified Z-score scaling factor (0.6745)
    modified_z_scores = 0.6745 * (opacity_sigmoid - median_op) / mad

    # Retain elements that do not fall into the extreme left-tail outlier zone
    op_mask = modified_z_scores > z_threshold

    cleaned_data = data[op_mask]
    removed_count = int(np.sum(~op_mask))

    print(f"    -> Removed {removed_count} transparent Gaussians (Modified Z-Score < {z_threshold}).")

    audit_log.log_removal(
        output_path.parent,
        "Stage 2 - Opacity Filter",
        "opacity MAD outlier (left-tail)",
        removed_count,
        threshold=float(z_threshold)
    )

    return cleaned_data
