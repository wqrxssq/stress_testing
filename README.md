## Stress Testing

A lightweight shell for **automated stress testing** of two competing solutions on `C++`:

- `naive-solution.cpp` (slow but guaranteed correct)  
- `smart-solution.cpp` (fast, but may contain bugs)

By generating random test cases and comparing outputs, this tool helps you find edge‑case failures in your “smart” implementation, or just check correctness.

---

### Project Structure

You will need to work with these files to run stress-testing.

```markdown

src/cxx_builder
├── naive-solution.cpp         # Correct (but slow) reference solution
├── smart-solution.cpp         # High‑performance solution under test
├── generator.cpp              # User‑provided test‑case generator
└── advanced-cheker.cpp        # (Optional) Custom checker for advanced problems

````

---

### Usage

#### Dependencies

- **CMake** ≥ 3.15  
- **make**  
- **clang++** (with C++20)

#### Build

To build project use in terminal:

```bash
make build
```

#### Basic Mode

Run without a custom checker. Each test’s output is compared for **exact match**:

1) Edit the following files in `src/cxx-builder` (in each file you have a small instuction how to do it):
    - `naive-solution.cpp` - A correct solution that works for any time(even exponent or factorial)
    - `smart-solution.cpp` - A solution that works efficiently, the correctness of which the user is not sure of
    - `generator.cpp` - A generator that generates random short(or not so short, but a naive solution should process it in a reasonable amount of time) tests

2) Run the following command in terminal:

```bash
make start-stress
```

If the stress test detects a wrong answer (WA), you can inspect the failing test case in the `tests` directory—there you’ll find the input file (`in.txt`) and the corresponding outputs (`naiveOut.txt` and `smartOut.txt`) to help you diagnose the issue.

#### Advanced Mode

Use a custom checker (for problems with multiple valid outputs):

1) Exactly the same as in the basic mode

2) Edit `src/cxx-builder/advanced-checker.cpp` - In it you should have files `test.txt`, `smartOut.txt`, `naiveOut.txt` to check the correctness of each, and then compare their results, for more understanding see the original example in `advanced-checker.cpp`.

3) Run the following command in terminal:

```bash
make start-adv-stress
```

#### Other features

Also you can use basic or advanced mode with our files by providing path to them (or only some of them!):

```bash
make start-stress NAIVE=<path/to/naive> SMART=<path/to/smart> GENERATOR=<path/to/generator>
make start-adv-stress NAIVE=<path/to/naive> SMART=<path/to/smart> GENERATOR=<path/to/generator> CHECKER=<path/to/checker>
```

---

### How It Works

1. **Generate** a random test via your `generator`.
2. **Run** both solutions (`naive` and `smart`) on that test.
3. **Compare** outputs:
   - In **basic** mode, do a direct string comparison.
   - In **advanced** mode, invoke your `advanced-checker` to validate the “smart” output.
4. **Report** the first failing test (input + both outputs) and halt.

Loop until a discrepancy is found or a user‑defined iteration limit is reached.

---

### Writing Your Generator

Your generator should read nothing from **stdin** and output **one** random test case per invocation, for example:

```cpp
// generator.cpp (pseudocode)
#include <iostream>
#include <random>

int main() {
    std::mt19937_64 rng(42);
    int n = rng() % 100 + 1;
    std::cout << n << "\n";
    for (size_t i = 0; i < n; ++i)
        std::cout << (rng() % 1000) << ' ';
    std::cout << '\n';
    return 0;
}
```

Happy stress‑testing! 🚀
