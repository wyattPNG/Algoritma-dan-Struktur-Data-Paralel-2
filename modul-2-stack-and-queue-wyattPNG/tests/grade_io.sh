#!/bin/bash
# grade_io.sh — Run all .in/.out test cases against a compiled binary
# Usage: bash tests/grade_io.sh <binary_path> <test_case_dir>
#
# Exit 0  → all test cases passed
# Exit 1  → one or more failures (or no test cases found)

BINARY="$1"
TEST_DIR="$2"

if [ ! -f "$BINARY" ]; then
    echo "ERROR: Binary '$BINARY' not found. Did compilation succeed?"
    exit 1
fi

PASS=0
TOTAL=0

# Sort so cases run in deterministic order (1.in, 2.in, ...)
for in_file in $(ls "$TEST_DIR"/*.in 2>/dev/null | sort); do
    base="${in_file%.in}"
    out_file="${base}.out"
    case_name="$(basename "$base")"

    if [ ! -f "$out_file" ]; then
        echo "[SKIP] $case_name (no matching .out file)"
        continue
    fi

    TOTAL=$((TOTAL + 1))

    expected="$(cat "$out_file")"
    actual="$(timeout 1.0 "$BINARY" < "$in_file" 2>/dev/null)"
    exit_code=$?

    # Normalize: trim trailing whitespace / newlines for comparison
    expected_norm="$(echo "$expected" | sed 's/[[:space:]]*$//')"
    actual_norm="$(echo "$actual"   | sed 's/[[:space:]]*$//')"

    if [ $exit_code -eq 124 ]; then
        echo "[TLE ] $case_name  (Time Limit Exceeded)"
    elif [ "$actual_norm" = "$expected_norm" ]; then
        echo "[PASS] $case_name"
        PASS=$((PASS + 1))
    else
        echo "[FAIL] $case_name"
        echo "       Expected : $(echo "$expected_norm" | head -1)"
        echo "       Got      : $(echo "$actual_norm"   | head -1)"
    fi
done

echo ""
echo "Result: $PASS / $TOTAL test cases passed"

if [ $TOTAL -eq 0 ]; then
    echo "No test cases found in '$TEST_DIR'."
    exit 1
fi

[ $PASS -eq $TOTAL ] && exit 0 || exit 1
