// StandartChecker checks that answers of test and correct solutions are the same(word by word)

// WARNING: The programm does not check whitespaces!

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ifstream input("tests/in.txt");
    ifstream stupid("tests/out_stupid.txt");
    ifstream smart("tests/out_smart.txt");

    if (!input.is_open() || !stupid.is_open() || !smart.is_open()) {
        cerr << "Checker error: cannot open one of the files.\n";
        return 1;
    }

    // read all non-whitespace tokens from each output
    vector<string> correctTokens, testTokens;
    string token;

    while (stupid >> token) {
        correctTokens.push_back(token);
    }
    while (smart >> token) {
        testTokens.push_back(token);
    }

    // number of tokens should be the same
    if (correctTokens.size() != testTokens.size()) {
        return 1;
    }

    // compare token by token
    for (size_t i = 0; i < correctTokens.size(); i++) {
        if (correctTokens[i] != testTokens[i]) {
            return 1;
        }
    }

    // all tokens match
    return 0;
}