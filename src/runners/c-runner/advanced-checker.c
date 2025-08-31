/*

For users:

This is custom checker.

You need to write a custom checker. You should work with input("tests/in.txt"),
stupid("tests/naiveOut.txt"), smart("tests/smartOut.txt") threads.
If answers are correct, return 0, else return 1

Check example for more understanding.

*/

#include <stdio.h>
#include <stdlib.h>

int solve(FILE *input, FILE *stupid, FILE *smart) {
    int expected_ans, testing_ans;
    fscanf(stupid, "%d", &expected_ans);
    fscanf(smart, "%d", &testing_ans);

    if (expected_ans == testing_ans)
        return 0;
    return 1;
}

int main(void) {
    FILE *input = fopen("tests/in.txt", "r");
    FILE *stupid = fopen("tests/naiveOut.txt", "r");
    FILE *smart = fopen("tests/smartOut.txt", "r");

    if (!input || !stupid || !smart) {
        fprintf(stderr, "Checker error: cannot open one of the files.\n");
        if (input)
            fclose(input);
        if (stupid)
            fclose(stupid);
        if (smart)
            fclose(smart);
        return 2;
    }

    int res = solve(input, stupid, smart);

    fclose(input);
    fclose(stupid);
    fclose(smart);

    return res;
}