/*

For users: 

This is smart solution (uses greedy aproach).

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 10;
const int MAXM = 1000;
int n;
int a[MAXN];

void solve() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);
    reverse(a, a + n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (m - a[i] >= 0) {
            m -= a[i];
            ans++;
        }
    }

    if (m > 0) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}