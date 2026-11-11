import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] w = new int[n];
        for (int i = 0; i < n; i++) {
            w[i] = in.nextInt();
        }
        int smallestDiff = Integer.MAX_VALUE;
        int pairCount = 0;
        int contiguousCount = 0;
        for (int i = 0; i < n; i++) {
            int diff = 0;
            for (int j = i+1; j < n; j++) {
                diff = Math.abs(w[i] - w[j]);
                smallestDiff = Math.min(smallestDiff, diff);
                if (w[i] + w[j] <= 10) {
                    pairCount++;
                }
            }
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum+=w[j];
                if (sum > 20) {
                    contiguousCount++;
                }
            }
        }
        System.out.println(smallestDiff);
        System.out.println(pairCount);
        System.out.println(contiguousCount);
    }
}
