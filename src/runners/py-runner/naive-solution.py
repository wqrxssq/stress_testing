# For users: 

# This is example of naive-solution (uses brute-force)

# You need to write naive solution, which is always correct, but maybe it is not very fast working.

# You should write code as usual(cin, cout),
# no need to work with any threads,
# all the hard work is done for you

import sys
sys.setrecursionlimit(10000)

INF = 10**9

def calc(left, a):
    if left == 0:
        return 0
    if left < 0:
        return INF
    ans = INF
    for x in a:
        ans = min(ans, calc(left - x, a) + 1)
    return ans

def solve():
    data = sys.stdin.read().split()
    n, m = map(int, data[:2])
    a = list(map(int, data[2:2+n]))

    res = calc(m, a)
    if res >= INF:
        print(-1)
    else:
        print(res)

solve()
