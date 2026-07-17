# SplatStudio

An end-to-end 3D scene reconstruction pipeline that turns a phone video into a viewable Gaussian Splat.

Built as part of ongoing AR/VR + spatial computing work, with an applied use case in 3D crime scene reconstruction.

---

## What this enables

- **Crime scene digitization** — a single phone walkthrough of a scene produces a to-scale 3D reconstruction that investigators can revisit, measure, and view from angles never physically photographed — instead of being limited to a fixed set of 2D photos.
- **Property walkthroughs without dedicated 3D scanning hardware** — record one video and get a splat, skipping LiDAR rigs or DSLR photogrammetry rigs.
- **Physical evidence/damage capture for claims** — an accident site or damaged property can be captured once in the field and reviewed later in 3D, rather than relying on adjuster notes and flat photos.
- **Archiving physical installations or artifacts** — a museum exhibit, heritage site, or one-off physical setup can be recorded and preserved as a 3D asset before it's dismantled or degrades.
- **Sourcing real-world 3D assets for AR scenes** — instead of manually modeling an object or room for an AR experience, scan the real one and reconstruct it directly.

## Pipeline

The system takes a single monocular video and reconstructs it into a viewable 3D Gaussian Splat.

```
Capture (mobile app) → ffmpeg (frame extraction) → COLMAP (SfM) → FastGS (3D Gaussian Splatting + eval render)
  → cleanup (scale/opacity/radial/DBSCAN filters, audited) → SplatTransform (.sog compression) → served via FastAPI
```

| Stage | Tool / Library | Purpose |
|---|---|---|
| 1. Capture | Mobile app (`mobile/`, React Native) | Records a handheld video of the target scene and uploads it to the backend |
| 2. Frame extraction | ffmpeg | Extracts frames at `fps=3`, scaled to 800×800 (aspect-preserving) |
| 3. Structure-from-Motion | [COLMAP](https://colmap.github.io/) | `feature_extractor` → `sequential_matcher` → `mapper` → `image_undistorter` — camera poses + dense reconstruction. Uses `sequential_matcher` (not exhaustive) since frames come from a continuous video sequence, which is faster on longer captures |
| 4. Gaussian Splatting | [FastGS](https://github.com/adityandandia/FastGS) (fork, submodule) | Trains a 3D Gaussian Splat (10,000 iterations, `--eval`), then runs `render.py` against held-out views to produce PSNR/SSIM quality metrics |
| 5. Post-processing | Custom cleanup (`backend/cleanup/`) | Scale/anisotropy filtering, MAD-adaptive opacity filtering, radial crop, DBSCAN clustering with adaptive (k-distance elbow) `eps`, optional RANSAC plane consistency and color-consistency checks — every removal is written to a per-job audit log |
| 6. Compression | [splat-transform](https://github.com/playcanvas/splat-transform) | Compresses the cleaned `.ply` into the `.sog` format for lighter-weight delivery |
| 7. Serving | [FastAPI](https://fastapi.tiangolo.com/) | Orchestrates steps 2–6, tracks structured per-job status (`colmap` / `fastgs` / `post_processing` / `done` / `failed_colmap` / `failed_fastgs`), and serves the final `.ply` |
| 8. Rendering | SplatStudio (`SplatStudio.apk`) — our own Android viewer app, built in-house | Loads and displays the `.ply`/`.sog` splat on-device |

## Architecture

- **Capture app:** `mobile/` — a React Native app that records video and talks to the backend.
- **Viewer app:** SplatStudio — our own Android app for rendering the resulting splat; its built APK is committed here as `SplatStudio.apk`.
- **Backend:** FastAPI service (`backend/`) orchestrating the reconstruction pipeline:
  - `backend/tasks.py` — pipeline orchestration (ffmpeg → COLMAP → FastGS → cleanup → compression), with per-stage error handling that reports which stage failed (`failed_colmap`, `failed_fastgs`) rather than a single generic failure state.
  - `backend/cleanup/` — modular cleanup package:
    - `statistical_filters.py` — MAD-adaptive opacity filtering (replaces fixed-percentile drops).
    - `appearance_filters.py` — color-consistency filtering using local neighborhood comparison (opt-in via `USE_COLOR_FILTER`).
    - `audit_log.py` — writes a `removed_points.json` per job recording exactly what was removed at each stage and why, alongside the output `.ply`.
  - `backend/colmap_utils.py` — parses COLMAP's `points3D.txt`/`images.txt` for per-point observation/track-length reliability and camera positions.
  - `backend/segmentation.py` — ground-plane removal + DBSCAN-based object isolation, scoring clusters by proximity to the camera path's median position (see note below).
  - `backend/metrics.py` — quality/calibration/reliability metrics: COLMAP reprojection error and track-length reliability, physical scale calibration, PSNR/SSIM/LPIPS against held-out views.
- **FastGS:** vendored/forked as a submodule, used for the Gaussian Splatting training step.

  ## Screenshots

<p align="center">
  <img alt="server" src="https://github.com/user-attachments/assets/a7b1dc54-3bad-4349-922c-f8b09fe8026c" 
  alt="Server page" width="200"/>
  <img alt="recording page" src="https://github.com/user-attachments/assets/885e4b71-de88-4d10-aecb-e0fa1264622a" 
 alt="Recording page" width="200"/>
  <img alt="job card" src="https://github.com/user-attachments/assets/58321a52-0266-46c2-b2f4-3d2f6ea3cf06" 
    alt="Job card / status view" width="200"/>
<img alt="in app splat" src="https://github.com/user-attachments/assets/2a43e1f1-8758-48e9-a674-ad6364b4ca06" 
 alt="In-app splat viewer" width="200"/>
</p>

### On segmentation: DBSCAN-based, not SAM

Object isolation in this project uses classical, dependency-light techniques — RANSAC ground-plane removal + DBSCAN spatial clustering, with clusters selected by proximity to the camera path — rather than a semantic segmentation model (SAM). This avoids the added GPU/dependency footprint and camera-pose/resolution-matching fragility of a learned segmentation approach, at the cost of being a spatial heuristic rather than a semantic one.

> **Status:** `backend/segmentation.py` and the COLMAP-reliability filtering in `backend/colmap_utils.py` are implemented and tested in isolation, but not yet called from `backend/tasks.py`'s pipeline — they're present as modules ready to be wired in, not yet part of a live run. See open items below.

### Cleanup pass detail (`backend/tasks.py::clean_splat`)

1. **Scale + anisotropy filter** — drops Gaussians with degenerate or bloated `scale_0/1/2` values.
2. **Opacity filter (MAD-adaptive)** — drops near-transparent Gaussians using a robust Median Absolute Deviation cutoff rather than a fixed percentage, so the amount removed adapts to how contaminated a given scan actually is.
3. **Radial crop** — trims points beyond the 80th-percentile distance from the scene's median center.
4. **DBSCAN clustering** — adaptive `eps` via the k-distance elbow method (rather than a fixed fraction of scene extent), keeping clusters ≥0.15% of the largest cluster's size.
5. **RANSAC plane consistency** (optional, off by default) and **color-consistency filtering** (optional, off by default) — both available as opt-in stages.

Every removal at every stage is recorded to a per-job `removed_points.json` via `backend/cleanup/audit_log.py`.

## Repo structure

```
SplatStudio/
├── backend/            # FastAPI reconstruction pipeline
│   ├── cleanup/         # modular post-processing filters + audit log
│   ├── colmap_utils.py  # COLMAP reliability/camera-pose parsing
│   ├── segmentation.py  # DBSCAN-based object isolation
│   ├── metrics.py       # quality/calibration/reliability metrics
│   └── tasks.py         # pipeline orchestration
├── mobile/              # Expo/React Native capture app
├── FastGS/              # Gaussian Splatting submodule
├── outputs/, uploads/    # generated/incoming data
├── SplatStudio.apk       # viewer app build
└── main.py               # pipeline entry point
```

## Setup

### Prerequisites

- Python 3.10
- CUDA 12.6 + compatible NVIDIA driver
- PyTorch (cu121 build)
- COLMAP 3.9+
- ffmpeg
- numpy, scipy, scikit-learn (cleanup — Open3D is **not** required)
- `numpy<2` (required by FastGS)
- [`splat-transform`](https://github.com/playcanvas/splat-transform) (for `.sog` compression)

### Backend

```bash
git clone --recurse-submodules https://github.com/adityandandia/SplatStudio.git
cd SplatStudio
chmod +x setup_and_run.sh
./setup_and_run.sh
```

`setup_and_run.sh` handles compatibility checking, dependency installation, and launching the server — see the script itself for details.

> **Note (paths):** `backend/tasks.py` reads `FASTGS_DIR` and `FASTGS_PYTHON` from environment variables (falling back to a default path if unset), so the FastGS location and interpreter are portable across machines rather than hardcoded.

## Pipeline notes

- Frames are extracted with `ffmpeg` at `fps=3`, scaled to 800×800 (aspect-preserving).
- COLMAP uses `sequential_matcher` (frames are a continuous video sequence, not unordered photos), with `SiftExtraction.estimate_affine_shape=1` and up to 16,384 features per image on the `OPENCV` camera model.
- FastGS training runs for 10,000 iterations with `--eval`, followed by a `render.py` pass for quality metrics (PSNR/SSIM), reported per job via `backend/metrics.py`.
- `run_pipeline_from_images` provides an alternate entry point that skips video/ffmpeg and starts directly from a folder of images, reusing the same COLMAP → FastGS → cleanup chain.

Frontend Repo : [SplatStudioApp](https://github.com/adityandandia/SplatStudioApp)

**Open items:**
- Wire `backend/segmentation.py` and COLMAP-reliability filtering into `backend/tasks.py` — both are implemented and tested standalone but not yet called from the live pipeline.
- `outputs/`, `uploads/`, and `mobile/node_modules` are currently tracked in git; these should be gitignored (generated/regenerable content).
- A stale duplicate `tasks.py` exists at the repo root alongside the real `backend/tasks.py` and should be removed.
