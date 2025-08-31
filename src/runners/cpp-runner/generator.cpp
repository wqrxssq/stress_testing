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