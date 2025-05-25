#!/usr/bin/env python3
import os
import sys
import json
import subprocess

"""
Test Runner for HW3cProg
- Assumes executables are placed in `hw3_tester/execfiles/` named exactly as keys in tests_all.json (e.g. hw3_q1).
- `tests_all.json` lives alongside this script in `hw3_tester/`.
- I/O paths in the manifest are relative to the repository root.
- Run by simply invoking:
    ./test_runner.py
"""

# Directories
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))       # hw3_tester/
REPO_ROOT  = os.path.dirname(SCRIPT_DIR)                     # repository root
EXEC_DIR   = os.path.join(SCRIPT_DIR, 'execfiles')          # where executables reside

# Load test manifest
MANIFEST_PATH = os.path.join(SCRIPT_DIR, 'tests_all.json')
if not os.path.isfile(MANIFEST_PATH):
    print(f"[ERROR] Cannot find manifest at {MANIFEST_PATH}")
    sys.exit(1)
with open(MANIFEST_PATH, 'r') as f:
    manifest = json.load(f)

all_passed = True

for qname, tests in manifest.items():
    exe_path = os.path.join(EXEC_DIR, qname)
    if not (os.path.isfile(exe_path) and os.access(exe_path, os.X_OK)):
        print(f"[SKIP] {qname}: executable not found or not executable: {exe_path}")
        all_passed = False
        continue

    print(f"=== Testing {qname} ===")
    passed = 0
    total  = len(tests)

    for inp_rel, out_rel in tests:
        inp_path = os.path.join(REPO_ROOT, inp_rel)
        out_path = os.path.join(REPO_ROOT, out_rel)

        # Read files
        try:
            with open(inp_path, 'r') as fi:
                inp_data = fi.read()
            with open(out_path, 'r') as fo:
                expected = fo.read()
        except FileNotFoundError as e:
            print(f"[ERROR] Missing file: {e.filename}")
            all_passed = False
            continue

        # Run executable
        proc = subprocess.run([exe_path], input=inp_data, text=True,
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        actual = proc.stdout

        # Compare results
        if actual.strip() == expected.strip():
            print(f"[PASS] {os.path.basename(inp_path)} -> {os.path.basename(out_path)}")
            passed += 1
        else:
            print(f"[FAIL] {os.path.basename(inp_path)} -> {os.path.basename(out_path)}")
            print('--- Expected:')
            print(expected)
            print('--- Actual:')
            print(actual)
            print()
            all_passed = False

    print(f"{passed}/{total} passed for {qname}\n")

sys.exit(0 if all_passed else 1)
