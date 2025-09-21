/*

For users: 

This is example of naive-solution (uses brute-force)

You need to write naive solution, which is always correct, but maybe it is not very fast working.

You should write code as usual(System.in, System.out),
no need to work with any threads,
all the hard work is done for you

*/

import java.util.*;

public class NaiveSolution {
    
    private static final int INF = 1000000000;
    private static final int MAXN = 10;
    private static final int MAXM = 1000;
    private static int n;
    private static int[] a = new int[MAXN];
    
    private static int calc(int left) {
        if (left == 0) {
            return 0;
        }
        if (left < 0) {
            return INF;
        }
        int ans = INF;
        for (int i = 0; i < n; i++) {
            ans = Math.min(ans, calc(left - a[i]) + 1);
        }
        return ans;
    }
    
    private static void solve() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        int m = sc.nextInt();
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }
        
        int ans = calc(m);
        if (ans == INF) {
            System.out.println(-1);
        } else {
            System.out.println(ans);
        }
        sc.close();
    }
    
    public static void main(String[] args) {
        solve();
    }
}
