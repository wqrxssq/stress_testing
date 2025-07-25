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

This is example of naive-solution (uses brute-force)

You need to write naive solution, which is always correct, but maybe it is not very fast working.

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

#include <iostream>
using namespace std;

const int INF = 1e9;
const int MAXN = 10;
const int MAXM = 1000;
int n;
int a[MAXN];

int calc(int left) {
    if (left == 0) {
        return 0;
    }
    if (left < 0) {
        return INF;
    }
    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, calc(left - a[i]) + 1);
    }
    return ans;
}

void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = calc(m);
    if (ans == INF) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}