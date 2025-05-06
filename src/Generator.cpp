#include <iostream>
#include <random>
#include <set>
#include <chrono>
#include <vector>
#include <assert.h>
using namespace std;

const int MAXN = 5;
const int MAXH = 10;
const int MAXW = 5;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<int> generate_vector(int n, int l, int r) {
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = rnd() % (r - l + 1) + l; // [0, r - l] -> [l, r]
    }
    return res;
}

bool not_correct(vector<int>& a) {
    int sum = 0;
    for (auto x : a) {
        if (x) {
            sum++;
        } else {
            sum--;
            if (sum < 0) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int n = rnd() % 500 + 1;
    cout << n << '\n';

    vector<int> a(2 * n);
    for (int i = 0; i < n; i++) {
        a[i * 2] = 0;
        a[i * 2 + 1] = 1; 
    }
    do {
        shuffle(a.begin(), a.end(), rnd);
    } while (not_correct(a));

    int prev = 0;
    for (int i = 0; i < 2 * n; i++) {
        prev += rnd() % 1000 + 1;
        cout << (a[i] == 1 ? "+ " : "- ") << prev << '\n';
    }
}