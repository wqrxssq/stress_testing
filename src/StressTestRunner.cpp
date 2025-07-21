#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

static const int PIECES = 10;

// execute cmd and return exit code
int execute(const string& cmd) {
    int status = system(cmd.c_str());
    return WEXITSTATUS(status);
}

void throwFormatError() {
    cerr << "Format Error!\n"
    "Input commands:\n"
    "1) Standard mode - No argv\n"
    "2) Advanced mode - argv[1] == '-a' or argv[1] == '-advanced'\n"
    "3) Working with files:\n"
    "- <path/to/naive> <path/to/smart> <path/to/generator>\n"
    "  argv[1] - correct solution (stupid)\n"
    "  argv[2] - incorrect solution\n"
    "  argv[3] - generator\n"
    "- -a <path/to/naive> <path/to/smart> <path/to/generator> <path/to/checker>\n"
    "  '-a' flag enables checker‑based verdicts\n"
    "  argv[1] - correct solution (stupid)\n"
    "  argv[2] - incorrect solution\n"
    "  argv[3] - generator\n"
    "  argv[4] - path to the checker\n";
    exit(1);
}

void printProgress(int test, int every_piece) {
    cerr << '[';
    int done_pieces = (test - 1) / every_piece;
    for (int i = 0; i < done_pieces; i++) {
        cerr << "#####";
    } 
    for (int i = done_pieces; i < PIECES; i++) {
        cerr << ".....";
    }
    cerr << 10 * done_pieces << "%]\n";
}

void printFile(ifstream& file) {
    string line;
    while (getline(file, line)) {
        cerr << line << '\n';
    }
}

class StressTesting {
public:
    StressTesting(bool is_advanced) :
        _correct_sol_name("src/NaiveSolution.cpp"),
        _incorrect_sol_name("src/SmartSolution.cpp"),
        _generator_name("src/Generator.cpp"),
        _checker_name(is_advanced ? "src/AdvancedChecker.cpp" : "src/StandartChecker.cpp")
    {}

    StressTesting(bool is_advanced,
        const string& correct_sol_name,
        const string& incorrect_sol_name,
        const string& generator_name,
        const string& checker_name = "src/StandartChecker.cpp") : 
        _correct_sol_name(correct_sol_name),
        _incorrect_sol_name(incorrect_sol_name),
        _generator_name(generator_name),
        _checker_name(is_advanced ? checker_name : "src/StandartChecker.cpp")
    {}

    void startStress() const {
        // compile
        execute("clang++ -std=c++2a " + _correct_sol_name + " -o build/stupid");
        cerr << "Compilation of correct solution completed!\n";
        execute("clang++ -std=c++2a " + _incorrect_sol_name + " -o build/smart");
        cerr << "Compilation of smart(but maybe incorrect) solution completed!\n";
        execute("clang++ -std=c++2a " + _generator_name + " -o build/generator");
        cerr << "Compilation of generator completed!\n";
        execute("clang++ -std=c++2a " + _checker_name + " -o build/checker");
        cerr << "Compilation of checker completed!\n";

        // read test count
        int cnt_tests;
        cerr << "Enter number of tests (>= " << PIECES << "): ";
        if (!(cin >> cnt_tests) || cnt_tests < PIECES) {
            cerr << "Error: invalid test count; must be integer >= " << PIECES << "\n";
            exit(3);
        }
        int every_piece = cnt_tests / PIECES;

        cerr << "\nStarting stress testing (" << cnt_tests << " runs)...\n";
        for (int t = 1; t <= cnt_tests; t++) {
            if ((t - 1) % every_piece == 0) {
                printProgress(t, every_piece);
            }

            // gen test
            execute("build/generator >tests/in.txt");

            // run solutions
            execute("build/stupid <tests/in.txt >tests/naiveOut.txt");
            execute("build/smart <tests/in.txt >tests/smartOut.txt");

            // run checker and get exit code
            int checker_code = execute("build/checker");

            // found WA
            if (checker_code != 0) {
                cerr << "WA on test #" << t << "!\n";

                // ifstream input("tests/in.txt");
                // ifstream stupid("tests/naiveOut.txt");
                // ifstream smart("tests/smartOut.txt");

                // cerr << "====Input====\n";
                // printFile(input);
                // cerr << '\n';

                // cerr << "====Your answer====\n";
                // printFile(smart);
                // cerr << '\n';

                // cerr << "====Expected answer====\n";
                // printFile(stupid);
                cerr << '\n';

                exit(1);
            }
        }
        cerr << "Your programm is correct:3\n";
    }

private:
    string _correct_sol_name;
    string _incorrect_sol_name;
    string _generator_name;
    string _checker_name;
};

int main(int argc, char ** argv) {
    switch (argc) {

    // Basic mode
    case 1: {
        StressTesting Stress(false);
        Stress.startStress();
        break;
    }

    // Advanced mode
    case 2: {
        string flag = argv[1];
        if (flag == "-a" || flag == "-advanced") {
            StressTesting Stress(true);
            Stress.startStress();
        } else {
            throwFormatError();
        }
        break;
    }

    // Basic mode with own files
    case 4: {
        string correct_sol_name = argv[1];
        string incorrect_sol_name = argv[2];
        string generator_name = argv[3];
        StressTesting Stress(false, correct_sol_name, incorrect_sol_name, generator_name);
        Stress.startStress();
        break;
    }

    // Advanced mode with own files
    case 6: {
        string flag = argv[1];
        if (flag != "-a") {
            throwFormatError();
        } else {
            string correct_sol_name = argv[2];
            string incorrect_sol_name = argv[3];
            string generator_name = argv[4];
            string checker_name = argv[5];
            StressTesting Stress(true, correct_sol_name, incorrect_sol_name, generator_name, checker_name);
            Stress.startStress();
        }
        break;
    }
    default:
        throwFormatError();
    }

    return 0;
}