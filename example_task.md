## ATM-machine

### Problem Statement

You are given an ATM machine with `n` types of banknotes and a target sum `m`.
Each banknote type has a positive integer denomination `a_i`.
You may use any denomination any number of times (including zero) to form the sum.

---

### Input

- The first line contains two integers `n` and `m` (1 <= n <= 10, 1 <= m <= 1000)
- The second line contains `n` integers `a_1, a_2, ..., a_n` (1 <= a_i <= 100)

---

### Output
Print a single integer — the minimum number of banknotes needed to form the sum `m`.
If it is impossible to form exactly `m`, print `-1`.

---

### Examples

- Test 1

    Input:
    ```
    3 8
    1 2 5
    ```

    Output:
    ```
    3
    ```

    Explanation:  You can form $8$ as $5 + 2 + 1$, using 3 banknotes.

- Test 2

    Input:
    ```
    2 3
    2 4
    ```

    Output:
    ```
    -1
    ```

    Explanation:  There is no way to sum to 3 using only denominations 2 and 4.

---

### Notes

- The naive solution is correct but very slow (TL). It uses brute-force. 
- The smart solution uses greedy algorithm (choose the most valueable denomination), so sometimes it is correct.
- This error is difficult to detect by hand, so stress testing is very usefull for it.
