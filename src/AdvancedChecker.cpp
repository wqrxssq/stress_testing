/*

For example, this task is:

Given an integer n, and an array of numbers size n. You need to return sum of array.

The naive solution is correct. 
And smart solution can overflow(because I use "int" instead of "long long"), so it is sometimes inccorect.
This error is very difficult to detect manually (unless you are a professional), so stress testing is very usefull for it.

This is custom checker.

*/

/*

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

    long long sum1, sum2;
    stupid >> sum1;
    smart >> sum2;

    if (sum1 == sum2) {
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