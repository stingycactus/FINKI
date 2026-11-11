import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.println("count: " + greedyCoins(new int[]{1, 2, 5, 10, 50}, 87));
        System.out.println("count: " + greedyCoins(new int[]{1, 5, 8, 10}, 23));
        System.out.println("count: " + greedyCoins(new int[]{1, 2, 5, 8, 10}, 13));
        int[] jobs = {16, 9, 5, 11};
        System.out.println("average finish: " + averageFinish(jobs));
        int[] sortedJobs = jobs.clone();
        Arrays.sort(sortedJobs);
        System.out.println("average finish, shortest first: " + averageFinish(sortedJobs));
        System.out.println("smallest code: " + smallestNumber(new int[]{3, 0, 7, 1, 0}));
    }

    // greedyCoins also prints the coins it uses
    static int greedyCoins(int[] coins, int sum) {
        int n = coins.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (coins[j] < coins[j + 1]) {
                    int temp = coins[j];
                    coins[j] = coins[j + 1];
                    coins[j + 1] = temp;
                }
            }
        }
        List<Integer> coinsUsed = new ArrayList<>();
        for (int coin : coins) {
            if (sum == 0) {
                break;
            }
            int k = sum / coin;
            sum -= k * coin;
            for (int i = 0; i < k; i++) {
                coinsUsed.add(coin);
            }
        }
        System.out.println(coinsUsed);
        return coinsUsed.size();
    }

    static double averageFinish(int[] jobs) {
        int n = jobs.length;
        int time = 0;      // the clock: when the current job finishes
        int total = 0;     // sum of everyone's finish times
        for (int i = 0; i < n; i++) {
            time += jobs[i];   // this job runs, the clock moves forward by its length
            total += time;     // this job finishes at 'time'
        }
        return (double) total / n;
    }

    static String smallestNumber(int[] digits) {
        int[] sorted = digits.clone();
        Arrays.sort(sorted);
        for (int i = 0; i < sorted.length; i++) {
            if (sorted[i] != 0) {
                int temp = sorted[0];
                sorted[0] = sorted[i];
                sorted[i] = temp;
                break;
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i : sorted) {
            sb.append(i);
        }
        return sb.toString();
    }
}