/*
For users:

This is custom checker.

You need to write a custom checker. You should work with input("tests/in.txt"),
stupid("tests/naiveOut.txt"), smart("tests/smartOut.txt") threads.
If answers are correct, return 0, else return 1

Check example for more understanding.
*/

import java.io.*;
import java.util.*;

public class AdvancedChecker {

    static int solve(Scanner input, Scanner stupid, Scanner smart) {
        // Your code is here!
        // Example:
        // int n = input.nextInt();

        if (!stupid.hasNextInt() || !smart.hasNextInt()) {
            // malformed outputs
            return 1;
        }

        int expectedAns = stupid.nextInt();
        int testingAns  = smart.nextInt();

        return (expectedAns == testingAns) ? 0 : 1;
    }

    public static void main(String[] args) {
        try (
            FileInputStream in  = new FileInputStream("tests/in.txt");
            FileInputStream st  = new FileInputStream("tests/naiveOut.txt");
            FileInputStream sm  = new FileInputStream("tests/smartOut.txt");
            Scanner input  = new Scanner(in);
            Scanner stupid = new Scanner(st);
            Scanner smart  = new Scanner(sm)
        ) {
            int code = solve(input, stupid, smart);
            System.exit(code);
        } catch (FileNotFoundException e) {
            System.err.println("Checker error: cannot open one of the files.");
            System.exit(2);
        } catch (Exception e) {
            System.err.println("Checker runtime error: " + e.getMessage());
            System.exit(2);
        }
    }
}
