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
Android capture → ffmpeg (frame extraction) → COLMAP (SfM) → FastGS (3D Gaussian Splatting) → custom cleanup (scale/opacity filter + DBSCAN + optional RANSAC) → .ply → Unity GaussianSplatRenderer
```

| Stage | Tool / Library | Version | Purpose |
|---|---|---|---|
| 1. Capture | Android (Unity) | Unity 2022 LTS | Records a short handheld video of the target scene |
| 2. Frame extraction | ffmpeg | — | Extracts frames at `fps=6`, scaled to 800×800 (aspect-preserving) |
| 3. Structure-from-Motion | [COLMAP](https://colmap.github.io/) | 3.9+ | `feature_extractor` → `exhaustive_matcher` → `mapper` → `image_undistorter` to estimate camera poses and build a dense reconstruction from extracted frames |
| 4. Gaussian Splatting | [FastGS](https://github.com/adityandandia/FastGS) (fork, submodule) | pinned commit, CUDA-accelerated | Trains a 3D Gaussian Splat (10,000 iterations) from the COLMAP dense reconstruction |
| 5. Post-processing | Custom cleanup (numpy, scipy, scikit-learn) | — | Filters degenerate/bloated Gaussians by scale, removes floating debris via DBSCAN clustering, and optionally checks geometric consistency against dominant scene planes (RANSAC) |
| 6. Export | Custom exporter | — | Serializes the cleaned scene to `.ply`; optional `.ply → .splat` conversion for external viewers |
| 7. Serving | [FastAPI](https://fastapi.tiangolo.com/) | 0.110+ | Orchestrates steps 2–6 and serves the final `.ply` to the client |
| 8. Rendering | Unity (custom renderer) | Unity 2022 LTS | `GaussianSplatRenderer` loads and displays the `.ply` on-device |

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
  - Runs `ffmpeg` for frame extraction
  - Runs COLMAP for SfM
  - Runs FastGS (Gaussian Splatting) for scene training
  - Runs a custom numpy/scipy/scikit-learn cleanup pass on the raw `.ply` (no Open3D dependency)
  - Serves the final `.ply` back to the app
- **FastGS:** vendored/forked as a submodule, used for the Gaussian Splatting training step

### Cleanup pass detail (`backend/tasks.py::clean_splat`)

The post-processing step is implemented from scratch rather than via Open3D:

1. **Scale filter** — drops Gaussians with degenerate or bloated `scale_0/1/2` values (cheapest check, run first to shrink the working set).
2. **Opacity / intermediate filtering** — additional property-level filtering ahead of the spatial checks.
3. **DBSCAN clustering** — clusters the remaining points spatially and keeps clusters that are at least 0.5% of the largest cluster's size, removing noise points and small floating-debris clusters while preserving legitimate secondary objects in a scene.
4. **RANSAC plane consistency (optional, off by default)** — fits up to 4 dominant planes (floor/wall/table) and can remove points that are both plane-inconsistent and spatially isolated; useful for indoor/planar scenes, skippable for organic ones via `USE_RANSAC = False`.

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
- ffmpeg
- numpy, scipy, scikit-learn (used for cleanup — Open3D is **not** required)
- `numpy<2` (required by FastGS)

- Run setup_and_run.sh, one all-in-one script that does compatibility checking, dependency install, environment setup, and finally runs the server as a receive→process → send loop.

### Backend

```bash
git clone --recurse-submodules https://github.com/adityandandia/3dReConstruct.git
cd 3dReConstruct/backend
pip install -r requirements.txt
uvicorn main:app --reload
```

> **Note (Windows/MSVC):** build FastGS with `-allow-unsupported-compiler`, and ensure the COLMAP source path points to the `dense/` reconstruction folder before training.

> **Note (paths):** `backend/tasks.py` currently hardcodes the FastGS location (`/home/cave/3dapp/FastGS`) and the training interpreter (`/home/cave/miniconda3/envs/fastgs/bin/python`). Update these to match your environment, or parameterize them via config/env vars before running elsewhere.

### Mobile app

Open `3d-scanner-app/` in Unity 2022 LTS, build for Android, and point the app at your backend's endpoint.

## Pipeline notes

- Frames are extracted with `ffmpeg` at `fps=6`, scaled to 800×800 (aspect-preserving), to keep COLMAP within budget on consumer GPUs (tested on 4GB VRAM).
- COLMAP is run with `SiftExtraction.estimate_affine_shape=1` and up to 16,384 features per image, using the `OPENCV` camera model.
- FastGS training runs for 10,000 iterations by default.
- A `.ply` → `.splat` converter is included for compatibility with external splat viewers.
- `run_pipeline_from_images` provides an alternate entry point that skips video/ffmpeg and starts directly from a folder of images, reusing the same COLMAP → FastGS → cleanup chain.
