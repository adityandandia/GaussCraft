# 3dReConstruct

An end-to-end 3D scene reconstruction pipeline that turns a phone video into a viewable Gaussian Splat, rendered natively inside an Android app.

Built as part of ongoing AR/VR + spatial computing work, with an applied use case in 3D crime scene reconstruction.

---

## What this enables

- **Crime scene digitization** — a single phone walkthrough of a scene produces a to-scale 3D reconstruction that investigators can revisit, measure, and view from angles never physically photographed — instead of being limited to a fixed set of 2D photos.
- **Property walkthroughs without dedicated 3D scanning hardware** — a listing agent or homeowner records one video and gets a splat viewable in-app, skipping LiDAR rigs or DSLR photogrammetry rigs.
- **Physical evidence/damage capture for claims** — an accident site or damaged property can be captured once in the field and reviewed later in 3D, rather than relying on adjuster notes and flat photos.
- **Archiving physical installations or artifacts** — a museum exhibit, heritage site, or one-off physical setup can be recorded and preserved as a 3D asset before it's dismantled or degrades.
- **Sourcing real-world 3D assets for AR scenes** — instead of manually modeling an object or room for an AR experience, scan the real one and reconstruct it directly.

## Pipeline

The system takes a single monocular video captured on an Android device and reconstructs it into a viewable 3D Gaussian Splat, rendered natively in-app.

```
Android capture → COLMAP (SfM) → FastGS (3D Gaussian Splatting) → Open3D (cleanup) → .ply → Unity GaussianSplatRenderer
```

| Stage | Tool / Library | Version | Purpose |
|---|---|---|---|
| 1. Capture | Android (Unity) | Unity 2022 LTS | Records a short handheld video of the target scene |
| 2. Structure-from-Motion | [COLMAP](https://colmap.github.io/) | 3.9+ | Estimates camera poses and produces a sparse point cloud from extracted frames |
| 3. Gaussian Splatting | [FastGS](https://github.com/adityandandia/FastGS) (fork, submodule) | pinned commit, CUDA-accelerated | Trains a 3D Gaussian Splat representation from the COLMAP dense reconstruction |
| 4. Post-processing | [Open3D](http://www.open3d.org/) | 0.18+ | Denoises, filters, and cleans the raw splat/point cloud output |
| 5. Export | Custom exporter | — | Serializes the cleaned scene to `.ply`; optional `.ply → .splat` conversion for external viewers |
| 6. Serving | [FastAPI](https://fastapi.tiangolo.com/) | 0.110+ | Orchestrates steps 2–5 and serves the final `.ply` to the client |
| 7. Rendering | Unity (custom renderer) | Unity 2022 LTS | `GaussianSplatRenderer` loads and displays the `.ply` on-device |

**Runtime environment (tested):**
- CUDA 12.6
- PyTorch (cu121 build)
- Python 3.10
- MSVC 14.39 (Windows build of FastGS)
- GPU: NVIDIA RTX 3050, 4GB VRAM

## App in action

| Capture | Processing | Result |
|---|---|---|
| ![Capture screenshot placeholder](docs/images/capture-placeholder.png) | ![Processing screenshot placeholder](docs/images/processing-placeholder.png) | ![Rendered splat screenshot placeholder](docs/images/result-placeholder.png) |

> Replace the placeholder images above with actual screenshots — add them to `docs/images/` as `capture-placeholder.png`, `processing-placeholder.png`, and `result-placeholder.png` (or update the paths/filenames to match).

## Architecture

- **Frontend:** Android app built in Unity
  - Custom PLY loader and point cloud renderer (`PLYLoader.cs`, `PointCloudRenderer.cs`)
  - Custom unlit shader for splat rendering (`PointCloudUnlit.shader`)
  - AR session handling for on-device capture and viewing
- **Backend:** FastAPI service orchestrating the reconstruction pipeline
  - Runs COLMAP for SfM
  - Runs FastGS (Gaussian Splatting) for scene training
  - Runs Open3D for point cloud cleanup
  - Serves the final `.ply` back to the app
- **FastGS:** vendored/forked as a submodule, used for the Gaussian Splatting training step

## Repo structure

```
3dReConstruct/
├── 3d-scanner-app/     # Unity Android app
├── backend/            # FastAPI reconstruction pipeline
├── FastGS/             # Gaussian Splatting submodule
├── outputs/            # generated .ply files (gitignored)
├── uploads/            # incoming capture videos (gitignored)
└── main.py             # pipeline entry point
```

## Setup

### Prerequisites

- Python 3.10
- CUDA 12.6 + compatible NVIDIA driver
- PyTorch (cu121 build)
- MSVC 14.39 (Windows only, required to build FastGS)
- Unity 2022 LTS (for the Android app)
- COLMAP 3.9+
- Open3D 0.18+
- `numpy<2` (required by FastGS)

### Backend

```bash
git clone --recurse-submodules https://github.com/adityandandia/3dReConstruct.git
cd 3dReConstruct/backend
pip install -r requirements.txt
uvicorn main:app --reload
```

> **Note (Windows/MSVC):** build FastGS with `-allow-unsupported-compiler`, and ensure the COLMAP source path points to the `dense/` reconstruction folder before training.

### Mobile app

Open `3d-scanner-app/` in Unity 2022 LTS, build for Android, and point the app at your backend's endpoint.

## Pipeline notes

- Video frames are subsampled aggressively (`fps=1 @ 640px`, keep every 3rd frame) to avoid COLMAP OOM on consumer GPUs (tested on 4GB VRAM).
- A `.ply` → `.splat` converter is included for compatibility with external splat viewers.

## Status

🚧 Actively in development — v1 targets a full capture-to-render loop on Android. Planned next: SAM-based segmentation (v2) and sparse-view reconstruction (v3).
