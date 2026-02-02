# Print out the total number of lines of code in .cpp and .hpp files
NUM_LINES_OF_CODE=$(find . \( -path './build' -o -path './external' -o -path './scripts/generated' \) -prune -o -type f \( -name '*.cpp' -o -name '*.hpp' \) -print0 | xargs -0 cat | wc -l)

echo
echo "Total lines of code: $NUM_LINES_OF_CODE"
echo