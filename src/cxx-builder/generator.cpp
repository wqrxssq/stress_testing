/*

For example, this task is ATM-machine:

Problem Statement:

You are given an ATM machine with `n` types of banknotes and a target sum `m`.
Each banknote type has a positive integer denomination `a_i`.
You may use any denomination any number of times (including zero) to form the sum.

---

Input:

- The first line contains two integers `n` and `m` (1 <= n <= 10, 1 <= m <= 1000)
- The second line contains `n` integers `a_1, a_2, ..., a_n` (1 <= a_i <= 100)

---

Output:
Print a single integer — the minimum number of banknotes needed to form the sum `m`.
If it is impossible to form exactly `m`, print `-1`.

---

Examples:

1)

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

2)

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

The naive solution is correct but very slow (TL). It uses brute-force. 
The smart solution uses greedy algorithm (choose the most valueable denomination), so sometimes it is correct.
This error is difficult to detect by hand, so stress testing is very usefull for it.

*/

/*

For users:

This is example of generator.

You need to write a code of generator of test. Use random to generate small test.

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/


#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <assert.h>
using namespace std;

const int MAXN = 10;
const int MAXM = 1000;
const int MAXA = 100;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<int> generate_vector(int n, int l, int r) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = rnd() % (r - l + 1) + l; // [0, r - l] -> [l, r]
    }
    return res;
}

int main() {
    int n = rnd() % 2 + 1; // [1, 2]
    int m = rnd() % 6 + 1; // [1, 6]
    cout << n << ' ' << m << '\n';

    vector<int> a = generate_vector(n, 1, 3);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}