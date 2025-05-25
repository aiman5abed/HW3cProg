#!/usr/bin/env python3
import sys, os, json, subprocess

def load_manifest(path):
    with open(path, 'r') as f:
        return json.load(f)

def run_test(exe_path, inp_path, out_path):
    with open(inp_path) as f: inp = f.read()
    expected = open(out_path).read()
    proc = subprocess.run([exe_path], input=inp, text=True,stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    actual = proc.stdout
    if actual.strip() == expected.strip():
        return True, ""
    diff = (
        f"--- Expected ({out_path})\n"
        f"+++ Actual   ({exe_path})\n"
        f"- {expected!r}\n+ {actual!r}\n"
    )
    return False, diff

def main():
    if len(sys.argv) != 3:
        print("Usage: test_runner.py <path/to/binary> <tests_all.json>")
        sys.exit(1)

    exe = sys.argv[1]
    manifest = load_manifest(sys.argv[2])
    key = os.path.basename(exe)  # expects keys like 'hw3_q1', etc.

    if key not in manifest:
        print(f"[ERROR] No tests defined for '{key}'")
        sys.exit(1)

    tests = manifest[key]
    passed = 0
    for inp, out in tests:
        ok, diff = run_test(exe, inp, out)
        status = "PASS" if ok else "FAIL"
        print(f"[{status}] {key}: {os.path.basename(inp)}")
        if not ok:
            print(diff)
        else:
            passed += 1

    total = len(tests)
    print(f"\nSummary: {passed}/{total} tests passed for {key}")
    sys.exit(0 if passed == total else 1)

if __name__ == "__main__":
    main()
