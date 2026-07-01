import numpy as np
import struct

input_path = "/home/cave/3dapp_workspace_data/7f8bf6d6-d3e5-4c74-b265-76117db625ac/output/point_cloud/iteration_7000/point_cloud.ply"
output_path = "/home/cave/3dapp_workspace_data/cleaned_splat.ply"

# Step 1 — read header
with open(input_path, "rb") as f:
    header_lines = []
    while True:
        line = f.readline()
        header_lines.append(line)
        if line.strip() == b"end_header":
            break
    
    # get vertex count and properties
    num_vertices = 0
    properties = []
    for line in header_lines:
        line_str = line.decode('utf-8').strip()
        if line_str.startswith("element vertex"):
            num_vertices = int(line_str.split()[-1])
        if line_str.startswith("property float"):
            properties.append(line_str.split()[-1])
    
    num_props = len(properties)
    print(f"Loaded {num_vertices} vertices with {num_props} properties")
    print(f"Properties: {properties[:6]}...")
    
    # Step 2 — read all data
    data = []
    for _ in range(num_vertices):
        raw = f.read(4 * num_props)
        vals = struct.unpack_from(f'{num_props}f', raw)
        data.append(vals)

data = np.array(data)
print(f"Data shape: {data.shape}")

# Step 3 — get XYZ
x_idx = properties.index('x')
y_idx = properties.index('y')
z_idx = properties.index('z')

xs = data[:, x_idx]
ys = data[:, y_idx]
zs = data[:, z_idx]

# Step 4 — filter outliers (keep within 3 std devs)
cx, cy, cz = xs.mean(), ys.mean(), zs.mean()
sx, sy, sz = xs.std(), ys.std(), zs.std()

mask = (
    (np.abs(xs - cx) < 3 * sx) &
    (np.abs(ys - cy) < 3 * sy) &
    (np.abs(zs - cz) < 3 * sz)
)

cleaned = data[mask]
print(f"After outlier removal: {len(cleaned)} / {num_vertices} points kept")

# Step 5 — filter by opacity (remove invisible gaussians)
if 'opacity' in properties:
    op_idx = properties.index('opacity')
    opacity_mask = cleaned[:, op_idx] > -5.0  # sigmoid(-5) ≈ 0.007
    cleaned = cleaned[opacity_mask]
    print(f"After opacity filter: {len(cleaned)} points")

# Step 6 — write output with full header preserved
with open(output_path, "wb") as f:
    for line in header_lines:
        line_str = line.decode('utf-8').strip()
        if line_str.startswith("element vertex"):
            f.write(f"element vertex {len(cleaned)}\n".encode('utf-8'))
        else:
            f.write(line)
    
    # write binary data
    for row in cleaned:
        f.write(struct.pack(f'{num_props}f', *row))

print(f"Saved to {output_path}")
