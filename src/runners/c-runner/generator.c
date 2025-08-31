/*

For users:

This is example of generator.

You need to write a code of generator of test. Use random to generate small test.

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXN 10
#define MAXM 1000
#define MAXA 100

int *generate_vector(int n, int l, int r) {
    int *res = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        res[i] = rand() % (r - l + 1) + l; // [l, r]
    }
    return res;
}

int main(void) {
    srand((unsigned)(time(NULL) ^ (unsigned)getpid()));

    int n = rand() % 2 + 1; // [1, 2]
    int m = rand() % 6 + 1; // [1, 6]
    printf("%d %d\n", n, m);

    int *a = generate_vector(n, 1, 3);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i + 1 < n)
            putchar(' ');
    }
    putchar('\n');

    free(a);
    return 0;
}