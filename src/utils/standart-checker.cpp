// StandartChecker checks that answers of test and correct solutions are the same(word by word)

// WARNING: The programm does not check whitespaces!

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

int main() {
    // std::ifstream input("tests/in.txt");
    std::ifstream stupid("tests/naiveOut.txt");
    std::ifstream smart("tests/smartOut.txt");

    if (!stupid.is_open() || !smart.is_open()) {
        std::cerr << "Checker error: cannot open one of the files.\n";
        return 2;
    }

    // read all non-whitespace tokens from each output
    std::vector<std::string> correctTokens, testTokens;
    std::string token;

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