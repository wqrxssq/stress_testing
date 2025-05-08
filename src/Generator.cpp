/*

For example, this task is:

Given an integer n, and an array of numbers size n. You need to return sum of array.

The naive solution is correct. 
And smart solution can overflow(because I use "int" instead of "long long"), so it is sometimes inccorect.
This error is very difficult to detect manually (unless you are a professional), so stress testing is very usefull for it.

This is generator. (Its just an example, so dont think about why numbers range is generating like that).

*/

/*

For users:
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

const int MAXN = 100;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<int> generate_vector(int n, int l, int r) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = rnd() % (r - l + 1) + l; // [0, r - l] -> [l, r]
    }
    return res;
}

int main() {
    int n = rnd() % MAXN + 1; // [1, MAXN]
    cout << n << '\n';

    vector<int> a = generate_vector(n, 0, (rnd() & 15) == 15 ? (int)1e9 : 1000);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}