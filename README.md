## Stress Testing Framework

A lightweight shell for **automated stress testing** of two competing solutions:

- `NaiveSolution.cpp` (slow but guaranteed correct)  
- `SmartSolution.cpp` (fast, but may contain bugs)

By generating random test cases and comparing outputs, this tool helps you find edge‑case failures in your “smart” implementation, or just check correctness.

---

### 📦 Project Structure

```

.
├── NaiveSolution.cpp         # Correct (but slow) reference solution
├── SmartSolution.cpp         # High‑performance solution under test
├── Generator.cpp             # User‑provided test‑case generator
├── Checker.cpp               # (Optional) Custom checker for advanced problems
└── StressTestRunner.cpp      # Main shell

````

---

### 🚀 Usage

Instruction if you don`t need check ()

Run this command in terminal:

```bash
/build/main
```

If using advanced checker:

```bash
build 
# If using advanced checker:
g++ -std=c++17 naive.cpp smart.cpp generator.cpp checker.cpp StressTestRunner.cpp -o stress-adv
````

#### Basic Mode

Run without a custom checker. Each test’s output is compared for **exact match**:

```bash
./stress <path/to/naive> <path/to/smart> <path/to/generator>
```

* `argv[1]` — path to the **correct** (naive) solution
* `argv[2]` — path to the **tested** (smart) solution
* `argv[3]` — path to the **test generator**

#### Advanced Mode

Use a custom checker (for problems with multiple valid outputs):

```bash
./stress-adv <path/to/naive> <path/to/smart> <path/to/generator> <path/to/checker> -advanced
```

* `argv[4]` — path to the **checker** executable
* `-advanced` flag enables checker‑based verdicts

---

### ⚙️ How It Works

1. **Generate** a random test via your `generator`.
2. **Run** both solutions (`naive` and `smart`) on that test.
3. **Compare** outputs:

   * In **basic** mode, do a direct string comparison.
   * In **advanced** mode, invoke your `checker` to validate the “smart” output.
4. **Report** the first failing test (input + both outputs) and halt.

Loop until a discrepancy is found or a user‑defined iteration limit is reached.

---

### 🛠️ Writing Your Generator

Your generator should read nothing from **stdin** and output **one** random test case per invocation, for example:

```cpp
// generator.cpp (pseudocode)
#include <iostream>;
#include <random>;

int main() {
    std::mt19937_64 rng(/* seed */);
    int n = rng() % 100 + 1;
    std::cout << n << "\n";
    for (int i = 0; i < n; ++i)
        std::cout << (rng() % 1000) << " ";
    return 0;
}
```

---

### 🎯 Tips & Best Practices

* Seed your RNG with a high‑resolution clock to avoid repeating tests.
* Start with small constraints, then gradually increase to find corner cases.
* Use the **advanced** mode when your problem has multiple correct outputs.
* Inspect the failing test to identify logical errors in your “smart” solution.

Happy stress‑testing! 🚀
