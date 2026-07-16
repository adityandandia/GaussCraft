<#
============================================================
 windows_setup.ps1 — 3dReConstruct Windows bootstrap
============================================================
 What this does:
   1. Checks it's running as Administrator (required for WSL install)
   2. Checks/enables WSL2 + installs Ubuntu if missing
   3. Detects your GPU and tells you whether/how to install the
      NVIDIA driver (driver install itself is manual — Windows
      doesn't allow silent unattended NVIDIA driver installs
      safely from a script)
   4. Once WSL+Ubuntu are ready, launches setup_and_run.sh
      *inside* Ubuntu automatically — this is the actual Linux
      script that installs ffmpeg/colmap/Python/FastGS and starts
      the server.

 Usage:
   1. Right-click this file -> "Run with PowerShell"
      (or: open PowerShell as Administrator, then
       powershell -ExecutionPolicy Bypass -File .\windows_setup.ps1)
   2. If it says a reboot is needed, reboot, then run it again —
      it's safe to re-run, every step checks before acting.
============================================================
#>

$ErrorActionPreference = "Stop"

function Write-Ok   { param($msg) Write-Host "[OK]   $msg" -ForegroundColor Green }
function Write-Warn2 { param($msg) Write-Host "[WARN] $msg" -ForegroundColor Yellow }
function Write-Err2  { param($msg) Write-Host "[FAIL] $msg" -ForegroundColor Red }
function Write-Step  { param($msg) Write-Host "`n==> $msg" -ForegroundColor Cyan }

# ============================================================
# STEP 0 — Must run as Administrator
# ============================================================
Write-Step "Checking for Administrator privileges"

$currentPrincipal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
if (-not $currentPrincipal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Err2 "This script must run as Administrator."
    Write-Host "Right-click this file -> 'Run with PowerShell' will usually prompt for this."
    Write-Host "If not, open PowerShell as Administrator manually and re-run:"
    Write-Host "  powershell -ExecutionPolicy Bypass -File `"$PSCommandPath`""
    exit 1
}
Write-Ok "Running as Administrator"

# ============================================================
# STEP 1 — Check / install WSL2 + Ubuntu
# ============================================================
Write-Step "Checking WSL status"

$wslInstalled = $false
try {
    $wslList = wsl -l -v 2>&1
    if ($LASTEXITCODE -eq 0 -and $wslList -match "Ubuntu") {
        Write-Ok "WSL + Ubuntu already installed:"
        Write-Host $wslList
        $wslInstalled = $true
    } else {
        Write-Warn2 "WSL present but Ubuntu distro not found."
    }
} catch {
    Write-Warn2 "WSL not found — will install it now."
}

if (-not $wslInstalled) {
    Write-Step "Installing WSL2 + Ubuntu (this downloads several GB, please wait)"
    wsl --install
    Write-Warn2 "A REBOOT IS LIKELY REQUIRED NOW."
    Write-Warn2 "After rebooting, Ubuntu will open once to ask for a UNIX username/password — set that up, then re-run THIS script."
    $reboot = Read-Host "Reboot now? (y/n)"
    if ($reboot -eq "y") { Restart-Computer }
    exit 0
}

# ============================================================
# STEP 2 — GPU detection (informational + manual driver step)
# ============================================================
Write-Step "Detecting GPU"

$gpus = Get-CimInstance Win32_VideoController | Select-Object -ExpandProperty Name
$nvidiaGpu = $gpus | Where-Object { $_ -match "NVIDIA" }

if ($nvidiaGpu) {
    Write-Ok "NVIDIA GPU detected: $nvidiaGpu"

    $smiOk = $false
    try {
        $smi = wsl -d Ubuntu -- nvidia-smi 2>&1
        if ($LASTEXITCODE -eq 0) { $smiOk = $true }
    } catch {}

    if ($smiOk) {
        Write-Ok "nvidia-smi already works inside WSL — driver is set up correctly."
    } else {
        Write-Warn2 "nvidia-smi did NOT respond inside WSL. Manual step required:"
        Write-Host "  1. Open a browser -> https://www.nvidia.com/drivers"
        Write-Host "  2. Select your GPU ($nvidiaGpu), download and run the installer (Express Install)"
        Write-Host "  3. Reboot Windows"
        Write-Host "  4. Re-run this script"
        Write-Host "(Install the driver on Windows itself — NOT inside Ubuntu. WSL shares it automatically.)"
    }
} else {
    Write-Warn2 "No NVIDIA GPU detected ($($gpus -join ', ')). The FastGS/splatting stage in the pipeline needs CUDA and will not run without one."
    Write-Warn2 "You can still continue — the backend + COLMAP steps will work; setup_and_run.sh will need --force for the rest."
}

# ============================================================
# STEP 3 — Proxy passthrough (optional, only if you use one)
# ============================================================
Write-Step "Proxy check"
Write-Host "If you're on a restrictive network (e.g. campus Wi-Fi) that needs a proxy for internet access,"
Write-Host "set it up manually INSIDE Ubuntu before continuing (see the Windows setup guide, Step 3)."
Write-Host "Skip this if you're on a normal network."

# ============================================================
# STEP 4 — Hand off to setup_and_run.sh inside Ubuntu
# ============================================================
Write-Step "Launching setup_and_run.sh inside Ubuntu"

$runCmd = @'
set -e
mkdir -p ~/3dreconstruct-run
cd ~/3dreconstruct-run
if [ ! -f setup_and_run.sh ]; then
  curl -O https://raw.githubusercontent.com/adityandandia/3dReConstruct/master/setup_and_run.sh
fi
chmod +x setup_and_run.sh
./setup_and_run.sh
'@

Write-Host "Running inside WSL Ubuntu now — this will take a while (installs ffmpeg/colmap/Python/FastGS, then starts the server)."
Write-Host "Watch for [OK]/[WARN]/[FAIL] lines below."
Write-Host ""

wsl -d Ubuntu -- bash -c $runCmd
