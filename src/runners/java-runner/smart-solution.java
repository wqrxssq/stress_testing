/*

For users: 

This is smart solution (uses greedy approach).

You should write code as usual(System.in, System.out),
no need to work with any threads,
all the hard work is done for you

*/

import java.util.*;

public class SmartSolution {
    
    private static final int INF = 1000000000;
    private static final int MAXN = 10;
    private static final int MAXM = 1000;
    private static int n;
    private static int[] a = new int[MAXN];
    
    private static void solve() {
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        int m = sc.nextInt();
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
        }
        
        Arrays.sort(a, 0, n);
        // Reverse the array
        for (int i = 0; i < n / 2; i++) {
            int temp = a[i];
            a[i] = a[n - 1 - i];
            a[n - 1 - i] = temp;
        }
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (m - a[i] >= 0) {
                m -= a[i];
                ans++;
            }
        }
        
        if (m > 0) {
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
