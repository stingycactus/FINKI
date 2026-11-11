import java.util.*;

class Item {
    private double profit;
    private double weight;

    public Item(double profit, double weight) {
        this.profit = profit;
        this.weight = weight;
    }

    public double getProfit() {
        return profit;
    }

    public double getWeight() {
        return weight;
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println(fractionalKnapsack(new double[]{25, 24, 15}, new double[]{18, 15, 10}, 20));
        System.out.println(fractionalKnapsack(new double[]{200, 150, 5, 80}, new double[]{10, 20, 0.5, 5}, 20));
        System.out.println(fractionalKnapsack(new double[]{60, 100, 120}, new double[]{10, 20, 30}, 50));
        System.out.println(fractionalKnapsack(new double[]{60, 100, 120}, new double[]{10, 20, 30}, 40));
    }

    //    static double fractionalKnapsack(double[] profit, double[] weight, double capacity) {
//        int n = profit.length;
//        for (int i = 0; i < n - 1; i++) {
//            for (int j = 0; j < n - 1 - i; j++) {
//                if (profit[j] / weight[j] < profit[j + 1] / weight[j + 1]) {
//                    double temp = profit[j];
//                    profit[j] = profit[j+1];
//                    profit[j+1] = temp;
//
//                    temp = weight[j];
//                    weight[j] = weight[j+1];
//                    weight[j+1] = temp;
//                }
//            }
//        }
//        double totalProfit = 0;
//        for (int i = 0; i < n; i++) {
//            if (capacity >= weight[i]) {
//                capacity -= weight[i];
//                totalProfit += profit[i];
//            } else {
//                totalProfit += profit[i] * (capacity / weight[i]);
//                break;
//            }
//        }
//        return totalProfit;
//    }
    static double fractionalKnapsack(double[] profit, double[] weight, double capacity) {
        List<Item> items = new ArrayList<>();
        for (int i = 0; i < profit.length; i++) {
            items.add(new Item(profit[i], weight[i]));
        }
        items.sort(Comparator.comparingDouble((Item o) -> o.getProfit() / o.getWeight()).reversed());
        double totalProfit = 0;
        for (Item item : items) {
            if (capacity >= item.getWeight()) {
                capacity -= item.getWeight();
                totalProfit += item.getProfit();
            } else {
                totalProfit += item.getProfit() * (capacity / item.getWeight());
                break;
            }
        }
        return totalProfit;
    }
}