## Stress Testing

A lightweight shell for **automated stress testing** of two competing solutions on `C++`:

- `NaiveSolution.cpp` (slow but guaranteed correct)  
- `SmartSolution.cpp` (fast, but may contain bugs)

By generating random test cases and comparing outputs, this tool helps you find edge‑case failures in your “smart” implementation, or just check correctness.

---

### Project Structure

```markdown

src/
├── NaiveSolution.cpp         # Correct (but slow) reference solution
├── SmartSolution.cpp         # High‑performance solution under test
├── Generator.cpp             # User‑provided test‑case generator
├── StandartChecker.cpp       # Standart checker for problems (One answer for each test)
├── AdvancedCheker.cpp        # (Optional) Custom checker for advanced problems
└── StressTestRunner.cpp      # Main shell

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

1) Edit the following files in `src` directory(In each file you have a small instuction how to do it):
    - `NaiveSolution.cpp` - A correct solution that works for any time(even exponent or factorial)
    - `SmartSolution.cpp` - A solution that works efficiently, the correctness of which the user is not sure of
    - `Generator.cpp` - A generator that generates random short(or not so short, but a naive solution should process it in a reasonable amount of time) tests

2) Run the following command in terminal:

```bash
make start-stress
```

If the stress test detects a wrong answer (**WA**), you can inspect the failing test case in the `tests` directory—there you’ll find the input file (`in.txt`) and the corresponding outputs (`naiveOut.txt` and `smartOut.txt`) to help you diagnose the issue.

#### Advanced Mode

Use a custom checker (for problems with multiple valid outputs):

1) Exactly the same as in the basic mode

2) Edit `AdvancedChecker.cpp` in `src` directory - In it you should have files `test.txt`, `smartOut.txt`, `naiveOut.txt` to check the correctness of each, and then compare their results, for more understanding see the original example in AdvancedChecker.cpp.

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
   - In **advanced** mode, invoke your `AdvancedChecker` to validate the “smart” output.
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
