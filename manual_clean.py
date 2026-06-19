python3 - << 'EOF'
import open3d as o3d
import numpy as np
from plyfile import PlyData, PlyElement

input_file = "/home/cave/3dapp/workspace/1ca53e1e-9f70-438a-b8af-832235c57810/output/point_cloud/iteration_30000/point_cloud.py"
output_file = "/home/cave/3dapp/outputs/cleaned.splat"

print(f"Reading {input_file}...")
plydata = PlyData.read(input_file)
vertex_data = plydata.elements[0].data

points = np.vstack((vertex_data['x'], vertex_data['y'], vertex_data['z'])).T
pcd = o3d.geometry.PointCloud()
pcd.points = o3d.utility.Vector3dVector(points)

print("Filtering background noise...")
cl, ind = pcd.remove_statistical_outlier(nb_neighbors=20, std_ratio=2.0)

cleaned_vertex_data = vertex_data[ind]
cleaned_el = PlyElement.describe(cleaned_vertex_data, 'vertex')

print(f"Saving to {output_file}...")
PlyData([cleaned_el]).write(output_file)
print("Complete!")
EOF
