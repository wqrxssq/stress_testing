#pragma GCC optimize("O3,unroll-loops")

#include <math.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <climits>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
const double PI = acos(-1);
const double EPS = 1e-6;
const int INF = 1e9;
const ll INFLL = 1e18;
const int MOD = 1e9 + 7;

mt19937 rnd(static_cast<unsigned int>(chrono::steady_clock().now().time_since_epoch().count()));

#define all(_x) _x.begin(), _x.end()
#define rall(_x) _x.rbegin(), _x.rend()
#define pb push_back
#define ff first
#define ss second
#define sz(_x) (int)_x.size()
#define display(_x)        \
    for (auto el : _x)     \
        cout << el << ' '; \
    cout << '\n'
#define cin_arr(_x)     \
    for (auto& el : _x) \
        cin >> el;
#define fast_input ios_base::sync_with_stdio(0); cin.tie(0)
#define setpr(_x) cout << setprecision(_x) << fixed
#define debug(x) cout << __FUNCTION__ << ": " << #x " = " << (x) << endl

const int MAXN = 1e5;
int n;

long double p[MAXN];
long double ans[MAXN];

void solve() {
    cin >> n;

    fill(p, p + n, 1);

    int unlocked = 0;
    int balance = 0;
    for (int i = 0; i < 2 * n; i++) {
        char c;
        int t;
        cin >> c >> t;
        if (c == '+') {
            ans[unlocked++] -= t;
            ++balance;
        } else {
            for (int j = 0; j < unlocked; j++) {
                long double temp_prob = p[j] / balance;
                ans[j] += (long double)t * temp_prob;
                p[j] -= temp_prob;
            }
            --balance;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
}

int main() {
    fast_input;
    setpr(9);
    solve();
}