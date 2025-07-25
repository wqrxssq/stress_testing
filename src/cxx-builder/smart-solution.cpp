/*

For example, this task is:

Given an integer n, and an array of numbers size n. You need to return sum of array.

The naive solution is correct. 
And smart solution can overflow(because I use "int" instead of "long long"), so it is sometimes inccorect.
This error is very difficult to detect manually (unless you are a professional), so stress testing is very usefull for it.

This is smart solution (with bugs).

*/

/*

For users: You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/


#include <iostream>
using namespace std;

const int MAXN = 1e5;
int n;
int a[MAXN];

void solve() {
    int sum = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    cout << sum << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();
}