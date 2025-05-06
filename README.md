## Stress Testing

A lightweight shell for **automated stress testing** of two competing solutions:

- `NaiveSolution.cpp` (slow but guaranteed correct)  
- `SmartSolution.cpp` (fast, but may contain bugs)

By generating random test cases and comparing outputs, this tool helps you find edge‑case failures in your “smart” implementation, or just check correctness.

---

### 📦 Project Structure

```markdown

.
├── NaiveSolution.cpp         # Correct (but slow) reference solution
├── SmartSolution.cpp         # High‑performance solution under test
├── Generator.cpp             # User‑provided test‑case generator
├── StandartChecker.cpp       # Standart checker for problems (One answer for each test)
├── AdvancedCheker            # (Optional) Custom checker for advanced problems (Multiple answers for each test)
└── StressTestRunner.cpp      # Main shell

````

---

### 🚀 Usage

#### Basic Mode

Run without a custom checker. Each test’s output is compared for **exact match**:

1) Edit the following files (In each file you have a small instuction how to do it):
    - `NaiveSolution.cpp` - A correct solution that works for any time(even exponent or factorial)
    - `SmartSolution.cpp` - A solution that works efficiently, the correctness of which the user is not sure of
    - `Generator.cpp` - A generator that generates random short(or not so short, but a naive solution should process it in a reasonable amount of time) tests

2) Run the following command in terminal:

```bash
/build/main
```

**Warning**: Don't edit 'StressTestRunner.cpp', you don't need it.

#### Advanced Mode

Use a custom checker (for problems with multiple valid outputs):

1) Exactly the same as in the basic mode

2) Edit 'AdvancedChecker.cpp' - In it you should have files 'test.txt', 'smartOut.txt', 'naiveOut.txt' to check the correctness of each, and then compare their results, for more understanding see the original example in AdvancedChecker.cpp.

3) Run the following command in terminal:

```bash
/build/stress -advanced
```

or just:

```bash
/build/stress -a
```

#### Other features

Also you can use this command for basic mode:

```bash
build/stress <path/to/naive> <path/to/smart> <path/to/generator>
```

* `argv[1]` — path to the **correct** (naive) solution
* `argv[2]` — path to the **tested** (smart) solution
* `argv[3]` — path to the **test generator**

And for advanced mode:

```bash
build/stress <path/to/naive> <path/to/smart> <path/to/generator> <path/to/checker> -a
```

* `argv[4]` — path to the **checker** executable
* `-a` flag enables checker‑based verdicts

#### Logs

If you want to get statistics for usage, run the command:

```bash
build/stress -logs
```

---

### ⚙️ How It Works

1. **Generate** a random test via your `generator`.
2. **Run** both solutions (`naive` and `smart`) on that test.
3. **Compare** outputs:
   - In **basic** mode, do a direct string comparison.
   - In **advanced** mode, invoke your `AdvancedChecker` to validate the “smart” output.
4. **Report** the first failing test (input + both outputs) and halt.

Loop until a discrepancy is found or a user‑defined iteration limit is reached.

---

### 🛠️ Writing Your Generator

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
