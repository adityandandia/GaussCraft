import os

import shutil
from fastapi import FastAPI, UploadFile, File, BackgroundTasks, Form
from fastapi.middleware.cors import CORSMiddleware

from pathlib import Path
from fastapi import FastAPI, HTTPException
from fastapi.responses import FileResponse
from fastapi.middleware.cors import CORSMiddleware
import uvicorn
from backend.api_routes import router

app = FastAPI()


# CORS Middleware (Correctly configured)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["GET", "POST", "OPTIONS"],
    allow_headers=["*"],
    expose_headers=["*"]
)


BASE_WORKSPACE = Path("/home/cave/3dapp_workspace_data")

# Mount all routes from api_routes.py under /api, so they resolve at
# /api/ping, /api/upload, /api/jobs/{id}, /api/view/{id}, /api/download/...
# This matches exactly what the Android client's Retrofit service expects.
app.include_router(router, prefix="/api")

# NOTE: the old /upload route that lived here has been removed —
# it duplicated (and conflicted with) the one now in api_routes.py,
# which uses the new job_id dict schema (status/progress/modelUrl)
# instead of the old {job_id, status} shape.


# --- Legacy/diagnostic routes kept as-is, unrelated to the Android contract ---

@app.get("/health")
def health():
    ply_files = []
    for root, dirs, files in os.walk(BASE_WORKSPACE):
        for f in files:
            if f.endswith(".ply"):
                ply_files.append(os.path.join(root, f))
    latest = sorted(ply_files)[-1] if ply_files else None
    return {"status": "ok", "ply_ready": latest is not None, "ply_path": latest}


@app.get("/splat/latest.ply")
def serve_ply():
    ply_files = []
    for root, dirs, files in os.walk(BASE_WORKSPACE):
        for f in files:
            if f.endswith("cleaned_point_cloud.ply"):
                ply_files.append(os.path.join(root, f))
    if not ply_files:
        raise HTTPException(status_code=404, detail="No PLY found. Run pipeline first.")
    latest = sorted(ply_files)[-1]
    return FileResponse(path=latest, media_type="application/octet-stream", filename="latest.ply")


# --- Startup ---
BASE_WORKSPACE = Path("/home/cave/3dapp/workspace")

app.include_router(router)  # router already carries the /api prefix

@app.post("/api/upload_video")
async def upload_video(background_tasks: BackgroundTasks, file: UploadFile = File(...)):
    job_id = str(uuid.uuid4())
    session_dir = BASE_WORKSPACE / job_id
    os.makedirs(session_dir / "images", exist_ok=True)
    video_path = session_dir / "input.mp4"
    with open(video_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)
    background_tasks.add_task(run_pipeline, job_id, video_path, session_dir)
    return {"job_id": job_id, "status": "started"}


if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)
