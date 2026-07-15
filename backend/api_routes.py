<<<<<<< Updated upstream
from fastapi import FastAPI,APIRouter, UploadFile, File, Form, BackgroundTasks, HTTPException
from fastapi.responses import FileResponse, HTMLResponse
from fastapi.middleware.cors import CORSMiddleware
import uuid
import shutil
import os
import zipfile
import torch
from pathlib import Path
from backend.tasks import run_pipeline, run_pipeline_from_images

router = APIRouter()

# Updated to match the correct path you established earlier
WORKSPACE = Path("/home/cave/3dapp_workspace_data")
=======
from fastapi import APIRouter, UploadFile, File, BackgroundTasks, HTTPException, Form
from fastapi.responses import FileResponse, RedirectResponse
import uuid, shutil, os, zipfile, json
from pathlib import Path
from backend.tasks import run_pipeline, run_pipeline_from_images

router = APIRouter(prefix="/api")

WORKSPACE = Path("/home/cave/3dapp/workspace")
>>>>>>> Stashed changes
BACKEND_URL = "https://glazing-chaperone-bazooka.ngrok-free.dev"

# In-memory job store. Each job is now a dict, not a plain string,
# so we can track title/status/progress/modelUrl per the Android contract.
jobs = {}

<<<<<<< Updated upstream

@router.get("/ping")
async def ping():
    """Heartbeat check polled by the Android client's Config tab."""
    return {
        "status": "healthy",
        "version": "1.1",
        "gpu_available": torch.cuda.is_available()
    }

=======
# ───────────────────────────────────────────────────────────
# NEW: Granular Failure Mappings
# ───────────────────────────────────────────────────────────
FAILURE_REASONS = {
    "failed_ffmpeg": "Video extraction failed. The uploaded file may be corrupted or in an unsupported format.",
    "failed_colmap": "Camera tracking failed (COLMAP). The video likely lacks sufficient texture, overlap, or steady movement for reconstruction.",
    "failed_fastgs": "Scene training failed (FastGS). This is typically caused by memory limits or an empty point cloud from the previous step.",
    "failed_cleanup": "Post-processing failed while attempting to clean noise and floaters from the generated scene."
}

@router.get("/ping")
async def ping():
    return {"message": "pong"}

@router.get("/health")
def health():
    ply_files = []
    for root, dirs, files in os.walk(WORKSPACE):
        for f in files:
            if f.endswith(".ply"):
                ply_files.append(os.path.join(root, f))
    latest = sorted(ply_files)[-1] if ply_files else None
    return {"status": "ok", "ply_ready": latest is not None, "ply_path": latest}

@router.get("/splat/latest.ply")
def serve_ply():
    ply_files = []
    for root, dirs, files in os.walk(WORKSPACE):
        for f in files:
            if f.endswith("cleaned_point_cloud.ply"):
                ply_files.append(os.path.join(root, f))
    if not ply_files:
        raise HTTPException(status_code=404, detail="No PLY found. Run pipeline first.")
    latest = sorted(ply_files)[-1]
    return FileResponse(path=latest, media_type="application/octet-stream", filename="latest.ply")
>>>>>>> Stashed changes

@router.post("/upload")
async def upload(
    background_tasks: BackgroundTasks,
    video: UploadFile = File(...),
<<<<<<< Updated upstream
    title: str = Form(...)
):
    """
    Video/zip ingestion. Field name must be 'video' to match the
    Android Retrofit @Part video: MultipartBody.Part declaration.
    """
=======
    title: str = Form(...),
):
>>>>>>> Stashed changes
    job_id = str(uuid.uuid4())
    session_dir = WORKSPACE / job_id
    images_dir = session_dir / "images"
    os.makedirs(images_dir, exist_ok=True)

<<<<<<< Updated upstream
    # Save uploaded file
    upload_path = session_dir / video.filename
    with open(upload_path, "wb") as buffer:
        shutil.copyfileobj(video.file, buffer)

    # Initialize job record in the shape the Android client expects
    jobs[job_id] = {
        "id": job_id,
        "title": title,
        "status": "colmap",
        "progress": 0,
        "modelUrl": None
    }

    # If zip of frames, extract to images_dir; otherwise treat as video
=======
    upload_path = session_dir / video.filename
    with open(upload_path, "wb") as buffer:
        shutil.copyfileobj(video.file, buffer)

>>>>>>> Stashed changes
    if video.filename.endswith(".zip"):
        with zipfile.ZipFile(upload_path, 'r') as z:
            z.extractall(images_dir)
        os.remove(upload_path)
        background_tasks.add_task(run_pipeline_from_images, job_id, session_dir, jobs)
    else:
        video_path = session_dir / "input.mp4"
        os.rename(upload_path, video_path)
        background_tasks.add_task(run_pipeline, job_id, video_path, session_dir, jobs)

    return {
        "success": True,
        "jobId": job_id,
        "message": "Upload complete. Pipeline scheduled."
    }

<<<<<<< Updated upstream

@router.get("/jobs/{job_id}")
async def get_job(job_id: str):
    if job_id not in jobs:
        raise HTTPException(status_code=404, detail="Job not found")
=======
STAGE_PROGRESS = {
    "processing": 10,
    "colmap": 35,
    "fastgs": 65,
    "post_processing": 85,
    "done": 100,
    "failed": 0,
    "failed_ffmpeg": 0,
    "failed_colmap": 0,
    "failed_fastgs": 0,
    "failed_cleanup": 0,
}

@router.get("/jobs/{job_id}")
async def get_job(job_id: str):
    if job_id not in jobs:
        raise HTTPException(status_code=404, detail="Job not found")
    
    raw_status = jobs[job_id]
    model_url = None
    if raw_status == "done":
        model_url = f"/api/download/{job_id}/ply"
        
    # Mask granular failures as just "failed" for the primary status field 
    # so standard UI logic doesn't break, but include the new granular details.
    display_status = "failed" if raw_status.startswith("failed") else raw_status
        
    response = {
        "job_id": job_id,
        "status": display_status,
        "progress": STAGE_PROGRESS.get(raw_status, 10),
        "model_url": model_url,
    }

    # Inject granular error details if applicable
    if raw_status.startswith("failed"):
        response["error_stage"] = raw_status
        response["error_message"] = FAILURE_REASONS.get(raw_status, "An unknown error occurred during pipeline execution.")

    return response

@router.get("/jobs")
async def get_all_jobs():
    response_list = []
    for jid, raw_status in jobs.items():
        display_status = "failed" if raw_status.startswith("failed") else raw_status
        job_data = {
            "job_id": jid,
            "status": display_status,
            "progress": STAGE_PROGRESS.get(raw_status, 10),
            "model_url": f"/api/download/{jid}/ply" if raw_status == "done" else None,
        }
        
        if raw_status.startswith("failed"):
            job_data["error_stage"] = raw_status
            job_data["error_message"] = FAILURE_REASONS.get(raw_status, "An unknown error occurred during pipeline execution.")
            
        response_list.append(job_data)
        
    return response_list

@router.get("/audit/{job_id}")
def get_audit_log(job_id: str):
    if job_id not in jobs:
        raise HTTPException(status_code=404, detail="Job not found")
    log_path = WORKSPACE / job_id / "removed_points.json"
    if not log_path.exists():
        raise HTTPException(status_code=404, detail="Audit log not found — job may still be processing.")
    with open(log_path, "r") as f:
        return json.load(f)
>>>>>>> Stashed changes

    job = jobs[job_id]

    if job.get("status") == "done" and not job.get("modelUrl"):
        job["modelUrl"] = f"/api/download/{job_id}/point_cloud.ply"

    return job


# Kept for backwards compatibility with anything still calling the old route.
# Not used by the new Android client, safe to remove once fully migrated.
@router.get("/status/{job_id}")
async def get_status_legacy(job_id: str):
    if job_id not in jobs:
        raise HTTPException(status_code=404, detail="Job not found")
    return {"status": jobs[job_id].get("status")}


# Download route serving the raw .ply file directly to the Three.js frontend
@router.get("/download/{job_id}/point_cloud.ply")
def download_ply(job_id: str):
    ply_path = WORKSPACE / job_id / "point_cloud.ply"

    if not ply_path.exists():
        raise HTTPException(status_code=404, detail="Cleaned point cloud file (.ply) not found")

    return FileResponse(
        path=str(ply_path),
        media_type="application/octet-stream",
        headers={"Content-Disposition": "inline"}
    )


# View route returning the lightweight self-contained Three.js 3D renderer.
# This is what gets exposed as `modelUrl` once a job is done.
@router.get("/view/{job_id}", response_class=HTMLResponse)
def view_splat(job_id: str):
<<<<<<< Updated upstream
    html_content = f"""
    <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0">
    <title>3D Splat Viewer</title>
    <style>
        body, html { 
            margin: 0; 
            padding: 0;
            width: 100%;
            height: 100%;
            overflow: hidden; 
            background-color: #111; 
            font-family: monospace; 
        }
        #canvas-container {
            width: 100%;
            height: 100%;
            position: absolute;
            top: 0;
            left: 0;
            z-index: 1;
        }
        #loading { 
            position: absolute; 
            top: 50%; 
            left: 50%; 
            transform: translate(-50%, -50%); 
            color: white; 
            font-size: 14px; 
            max-width: 90%; 
            word-break: break-all; 
            text-align: center; 
            z-index: 10;
        }
    </style>

    <script async src="https://unpkg.com/es-module-shims@1.8.0/dist/es-module-shims.js"></script>

    <script type="importmap">
    {
        "imports": {
            "three": "https://unpkg.com/three@0.157.0/build/three.module.js",
            "@mkkellogg/gaussian-splats-3d": "https://unpkg.com/@mkkellogg/gaussian-splats-3d@0.4.7/build/gaussian-splats-3d.module.js"
        }
    }
    </script>
</head>
<body>
    <div id="loading">Initializing 3D Splat Engine...</div>
    <div id="canvas-container"></div>

    <script type="module">
        // Injected by your server template engine
        const jobId = "{job_id}";
        const plyUrl = `/api/download/${jobId}/point_cloud.ply?ngrok-skip-browser-warning=true`;
        const loadingEl = document.getElementById('loading');

        function showError(label, err) {
            loadingEl.innerText = label + ": " + (err && err.message ? err.message : String(err));
            loadingEl.style.color = "#ff6b6b";
        }

        // Dynamically load the library and initialize immediately to avoid double fetching files
        import('@mkkellogg/gaussian-splats-3d')
            .then(GaussianSplats3D => {
                try {
                    const viewer = new GaussianSplats3D.Viewer({
                        'container': document.getElementById('canvas-container'),
                        'initialCameraPosition': [0, 0, 5],
                        'initialCameraLookAt': [0, 0, 0],
                        'ignoreDevicePixelRatio': false,
                        'sharedMemoryForWorkers': false, // Vital for Android WebView compatibility
                        'selfClosed': true
                    });

                    loadingEl.innerText = "Downloading and processing 3D data...";

                    // The library handles fetching natively in a single continuous stream
                    viewer.addSplatScene(plyUrl, {
                        'splatAlphaRemovalThreshold': 5,
                        'showLoadingUI': false
                    })
                    .then(() => {
                        loadingEl.style.display = 'none';
                        viewer.start();
                    })
                    .catch(err => showError("Viewer load error", err));

                    window.addEventListener('resize', () => {
                        viewer.resize();
                    });

                } catch (err) {
                    showError("Viewer init error", err);
                }
            })
            .catch(err => showError("Module import error", err));
    </script>
</body>
</html>
    """
    return html_content
=======
    ply_url = f"{BACKEND_URL}/api/download/{job_id}/ply"
    redirect_url = f"https://playcanvas.com/supersplat/editor?load={ply_url}"
    return RedirectResponse(url=redirect_url)
>>>>>>> Stashed changes
