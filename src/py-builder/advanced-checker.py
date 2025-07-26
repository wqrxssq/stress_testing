# For users:

# This is custom checker.

# You need to write a custom checker. You should work with input("tests/in.txt"),
# stupid("tests/naiveOut.txt"), smart("tests/smartOut.txt") threads.
# If answers are correct, return 0, else return 1

# Check example for more understanding.

import sys

def solve(input_path, naive_path, smart_path):
    with open(input_path, 'r') as f:
        parts = f.read().split()
        if not parts:
            print("Checker error: input file is empty.", file=sys.stderr)
            return 2
        # original C++ read only `n`
        n = int(parts[0])

    # read expected from naive, testing from smart
    with open(naive_path, 'r') as f:
        naive_ans = f.read().split()
    with open(smart_path, 'r') as f:
        smart_ans = f.read().split()

    if not naive_ans or not smart_ans:
        print("Checker error: output file is empty.", file=sys.stderr)
        return 2

    expected = int(naive_ans[0])
    tested  = int(smart_ans[0])

    if expected == tested:
        return 0
    else:
        return 1

exit_code = solve("tests/in.txt", "tests/naiveOut.txt", "tests/smartOut.txt")
sys.exit(exit_code)
