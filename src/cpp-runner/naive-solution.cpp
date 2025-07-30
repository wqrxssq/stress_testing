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