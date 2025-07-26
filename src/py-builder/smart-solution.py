# For users: 

# This is smart solution (uses greedy aproach).

# You should write code as usual(cin, cout),
# no need to work with any threads,
# all the hard work is done for you

import sys

INF = 10**9

def solve():
    data = sys.stdin.read().split()
    n, m = map(int, data[:2])
    a = list(map(int, data[2:2+n]))

    a.sort(reverse=True)

    cnt = 0
    remaining = m
    for x in a:
        while remaining - x >= 0:
            remaining -= x
            cnt += 1

    if remaining > 0:
        print(-1)
    else:
        print(cnt)

solve()
