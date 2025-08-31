/*

For users:

This is example of generator.

You need to write a code of generator of test. Use random to generate small test.

You should write code as usual(cin, cout),
no need to work with any threads,
all the hard work is done for you

*/

package main

import (
	"fmt"
	"math/rand"
	"time"
)

const (
	MAXN = 10
	MAXM = 1000
	MAXA = 100
)

func generateVector(n, l, r int) []int {
	res := make([]int, n)
	rangeLen := r - l + 1
	for i := 0; i < n; i++ {
		res[i] = rand.Intn(rangeLen) + l // [l, r]
	}
	return res
}

func main() {
	rand.Seed(time.Now().UnixNano())

	n := rand.Intn(2) + 1 // [1,2]
	m := rand.Intn(6) + 1 // [1,6]
	fmt.Printf("%d %d\n", n, m)

	a := generateVector(n, 1, 3)
	for i := 0; i < n; i++ {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(a[i])
	}
	fmt.Println()
}
