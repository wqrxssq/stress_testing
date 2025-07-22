#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <sys/wait.h>

static const int PIECES = 10;

// execute cmd and return exit code
int execute(const std::string& cmd) {
    int status = system(cmd.c_str());
    return WEXITSTATUS(status);
}

void throwFormatError() {
    throw std::logic_error("Format Error!\n");
}

void PrintProgress(int test, int every_piece) {
    std::cout << '[';
    int done_pieces = test / every_piece;
    for (int i = 0; i < done_pieces; i++) {
        std::cout << "#####";
    } 
    for (int i = done_pieces; i < PIECES; i++) {
        std::cout << "-----";
    }
    std::cout << PIECES * done_pieces << "%]\n";
}

void compile(std::string path_to_file, std::string name, std::string path_to_bin) {
    int status_code = execute("clang++ -std=c++2a " + path_to_file + " -o " + path_to_bin);
    if (status_code != 0) {
        throw std::logic_error("Problems with compilation\n");
    }
    std::cout << "Compilation of " << name << " completed!\n";
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
        const std::string& correct_sol_name,
        const std::string& incorrect_sol_name,
        const std::string& generator_name,
        const std::string& checker_name = "src/StandartChecker.cpp") : 
        _correct_sol_name(correct_sol_name),
        _incorrect_sol_name(incorrect_sol_name),
        _generator_name(generator_name),
        _checker_name(is_advanced ? checker_name : "src/StandartChecker.cpp")
    {}

    void startStress() const {
        // compile
        compile(_correct_sol_name, "correct solution", "build/stupid");
        compile(_incorrect_sol_name, "testing solution", "build/smart");
        compile(_generator_name, "generator", "build/generator");
        compile(_checker_name, "checker", "build/checker");

        // read test count
        int cnt_tests;
        std::cout << "Enter number of tests (>= " << PIECES << "): ";
        if (!(std::cin >> cnt_tests) || cnt_tests < PIECES) {
            throw std::invalid_argument(
                "Error: invalid test count; must be integer >= " + std::to_string(PIECES)
            );
        }
        int every_piece = cnt_tests / PIECES;

        std::cout << "\nStarting stress testing (" << cnt_tests << " runs)...\n";
        for (int t = 0; t < cnt_tests; t++) {
            if (t % every_piece == 0) {
                PrintProgress(t, every_piece);
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
                std::cout << "WA on test #" << t + 1 << "!\n";
                std::cout << "Check dir 'tests' for more information!\n";
                return;
            }
        }
        PrintProgress(cnt_tests, every_piece);
        std::cout << "Your programm is correct:3\n";
    }

private:
    std::string _correct_sol_name;
    std::string _incorrect_sol_name;
    std::string _generator_name;
    std::string _checker_name;
};

int main(int argc, char ** argv) {
    switch (argc) {

    // Basic mode
    case 4: {
        std::string correct_sol_name = argv[1];
        std::string incorrect_sol_name = argv[2];
        std::string generator_name = argv[3];
        StressTesting Stress(false, correct_sol_name, incorrect_sol_name, generator_name);
        Stress.startStress();
        break;
    }

    // Advanced mode
    case 6: {
        std::string flag = argv[1];
        if (flag != "-a") {
            throwFormatError();
        } else {
            std::string correct_sol_name = argv[2];
            std::string incorrect_sol_name = argv[3];
            std::string generator_name = argv[4];
            std::string checker_name = argv[5];
            StressTesting Stress(true, correct_sol_name, incorrect_sol_name, generator_name, checker_name);
            Stress.startStress();
        }
        break;
    }
    }
    return 0;
}