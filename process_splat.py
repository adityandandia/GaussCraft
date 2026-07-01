import open3d as o3d
import numpy as np

input_path = "/home/cave/3dapp_workspace_data/7f8bf6d6-d3e5-4c74-b265-76117db625ac/output/point_cloud/iteration_7000/point_cloud.ply"
output_path = "/home/cave/3dapp_workspace_data/cleaned_point_cloud.ply"

print("Loading...")
pcd = o3d.io.read_point_cloud(input_path)
print(f"Original points: {len(pcd.points)}")

# Step 1 — remove outliers
print("Removing outliers...")
pcd, ind = pcd.remove_statistical_outlier(nb_neighbors=20, std_ratio=2.0)
print(f"After outlier removal: {len(pcd.points)}")

# Step 2 — crop to bounding box (keep points within 3 std devs of center)
print("Cropping...")
pts = np.asarray(pcd.points)
center = pts.mean(axis=0)
std = pts.std(axis=0)
mask = np.all(np.abs(pts - center) < 3 * std, axis=1)
pcd = pcd.select_by_index(np.where(mask)[0])
print(f"After crop: {len(pcd.points)}")

# Step 3 — estimate normals
print("Estimating normals...")
pcd.estimate_normals(search_param=o3d.geometry.KDTreeSearchParamHybrid(radius=0.1, max_nn=30))
pcd.orient_normals_consistent_tangent_plane(100)

# Step 4 — save
print("Saving...")
o3d.io.write_point_cloud(output_path, pcd)
print(f"Done! Saved to {output_path}")
