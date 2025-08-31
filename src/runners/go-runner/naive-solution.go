/*

For users:

This is example of naive-solution (uses brute-force)

You need to write naive solution, which is always correct, but maybe it is not very fast working.

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

package main

import (
	"bufio"
	"fmt"
	"os"
)

const INF = 1000000000

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m int
	fmt.Fscan(in, &n, &m)
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
	}

	var calc func(int) int
	calc = func(left int) int {
		if left == 0 {
			return 0
		}
		if left < 0 {
			return INF
		}
		ans := INF
		for i := 0; i < n; i++ {
			cur := calc(left - a[i])
			if cur+1 < ans {
				ans = cur + 1
			}
		}
		return ans
	}

	ans := calc(m)
	if ans == INF {
		fmt.Println(-1)
	} else {
		fmt.Println(ans)
	}
}
