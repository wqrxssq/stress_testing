## Stress Testing

A lightweight shell for **automated stress testing** of two competing solutions on `C++` or `Python` (using * for cpp or py):

- `naive-solution.*` (slow but guaranteed correct)  
- `smart-solution.*` (fast, but may contain bugs)

By generating random test cases and comparing outputs, this tool helps you find edge‑case failures in your “smart” implementation, or just check correctness.

---

### Project Structure

You will need to work with these files to run stress-testing.

```markdown

src/*-runner
├── naive-solution.*         # Correct (but slow) reference solution
├── smart-solution.*         # High‑performance solution under test
├── generator.*              # User‑provided test‑case generator
└── advanced-cheker.*        # (Optional) Custom checker for advanced problems

````

---

### Usage

#### Dependencies

- **CMake** ≥ 3.15  
- **make**  
- **clang** (with C++20)
- **python3** (if you want to test **py** solutions)

#### Build

To build project use in terminal:

```bash
make build
```

#### Basic Mode

Run without a custom checker. Each test’s output is compared for **exact match**:

1) Edit the following files in `src/*-runner` (in each file you have a small instuction how to do it):
    - `naive-solution.*` - A correct solution that works for any time(even exponent or factorial)
    - `smart-solution.*` - A solution that works efficiently, the correctness of which the user is not sure of
    - `generator.*` - A generator that generates random short (or not so short, but a naive solution should process it in a reasonable amount of time) tests

2) Run the following command in terminal:

```bash
make start-stress
```

If the stress test detects a wrong answer (WA), you can inspect the failing test case in the `tests` directory—there you’ll find the input file (`in.txt`) and the corresponding outputs (`naiveOut.txt` and `smartOut.txt`) to help you diagnose the issue.

**WARNING**: by default it uses cpp files, so if you want to use another lang use `RUN_LANG`:

```bash
make start-stress RUN_LANG=py
```

#### Advanced Mode

Use a custom checker (for problems with multiple valid outputs):

1) Exactly the same as in the basic mode

2) Edit `src/*-runner/advanced-checker.*` - In it you should have files `test.txt`, `smartOut.txt`, `naiveOut.txt` to check the correctness of each, and then compare their results, for more understanding see the original example in `advanced-checker.*`.

3) Run the following command in terminal:

```bash
make start-adv-stress
```

**WARNING**: by default it uses cpp files, so if you want to use another lang use `RUN_LANG`:

```bash
make start-adv-stress RUN_LANG=py
```

#### Other features

Also you can use basic or advanced mode with our files by providing path to them (or only some of them!) and even use different languages:

```bash
make start-stress NAIVE=<path/to/naive> SMART=<path/to/smart> GENERATOR=<path/to/generator>
make start-adv-stress NAIVE=<path/to/naive> SMART=<path/to/smart> GENERATOR=<path/to/generator> CHECKER=<path/to/checker>
```

For example(use python and c++ files both!):

```bash
make start-adv-stress NAIVE=src/cpp-runner/naive-solution.cpp SMART=src/py-runner/smart-solution.py CHECKER=src/py-runner/advanced-checker.py
```

### Example

There is example for writing `generator`, `naive`, `smart`, `advanced-checker` and even example task. Check example codes in `src/*-runner/` and given example problem [here](example_task.md)

---

### How It Works

1. **Generate** a random test via your `generator`.
2. **Run** both solutions (`naive` and `smart`) on that test.
3. **Compare** outputs:
   - In **basic** mode, do a direct string comparison.
   - In **advanced** mode, invoke your `advanced-checker` to validate the “smart” output.
4. **Report** the first failing test (input + both outputs) and halt.

Loop until a discrepancy is found or a user‑defined iteration limit is reached.

Happy stress‑testing! 🚀
