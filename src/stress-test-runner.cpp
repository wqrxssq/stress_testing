#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <sys/wait.h>

#include "langs.hpp"

static const int kPARTS = 10;
static const std::string kPATH_TO_BASIC_CHECKER = "src/utils/standart-checker.cpp";

// execute cmd and return exit code
int Execute(const std::string& cmd) {
    int status = system(cmd.c_str());
    return WEXITSTATUS(status);
}

void ThrowFormatError() {
    throw std::logic_error("Format Error!\n");
}

void PrintProgress(int test, int every_piece) {
    std::cout << '[';
    int done_pieces = test / every_piece;
    for (int i = 0; i < done_pieces; i++) {
        std::cout << "#####";
    } 
    for (int i = done_pieces; i < kPARTS; i++) {
        std::cout << "-----";
    }
    std::cout << kPARTS * done_pieces << "%]\n";
}

void Compile(std::string path_to_file, std::string name, std::string path_to_bin) {
    auto compiler = CompilerFactory::FromPath(path_to_file);
    bool is_compiled = compiler->Compile(path_to_file, path_to_bin);
    if (!is_compiled) {
        throw std::logic_error("Problems with compilation\n");
    }
    std::cout << "Compilation of " << name << " completed!\n";
}

class StressTesting {
public:
    StressTesting(
        const std::string& correct_sol_name,
        const std::string& incorrect_sol_name,
        const std::string& generator_name,
        const std::string& checker_name = kPATH_TO_BASIC_CHECKER) : 
        _path_to_correct_sol(correct_sol_name),
        _path_to_testing_sol(incorrect_sol_name),
        _path_to_generator(generator_name),
        _path_to_checker(checker_name)
    {}

    void CompileFiles() const {
        Compile(_path_to_correct_sol, "correct solution", "build/stupid");
        Compile(_path_to_testing_sol, "testing solution", "build/smart");
        Compile(_path_to_generator, "generator", "build/generator");
        Compile(_path_to_checker, "checker", "build/checker");
    }

    int RunTest() const {
        // gen test
        Execute("build/generator >tests/in.txt");

        // run solutions
        Execute("build/stupid <tests/in.txt >tests/naiveOut.txt");
        Execute("build/smart <tests/in.txt >tests/smartOut.txt");

        // run checker and get exit code
        return Execute("build/checker");
    }

    void StartStress() const {
        CompileFiles();

        // read test count
        int cnt_tests;
        std::cout << "Enter number of tests (>= " << kPARTS << "): ";
        if (!(std::cin >> cnt_tests) || cnt_tests < kPARTS) {
            throw std::invalid_argument(
                "Error: invalid test count; must be integer >= " + std::to_string(kPARTS)
            );
        }
        int every_piece = cnt_tests / kPARTS;

        std::cout << "\nStarting stress testing (" << cnt_tests << " runs)...\n";
        for (int t = 0; t < cnt_tests; t++) {
            if (t % every_piece == 0) {
                PrintProgress(t, every_piece);
            }

            int status = RunTest();

            // found WA
            if (status != 0) {
                std::cout << "WA on test #" << t + 1 << "!\n";
                std::cout << "Check dir 'tests' for more information!\n";
                return;
            }
        }
        PrintProgress(cnt_tests, every_piece);
        std::cout << "Your programm is correct:3\n";
    }

private:
    std::string _path_to_correct_sol;
    std::string _path_to_testing_sol;
    std::string _path_to_generator;
    std::string _path_to_checker;
};

int main(int argc, char ** argv) {
    switch (argc) {

    // Basic mode
    case 4: {
        std::string correct_sol_name = argv[1];
        std::string incorrect_sol_name = argv[2];
        std::string generator_name = argv[3];
        StressTesting stress{correct_sol_name, incorrect_sol_name, generator_name};
        stress.StartStress();
        break;
    }

    // Advanced mode
    case 6: {
        std::string flag = argv[1];
        if (flag != "-a") {
            ThrowFormatError();
        } else {
            std::string correct_sol_name = argv[2];
            std::string incorrect_sol_name = argv[3];
            std::string generator_name = argv[4];
            std::string checker_name = argv[5];
            StressTesting stress{correct_sol_name, incorrect_sol_name, generator_name, checker_name};
            stress.StartStress();
        }
        break;
    }
    }
    return 0;
}