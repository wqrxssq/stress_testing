/*

For users:

This is smart solution (uses greedy aproach).

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, m int
	fmt.Fscan(in, &n, &m)
	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
	}

	sort.Slice(a, func(i, j int) bool { return a[i] > a[j] })

	ans := 0
	for i := 0; i < n; i++ {
		for m-a[i] >= 0 {
			m -= a[i]
			ans++
		}
	}

	if m > 0 {
		fmt.Println(-1)
	} else {
		fmt.Println(ans)
	}
}
