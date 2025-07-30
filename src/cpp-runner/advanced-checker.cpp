/*

For users:

This is custom checker.

You need to write a custom checker. You should work with input("tests/in.txt"),
stupid("tests/naiveOut.txt"), smart("tests/smartOut.txt") threads.
If answers are correct, return 0, else return 1

Check example for more understanding.

*/


#include <iostream>
#include <fstream>
using namespace std;

int solve(ifstream& input, ifstream& stupid, ifstream& smart) {
    // Your code is here! 

    int n;
    input >> n;

    int expected_ans, testing_ans;
    stupid >> expected_ans;
    smart >> testing_ans;

    if (expected_ans == testing_ans) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    // DON'T CHANGE THESE LINES
    ifstream input("tests/in.txt");
    ifstream stupid("tests/naiveOut.txt");
    ifstream smart("tests/smartOut.txt");

    if (!input.is_open() || !stupid.is_open() || !smart.is_open()) {
        cerr << "Checker error: cannot open one of the files.\n";
        return 2;
    }

    return solve(input, stupid, smart);
}