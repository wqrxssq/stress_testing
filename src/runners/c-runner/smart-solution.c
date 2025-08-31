/*

For users: 

This is smart solution (uses greedy aproach).

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000
#define MAXN 10
#define MAXM 1000

int n_glob;
int a[MAXN];

int cmp_desc(const void *p1, const void *p2) {
    int x = *(const int *)p1;
    int y = *(const int *)p2;
    return (y - x); /* descending */
}

void solve(void) {
    int m;
    scanf("%d %d", &n_glob, &m);
    for (int i = 0; i < n_glob; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n_glob, sizeof(int), cmp_desc);

    int ans = 0;
    for (int i = 0; i < n_glob; i++) {
        while (m - a[i] >= 0) {
            m -= a[i];
            ans++;
        }
    }

    if (m > 0) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}

int main(void) {
    solve();
    return 0;
}