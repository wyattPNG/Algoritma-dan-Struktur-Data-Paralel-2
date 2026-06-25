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

if [ ! -d "$TEST_DIR" ]; then
    echo "ERROR: Test directory '$TEST_DIR' not found."
    exit 1
fi

PASS=0
TOTAL=0

# Normalize helper: trim leading/trailing blank lines,
# strip trailing whitespace on each line, collapse \r
normalize() {
    sed 's/\r//' | sed 's/[[:space:]]*$//' | sed '/^$/d'
}

# Sort so cases run in deterministic order (1.in, 2.in, ...)
for in_file in $(ls "$TEST_DIR"/*.in 2>/dev/null | sort -V); do
    base="${in_file%.in}"
    out_file="${base}.out"
    case_name="$(basename "$base")"

    if [ ! -f "$out_file" ]; then
        echo "[SKIP] $case_name (no matching .out file)"
        continue
    fi

    TOTAL=$((TOTAL + 1))

    expected_norm="$(normalize < "$out_file")"
    actual_raw="$(timeout 2.0 "$BINARY" < "$in_file" 2>/dev/null)"
    exit_code=$?
    actual_norm="$(echo "$actual_raw" | normalize)"

    if [ $exit_code -eq 124 ]; then
        echo "[TLE ] $case_name  (Time Limit Exceeded)"
    elif [ "$actual_norm" = "$expected_norm" ]; then
        echo "[PASS] $case_name"
        PASS=$((PASS + 1))
    else
        echo "[FAIL] $case_name"
        echo "       Expected : $(echo "$expected_norm" | head -3)"
        echo "       Got      : $(echo "$actual_norm"   | head -3)"
    fi
done

echo ""
echo "Result: $PASS / $TOTAL test cases passed"

if [ $TOTAL -eq 0 ]; then
    echo "No test cases found in '$TEST_DIR'."
    exit 1
fi

[ $PASS -eq $TOTAL ] && exit 0 || exit 1