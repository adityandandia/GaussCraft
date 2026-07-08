import numpy as np
from plyfile import PlyData
import sys

path = sys.argv[1]
p = PlyData.read(path)
v = p['vertex'].data

xyz = np.stack([v['x'], v['y'], v['z']], axis=1)
opacity = 1 / (1 + np.exp(-v['opacity']))
scale = np.exp(np.stack([v['scale_0'], v['scale_1'], v['scale_2']], axis=1)).mean(axis=1)

centroid = np.median(xyz, axis=0)
dist = np.linalg.norm(xyz - centroid, axis=1)

bins = [0, 2, 4, 6, 8, 10, 12, 15]
for i in range(len(bins)-1):
    mask = (dist >= bins[i]) & (dist < bins[i+1])
    n = mask.sum()
    if n == 0:
        continue
    print(f"dist [{bins[i]:.0f}-{bins[i+1]:.0f}): n={n:5d} ({100*n/len(dist):5.1f}%)  "
          f"opacity mean={opacity[mask].mean():.4f} median={np.median(opacity[mask]):.4f}  "
          f"scale mean={scale[mask].mean():.5f}")

print(f"\nOverall opacity < 0.1: {(opacity < 0.1).sum()} ({100*(opacity<0.1).sum()/len(opacity):.2f}%)")
print(f"Overall opacity < 0.3: {(opacity < 0.3).sum()} ({100*(opacity<0.3).sum()/len(opacity):.2f}%)")

far_mask = dist > 8
print(f"\nPoints with dist > 8: {far_mask.sum()} ({100*far_mask.sum()/len(dist):.2f}%)")
if far_mask.sum() > 0:
    print(f"  of those, opacity < 0.1: {(opacity[far_mask] < 0.1).sum()} ({100*(opacity[far_mask]<0.1).sum()/far_mask.sum():.2f}%)")
    print(f"  of those, opacity < 0.3: {(opacity[far_mask] < 0.3).sum()} ({100*(opacity[far_mask]<0.3).sum()/far_mask.sum():.2f}%)")
