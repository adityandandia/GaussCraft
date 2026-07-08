import numpy as np
from plyfile import PlyData
import sys

path = sys.argv[1]
p = PlyData.read(path)
v = p['vertex'].data

xyz = np.stack([v['x'], v['y'], v['z']], axis=1)
opacity_raw = v['opacity']
opacity = 1 / (1 + np.exp(-opacity_raw))  # sigmoid

centroid = np.median(xyz, axis=0)
dist = np.linalg.norm(xyz - centroid, axis=1)

print(f"Total points: {len(xyz)}")
print(f"Centroid (median): {centroid}")
print(f"Distance from centroid - min: {dist.min():.4f}, max: {dist.max():.4f}, median: {np.median(dist):.4f}, 95th pct: {np.percentile(dist,95):.4f}, 99th pct: {np.percentile(dist,99):.4f}")

far_thresh = np.percentile(dist, 95) * 3
far_mask = dist > far_thresh
print(f"\nPoints beyond {far_thresh:.4f} (3x 95th pct): {far_mask.sum()} ({100*far_mask.sum()/len(xyz):.2f}%)")

if far_mask.sum() > 0:
    print(f"  Opacity of far points - min: {opacity[far_mask].min():.4f}, max: {opacity[far_mask].max():.4f}, mean: {opacity[far_mask].mean():.4f}")
    print(f"  Opacity of near points - min: {opacity[~far_mask].min():.4f}, max: {opacity[~far_mask].max():.4f}, mean: {opacity[~far_mask].mean():.4f}")

    scale_cols = ['scale_0','scale_1','scale_2']
    far_scale = np.exp(np.stack([v[c][far_mask] for c in scale_cols], axis=1))
    near_scale = np.exp(np.stack([v[c][~far_mask] for c in scale_cols], axis=1))
    print(f"  Scale of far points - min: {far_scale.min():.6f}, max: {far_scale.max():.6f}, mean: {far_scale.mean():.6f}")
    print(f"  Scale of near points - min: {near_scale.min():.6f}, max: {near_scale.max():.6f}, mean: {near_scale.mean():.6f}")
