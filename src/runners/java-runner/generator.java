/*

For users:

This is example of generator.

You need to write a code of generator of test. Use random to generate small test.

You should write code as usual(System.in, System.out),
no need to work with any threads,
all the hard work is done for you

*/

import java.util.*;

public class Generator {
    
    private static final int MAXN = 10;
    private static final int MAXM = 1000;
    private static final int MAXA = 100;
    
    private static Random rnd = new Random();
    
    private static int[] generateArray(int n, int l, int r) {
        int[] res = new int[n];
        for (int i = 0; i < n; i++) {
            res[i] = rnd.nextInt(r - l + 1) + l; // [l, r]
        }
        return res;
    }
    
    public static void main(String[] args) {
        int n = rnd.nextInt(2) + 1; // [1, 2]
        int m = rnd.nextInt(6) + 1; // [1, 6]
        System.out.println(n + " " + m);
        
        int[] a = generateArray(n, 1, 3);
        for (int i = 0; i < n; i++) {
            System.out.print(a[i]);
            if (i < n - 1) {
                System.out.print(" ");
            }
        }
        System.out.println();
    }
}