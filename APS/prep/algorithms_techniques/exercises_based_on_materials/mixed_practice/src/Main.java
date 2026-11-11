import java.util.*;

class Stall {
    double kg;
    double price;

    public Stall(double kg, double price) {
        this.kg = kg;
        this.price = price;
    }

    public double kgPerDenar() {
        return kg / price;
    }
}

public class Main {
    public static void main(String[] args) {
        // 1. Brute force: study minutes
        int[] minutes = {2, 3, 1, 4, 2, 3};
        System.out.println("pairs summing to 5: " + countPairs(minutes, 5));
        System.out.println("segments summing to 5: " + countSegments(minutes, 5));
        System.out.println("segments summing to 10: " + countSegments(new int[]{5, 5, 5}, 10));

        // 2. Greedy: vending machine change
        System.out.println("coins: " + changeCoins(new int[]{5, 1, 10, 2}, 100, 63));
        System.out.println("coins: " + changeCoins(new int[]{10, 5}, 50, 37));
        System.out.println("coins: " + changeCoins(new int[]{1, 3, 4}, 10, 4));

        // 3. Fractional knapsack: nut market
        System.out.println("kg bought: " + maxNuts(new double[]{10, 4, 6}, new double[]{50, 40, 12}, 60));
        System.out.println("kg bought: " + maxNuts(new double[]{10, 4, 6}, new double[]{50, 40, 12}, 200));

        // 4. Sweep: parking garage (a car leaving at X still occupies its spot at X)
        int[] enter = {8, 9, 10, 12, 14, 15};
        int[] exit  = {10, 12, 11, 15, 16, 17};
        System.out.println("spots needed: " + minSpots(enter, exit));
        System.out.println("spots needed: " + minSpots(new int[]{1, 3, 5}, new int[]{3, 5, 7}));
    }

    // TODO 1a: pairs i < j with minutes[i] + minutes[j] == target
    static int countPairs(int[] minutes, int target) {
        int count = 0;
        for (int i = 0; i < minutes.length; i++) {
            for (int j = i+1; j < minutes.length; j++) {
                int sum = minutes[i]+minutes[j];
                if (sum == target) {
                    count++;
                }
            }
        }
        return count;
    }

    // TODO 1b: runs of consecutive days whose total is exactly target
    static int countSegments(int[] minutes, int target) {
        int count = 0;
        for (int i = 0; i < minutes.length; i++) {
            int sum = 0;
            for (int j = i; j < minutes.length; j++) {
                sum+=minutes[j];
                if (sum > target) {
                    break;
                }
                if (sum == target) {
                    count++;
                    break;
                }
            }
        }
        return count;
    }

    // TODO 2: greedy change for paid - price; print the coins used, return the count or -1
    static int changeCoins(int[] coins, int paid, int price) { // {5, 1, 10, 2}, 100, 63, change = 37
        List<Integer> sorted = new ArrayList<>();
        for (int coin : coins) sorted.add(coin);
        sorted.sort(Comparator.reverseOrder());
        List<Integer> coinsUsed = new ArrayList<>();
        int coinsUsedCount = 0;
        int change = paid - price;
        for (Integer coin : sorted) {
            int count = 0;
            if (change >= coin) { // no need for if
                count = change / coin;
                for (int i = 0; i < count; i++) {
                    coinsUsed.add(coin);
                }
                coinsUsedCount+=count;
                change-=coin*count;
            }
        }
        if (change != 0) {
            return -1;
        }
        System.out.println(coinsUsed);
        return coinsUsedCount; // same as coinsUsed.size()
    }

    // TODO 3: most kilos you can buy with budget (partial stalls allowed)
    static double maxNuts(double[] kg, double[] price, double budget) {
        List<Stall> stalls = new ArrayList<>();
        for (int i = 0; i < kg.length; i++) {
            stalls.add(new Stall(kg[i], price[i]));
        }
        stalls.sort(Comparator.comparing(Stall::kgPerDenar, Comparator.reverseOrder()));
        double mostKg = 0;
        for (Stall stall : stalls) {
            if (budget >= stall.price) {
                mostKg+=stall.kg;
                budget-=stall.price;
            } else {
                mostKg+= (budget / stall.price) * stall.kg;
                break;
            }
        }
        return mostKg;
    }
    
    static int minSpots(int[] enter, int[] exit) {
        enter = enter.clone();
        exit = exit.clone();
        Arrays.sort(enter);
        Arrays.sort(exit);
        int j = 0;
        int current = 0;
        int spotsNeeded = 0;
        for (int i = 0; i < enter.length; i++) {
//            int[] enter = {8, 9, 10, 12, 14, 15};
//            int[] exit  = {10, 12, 11, 15, 16, 17};
            while (exit[j] < enter[i]) {
                current--;
                j++;
            }
            current++;
            spotsNeeded = Math.max(current, spotsNeeded);
        }
        return spotsNeeded;
    }
}