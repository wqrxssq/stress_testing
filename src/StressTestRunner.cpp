#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const double EPS = 1e6;
static const int PIECES = 10;

// execute cmd and return exit code
int execute(const string& cmd) {
    int status = system(cmd.c_str());
    return WEXITSTATUS(status);
}

void put_format_error() {
    cerr << R"(
    Fromat Error!

    Input commands:

    1) Standard mode - No argv

    2) Advanced mode - argv[1] == "-a" or argv[1] == "-advanced"

    3) Working with files:

    - <path/to/naive> <path/to/smart> <path/to/generator>
      argv[1] - correct solution (stupid)
      argv[2] - incorrect solution
      argv[3] - generator 

    - -a <path/to/naive> <path/to/smart> <path/to/generator> <path/to/checker>
      "-a" flag enables checker‑based verdicts
      argv[1] - correct solution (stupid)
      argv[2] - incorrect solution
      argv[3] - generator 
      argv[4] - path to the checker
    )";
}

void print_progress(int test, int every_piece) {
    cerr << '[';
    int done_pieces = (test - 1) / every_piece;
    for (int i = 0; i < done_pieces; i++) {
        cerr << "#####";
    } 
    for (int i = done_pieces; i < PIECES; i++) {
        cerr << ".....";
    }
    cerr << 10 * done_pieces << "%";
    cerr << "]\n";
}

class StressTesting {
public:
    StressTesting(bool is_advanced) {
        _correct_sol_name = "src/NaiveSolution.cpp";
        _incorrect_sol_name = "src/SmartSolution.cpp";
        _generator_name = "src/Generator.cpp";

        if (is_advanced) {
            _checker_name = "src/AdvancedChecker.cpp";
        } else {
            _checker_name = "src/StandartChecker.cpp";
        }
    }

    StressTesting(bool is_advanced, const string& correct_sol_name, const string& incorrect_sol_name,
                  const string& generator_name, const string& checker_name = "src/StandartChecker.cpp") {
        _correct_sol_name = correct_sol_name;
        _incorrect_sol_name = incorrect_sol_name;
        _generator_name = generator_name;

        if (is_advanced) {
            _checker_name = checker_name;
        } else {
            _checker_name = "src/StandartChecker.cpp";
        }
    }

    void startStress() const {
        // TODO: each file should exist

        // compile
        execute("clang++ -std=c++2a " + _correct_sol_name + " -o build/stupid");
        cerr << "Compilation of correct solution completed!\n";
        execute("clang++ -std=c++2a " + _incorrect_sol_name + " -o build/smart");
        cerr << "Compilation of smart(but maybe incorrect) solution completed!\n";
        execute("clang++ -std=c++2a " + _generator_name + " -o build/generator");
        cerr << "Compilation of generator completed!\n";
        execute("clang++ -std=c++2a " + _checker_name + " -o build/checker");
        cerr << "Compilation of checker completed!\n";

        int cnt_tests;
        cerr << "Print cnt_tests: ";
        cin >> cnt_tests;

        // TODO: cnt_tests should be >= 10
        int every_piece = cnt_tests / PIECES;

        cerr << "Start of testing\n";
        // searching for WA
        for (size_t t = 1; t <= cnt_tests; t++) {
            if ((t - 1) % every_piece == 0) {
                print_progress(t, every_piece);
            }

            // gen test
            execute("build/generator >tests/in.txt");

            // run solutions
            execute("build/stupid <tests/in.txt >tests/out_stupid.txt");
            execute("build/smart <tests/in.txt >tests/out_smart.txt");

            // run checker and get exit code
            int checker_code = execute("build/checker");

            if (checker_code != 0) {
                cerr << "WA on test #" << t << "!\n";
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
        StressTesting Stress{false};
        Stress.startStress();
        break;
    }

    // Advanced mode
    case 2: {
        if (argv[1] == "-a" || argv[1] == "-advanced") {
            StressTesting Stress{true};
            Stress.startStress();
        } else {
            put_format_error();
        }
        break;
    }

    // Basic mode with own files
    case 4: {
        string correct_sol_name = argv[1];
        string incorrect_sol_name = argv[2];
        string generator_name = argv[3];
        StressTesting Stress{false, correct_sol_name, incorrect_sol_name, generator_name};
        Stress.startStress();
        break;
    }

    // Advanced mode with own files
    case 6: {
        if (argv[1] != "-a") {
            put_format_error();
        } else {
            string correct_sol_name = argv[2];
            string incorrect_sol_name = argv[3];
            string generator_name = argv[4];
            string checker_name = argv[5];
            StressTesting Stress{true, correct_sol_name, incorrect_sol_name, generator_name, checker_name};
            Stress.startStress();
        }
        break;
    }
    default:
        put_format_error();
        break;
    }

    return 0;
}