"""
backend/cleanup/audit_log.py

Forensic audit trail for the Gaussian Splat cleanup pipeline.

Every stage in clean_splat() removes points via a deterministic rule
(fixed threshold, percentile, cluster-size cutoff, etc.). For evidentiary
use we need a permanent, human-readable record of exactly what was
removed, why, and at what threshold -- not just a console print that
disappears when the process exits.

log_removal() appends one entry per stage to removed_points.json, saved
in the same folder as the cleaned splat output -- i.e. alongside the
.ply the app already keeps for that job -- so a non-technical user can
find the audit trail sitting right next to the reconstruction it
describes.

This module is purely additive: it only RECORDS what a filter already
decided to remove. It never computes a mask, changes a threshold, or
alters cleaned_data in any way.
"""

import json
import datetime
from pathlib import Path

LOG_FILENAME = "removed_points.json"


def _log_path(output_dir: Path) -> Path:
    return Path(output_dir) / LOG_FILENAME


def start_audit_log(output_dir: Path, input_path: Path):
    """
    Call once at the top of clean_splat() to initialize the audit log
    for this run. Overwrites any prior log for the same job with a fresh
    header + empty entry list.
    """
    header = {
        "run_started": datetime.datetime.utcnow().isoformat() + "Z",
        "input_file": str(input_path),
        "entries": [],
    }
    try:
        log_path = _log_path(output_dir)
        log_path.parent.mkdir(parents=True, exist_ok=True)
        with open(log_path, "w") as f:
            json.dump(header, f, indent=2)
    except Exception as e:
        # Audit logging must never break the actual cleanup pipeline.
        print(f"    [audit] WARNING: failed to initialize audit log: {e}")


def log_removal(output_dir: Path, stage: str, reason: str, count: int, threshold=None):
    """
    Appends one audit entry recording a cleanup-stage removal.

    Parameters
    ----------
    output_dir : folder the cleaned splat is written to (log is saved
                 alongside it as removed_points.json)
    stage      : e.g. "Stage 1 - Scale Filter"
    reason     : e.g. "bloated (max axis > 8% of scene extent)"
    count      : number of points removed for this reason
    threshold  : exact numeric threshold used, so the record is
                 reproducible (pass None if not applicable)
    """
    entry = {
        "timestamp": datetime.datetime.utcnow().isoformat() + "Z",
        "stage": stage,
        "reason": reason,
        "points_removed": int(count),
        "threshold": threshold,
    }

    try:
        log_path = _log_path(output_dir)
        log_path.parent.mkdir(parents=True, exist_ok=True)

        if log_path.exists():
            with open(log_path, "r") as f:
                data = json.load(f)
        else:
            data = {"entries": []}

        data["entries"].append(entry)

        with open(log_path, "w") as f:
            json.dump(data, f, indent=2)

        print(f"    [audit] logged: {stage} — removed {count} ({reason}).")
    except Exception as e:
        print(f"    [audit] WARNING: failed to write audit log entry: {e}")
