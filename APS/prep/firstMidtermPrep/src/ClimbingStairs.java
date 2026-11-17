import java.util.ArrayList;
import java.util.Scanner;

public class ClimbingStairs {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] ways = new int[n+1];
        ways[0] = 1;
        ways[1] = 1;
        for (int i = 2; i <= n; i++) {
            ways[i] = ways[i-1] + ways[i-2];
        }
        System.out.println(ways[n]);
    }
}
