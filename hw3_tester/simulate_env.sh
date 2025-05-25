#!/usr/bin/env bash
set -e
if [ $# -lt 1 ]; then
  echo "Usage: $0 HW3_<StudentID>.zip"
  exit 1
fi

ZIP="$1"
TMPDIR=$(mktemp -d)
# 1. Unzip submission
unzip "$ZIP" -d "$TMPDIR"

# 2. Compile each question
for src in hw3_q1 hw3_q2 hw3_q3 hw3_q4; do
  cc -std=c99 -Wall -o "$TMPDIR/$src" "$TMPDIR/$src.c"
done

# 3. Run the tests
BASE="$(cd "$(dirname "$0")" && pwd)"
for q in hw3_q1 hw3_q2 hw3_q3 hw3_q4; do
  echo "=== Testing $q ==="
  "$BASE/test_runner.py" "$TMPDIR/$q" "$BASE/tests_all.json" || true
  echo
done
