# For users:

# This is example of generator.

# You need to write a code of generator of test. Use random to generate small test.

# You should write code as usual(cin, cout),
# no need to work with any threads,
# all the hard work is done for you

import random
import time

MAXN = 10
MAXM = 1000
MAXA = 100

random.seed(int(time.time() * 1e6) & 0xFFFFFFFF)

def generate_vector(n, l, r):
    return [random.randint(l, r) for _ in range(n)]


n = random.randint(1, 2)
m = random.randint(1, 6)
print(n, m)

a = generate_vector(n, 1, 3)
print(*a)


