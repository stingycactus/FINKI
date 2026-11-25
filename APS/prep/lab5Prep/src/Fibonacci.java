import java.util.Arrays;

public class Fibonacci {

    // 1) Plain recursion: just translate the formula directly.
    static long fibRec(int n) {
        // TODO: base cases for n == 0 and n == 1, then the recursive formula
        if (n <= 1) {
            return n;
        }
        return fibRec(n-1) + fibRec(n-2);
    }

    // 2) Memoization: same as fibRec, but save each answer in memo[n].
    //    memo[n] == -1 means "not computed yet".
    static long[] memo;

    static long fibMemo(int n) {
        // TODO: base cases
        if (n<=1) {
            return n;
        }
        // TODO: if memo[n] is already filled, return it
        if (memo[n] != -1) {
            return memo[n];
        }
        // TODO: otherwise compute it, store it in memo[n], return it
        memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
        return memo[n];
    }

    // 3) Table (bottom-up): no recursion. Fill dp[0], dp[1], dp[2]... in a loop.
    static long fibTable(int n) {
        // TODO: create dp array of size n+1, set dp[0] and dp[1],
        //       then loop i = 2..n using dp[i-1] and dp[i-2]
        if (n <= 1) return n;
        long[] dp = new long[n + 1];
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    public static void main(String[] args) {
        // Correctness: expected 0 1 1 2 3 5 8 13 21 34
        for (int n = 0; n < 10; n++) {
            memo = new long[n + 1];
            Arrays.fill(memo, -1);
            System.out.println(n + ": " + fibRec(n) + " " + fibMemo(n) + " " + fibTable(n));
        }

        // Speed: watch how slow plain recursion gets
        int n = 42;
        long t = System.currentTimeMillis();
        System.out.println("fibRec(" + n + ")   = " + fibRec(n) + "  in " + (System.currentTimeMillis() - t) + " ms");

        memo = new long[n + 1];
        Arrays.fill(memo, -1);
        t = System.currentTimeMillis();
        System.out.println("fibMemo(" + n + ")  = " + fibMemo(n) + "  in " + (System.currentTimeMillis() - t) + " ms");

        t = System.currentTimeMillis();
        System.out.println("fibTable(" + n + ") = " + fibTable(n) + "  in " + (System.currentTimeMillis() - t) + " ms");
        // expected value: 267914296
    }
}