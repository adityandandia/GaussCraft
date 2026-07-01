from fastapi import APIRouter, UploadFile, File, BackgroundTasks, HTTPException
from fastapi.responses import FileResponse, HTMLResponse
import uuid
import shutil
import os
import zipfile
from pathlib import Path
from backend.tasks import run_pipeline, run_pipeline_from_images

router = APIRouter()

# Updated to match the correct path you established earlier
WORKSPACE = Path("/home/cave/3dapp_workspace_data")
BACKEND_URL = "https://glazing-chaperone-bazooka.ngrok-free.dev"
jobs = {}

@router.post("/upload")
async def upload(background_tasks: BackgroundTasks, file: UploadFile = File(...)):
    job_id = str(uuid.uuid4())
    session_dir = WORKSPACE / job_id
    images_dir = session_dir / "images"
    os.makedirs(images_dir, exist_ok=True)

    # Save uploaded file
    upload_path = session_dir / file.filename
    with open(upload_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    # If zip of frames, extract to images_dir
    if file.filename.endswith(".zip"):
        with zipfile.ZipFile(upload_path, 'r') as z:
            z.extractall(images_dir)
        os.remove(upload_path)
        jobs[job_id] = "processing"
        background_tasks.add_task(run_pipeline_from_images, job_id, session_dir, jobs)
    else:
        # Treat as video
        video_path = session_dir / "input.mp4"
        os.rename(upload_path, video_path)
        jobs[job_id] = "processing"
        background_tasks.add_task(run_pipeline, job_id, video_path, session_dir, jobs)

    return {"job_id": job_id}

@router.get("/status/{job_id}")
async def get_status(job_id: str):
    if job_id not in jobs:
        raise HTTPException(status_code=404, detail="Job not found")
    return {"status": jobs[job_id]}

# Download route serving the raw .ply file directly to the Three.js frontend
@router.get("/download/{job_id}/point_cloud.ply")
def download_ply(job_id: str):
    ply_path = WORKSPACE / job_id / "point_cloud.ply"
    
    if not ply_path.exists():
        raise HTTPException(status_code=404, detail="Cleaned point cloud file (.ply) not found")
        
    return FileResponse(
        path=str(ply_path),
        media_type="application/octet-stream",
        filename="point_cloud.ply"
    )

# View route returning the lightweight self-contained Three.js 3D renderer
@router.get("/view/{job_id}", response_class=HTMLResponse)
def view_splat(job_id: str):
    # We use double braces {{ }} for CSS and JS to escape Python's f-string formatting
    html_content = f"""
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
        <title>3D Splat Viewer</title>
        <style>
            body {{ margin: 0; overflow: hidden; background-color: #111; font-family: sans-serif; }}
            #loading {{ position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); color: white; font-size: 18px; }}
        </style>
        
        <script async src="https://unpkg.com/es-module-shims@1.8.0/dist/es-module-shims.js"></script>
        
        <script type="importmap">
        {{
            "imports": {{
                "three": "https://unpkg.com/three@0.157.0/build/three.module.js",
                "@mkkellogg/gaussian-splats-3d": "https://unpkg.com/@mkkellogg/gaussian-splats-3d@0.4.7/build/gaussian-splats-3d.module.js"
            }}
        }}
        </script>
    </head>
    <body>
        <div id="loading">Loading 3D Splat...</div>
        
        <script type="module">
            import * as GaussianSplats3D from '@mkkellogg/gaussian-splats-3d';

            // 1. Initialize the viewer
            const viewer = new GaussianSplats3D.Viewer({{
                'initialCameraPosition': [0, 0, 5],
                'initialCameraLookAt': [0, 0, 0],
                'ignoreDevicePixelRatio': false,
                'sharedMemoryForWorkers': false // <--- SECURITY BYPASS ADDED HERE
            }});

            // 2. Fetch the specific PLY file using the injected job_id
            const jobId = "{job_id}";
            const plyUrl = `/download/${{jobId}}/point_cloud.ply`;
            
            // 3. Load the data using the correct API and start the renderer
            viewer.addSplatScene(plyUrl, {{
                'splatAlphaRemovalThreshold': 5 // Cleans up light fog
            }})
            .then(() => {{
                // Hide loading text when rendering begins
                document.getElementById('loading').style.display = 'none';
                viewer.start();
            }})
            .catch((err) => {{
                document.getElementById('loading').innerText = "Error loading 3D model.";
                console.error(err);
            }});
        </script>
    </body>
    </html>
    """
    return html_content
