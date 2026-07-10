import sys
import importlib.util
from pathlib import Path

def check_submodule(module_name):
    print(f"--- Checking: {module_name} ---")
    spec = importlib.util.find_spec(module_name)
    if spec is None:
        print(f"[FAIL] {module_name} is not installed.")
        return False
    
    try:
        module = importlib.import_module(module_name)
        # Check if the C++ extension (_C) is loadable
        if hasattr(module, '_C'):
            print(f"[OK] {module_name} found and _C extension loaded.")
            return True
        else:
            print(f"[FAIL] {module_name} found, but _C extension is missing/not linked.")
            return False
    except Exception as e:
        print(f"[FAIL] {module_name} failed to load: {e}")
        return False

# List of common FastGS submodules
# Ensure these match the actual package names installed in your environment
submodules = [
    "diff_gaussian_rasterization_fastgs",
    "simple_knn",
]

all_passed = True
for mod in submodules:
    if not check_submodule(mod):
        all_passed = False

if all_passed:
    print("\n[SUMMARY] All submodules are configured correctly. You are ready to train.")
else:
    print("\n[SUMMARY] Some submodules failed. Please re-install them using 'pip install . --no-build-isolation' from their respective directories.")
