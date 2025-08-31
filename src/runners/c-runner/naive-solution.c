/*

For users: 

This is example of naive-solution (uses brute-force)

You need to write naive solution, which is always correct, but maybe it is not very fast working.

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

#include <stdio.h>

#define INF 1000000000
#define MAXN 10
#define MAXM 1000

int n_glob;
int a[MAXN];

int calc(int left) {
    if (left == 0)
        return 0;
    if (left < 0)
        return INF;
    int ans = INF;
    for (int i = 0; i < n_glob; i++) {
        int cur = calc(left - a[i]);
        if (cur < INF && cur + 1 < ans)
            ans = cur + 1;
    }
    return ans;
}

void solve(void) {
    int m;
    scanf("%d %d", &n_glob, &m);
    for (int i = 0; i < n_glob; i++) {
        scanf("%d", &a[i]);
    }

    int ans = calc(m);
    if (ans == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}

int main(void) {
    solve();
    return 0;
}