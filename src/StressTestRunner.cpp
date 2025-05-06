#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

static const double EPS = 1e6;
static const int PIECES = 5;

void execute(string s) {
    system(s.c_str());
}

// argv[1] - correct solution(stupid)
// argv[2] - incorrect solution
// argv[3] - generator 

int main(int argc, char ** argv) {
    if (argc != 4) {
        cerr << "Wrong number of arguments\n";
        cerr << "argv[1] - correct solution(stupid)\n"
                "argv[2] - incorrect solution\n"
                "argv[3] - generator\n";
        return 1;
    }

    string correct_sol_name = argv[1];
    string incorrect_sol_name = argv[2];
    string generator_name = argv[3];

    // compile
    execute("clang++ -std=c++2a " + correct_sol_name + " -o build/stupid");
    cerr << "Compilation of smart solution completed!\n";
    execute("clang++ -std=c++2a " + incorrect_sol_name + " -o build/smart");
    cerr << "Compilation of correct solution completed!\n";
    execute("clang++ -std=c++2a " + generator_name + " -o build/generator");
    cerr << "Compilation of generator completed!\n";

    int cnt_tests;
    cerr << "Print cnt_tests: ";
    cin >> cnt_tests;
    int every_piece = cnt_tests / PIECES;

    cerr << "Start of testing\n";
    // searching for WA
    for (int t = 1; t <= cnt_tests; t++) {
        if ((t - 1) % every_piece == 0) {
            cout << '[';
            int done_pieces = (t - 1) / every_piece;
            for (int i = 0; i < done_pieces; i++) {
                cout << "#####";
            } 
            for (int i = done_pieces; i < PIECES; i++) {
                cout << ".....";
            }
            cout << 20 * done_pieces << "%";
            cout << "]\n";
        }

        // gen test
        execute("build/generator >tests/in.txt");
        // cerr << "Gen is ok!\n";

        // run stupid
        execute("build/stupid <tests/in.txt >tests/out_stupid.txt");
        // cerr << "stupid is ok!\n";

        // run smart
        execute("build/smart <tests/in.txt >tests/out_smart.txt");
        // cerr << "smart is ok!\n";

        // checker
        ifstream input("tests/in.txt");
        ifstream smart("tests/out_smart.txt");
        ifstream stupid("tests/out_stupid.txt");

        int n;
        input >> n;

        for (int i = 0; i < n; i++) {
            double ans1, ans2;
            stupid >> ans1;
            smart >> ans2;

            if (fabs(ans1 - ans2) > EPS) {
                cerr << "I have found WA on test " << t << ":( SAD";
                return 1;
            }
        }
    }
    cerr << "Your programm is correct:3\n";
    return 0;
}