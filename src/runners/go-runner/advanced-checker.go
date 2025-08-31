/*

For users:

This is custom checker.

You need to write a custom checker. You should work with input("tests/in.txt"),
stupid("tests/naiveOut.txt"), smart("tests/smartOut.txt") threads.
If answers are correct, return 0, else return 1

Check example for more understanding.

*/

package main

import (
	"fmt"
	"os"
)

func main() {
	inputFile := "tests/in.txt"
	stupidFile := "tests/naiveOut.txt"
	smartFile := "tests/smartOut.txt"

	input, err1 := os.Open(inputFile)
	if err1 != nil {
		fmt.Fprintln(os.Stderr, "Checker error: cannot open input file:", inputFile)
		os.Exit(2)
	}
	defer input.Close()

	stupid, err2 := os.Open(stupidFile)
	if err2 != nil {
		fmt.Fprintln(os.Stderr, "Checker error: cannot open naive output file:", stupidFile)
		os.Exit(2)
	}
	defer stupid.Close()

	smart, err3 := os.Open(smartFile)
	if err3 != nil {
		fmt.Fprintln(os.Stderr, "Checker error: cannot open smart output file:", smartFile)
		os.Exit(2)
	}
	defer smart.Close()

	var expectedAns, testingAns int
	if _, err := fmt.Fscan(stupid, &expectedAns); err != nil {
		fmt.Fprintln(os.Stderr, "Checker error: cannot read expected answer from naiveOut.txt")
		os.Exit(2)
	}
	if _, err := fmt.Fscan(smart, &testingAns); err != nil {
		fmt.Fprintln(os.Stderr, "Checker error: cannot read testing answer from smartOut.txt")
		os.Exit(2)
	}

	if expectedAns == testingAns {
		os.Exit(0)
	} else {
		os.Exit(1)
	}
}
