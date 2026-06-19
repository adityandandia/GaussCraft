from fastapi import APIRouter, UploadFile, File, BackgroundTasks, HTTPException
from fastapi.responses import FileResponse, RedirectResponse
import uuid, shutil, os, zipfile
from pathlib import Path
from backend.tasks import run_pipeline, run_pipeline_from_images

router = APIRouter()
WORKSPACE = Path("/home/cave/3dapp/workspace")
BACKEND_URL = "https://glazing-chaperone-bazooka.ngrok-free.dev"
jobs = {}

@router.post("/upload")
async def upload(background_tasks: BackgroundTasks, file: UploadFile = File(...)):
    job_id = str(uuid.uuid4())
    session_dir = WORKSPACE / job_id
    images_dir = session_dir / "images"
    os.makedirs(images_dir, exist_ok=True)

    # save uploaded file
    upload_path = session_dir / file.filename
    with open(upload_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    # if zip of frames, extract to images_dir
    if file.filename.endswith(".zip"):
        with zipfile.ZipFile(upload_path, 'r') as z:
            z.extractall(images_dir)
        os.remove(upload_path)
        jobs[job_id] = "processing"
        background_tasks.add_task(run_pipeline_from_images, job_id, session_dir, jobs)
    else:
        # treat as video
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

@router.get("/download/{job_id}/ply")
def download_ply(job_id: str):
    if job_id not in jobs:
        raise HTTPException(status_code=404, detail="Job not found")
    if jobs[job_id] != "done":
        raise HTTPException(status_code=400, detail="Job not complete yet")
    ply_path = WORKSPACE / job_id / "point_cloud.ply"
    if not ply_path.exists():
        raise HTTPException(status_code=404, detail="PLY file not found")
    return FileResponse(
        path=str(ply_path),
        media_type="application/octet-stream",
        filename="scene.ply"
    )

@router.get("/view/{job_id}")
def view_splat(job_id: str):
    ply_url = f"{BACKEND_URL}/download/{job_id}/ply"
    redirect_url = f"https://playcanvas.com/supersplat/editor?load={ply_url}"
    return RedirectResponse(url=redirect_url)
