import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class Item {
    int weight;
    int value;

    public Item(int weight, int value) {
        this.weight = weight;
        this.value = value;
    }

    public double getRatio() {
        return (double) value / weight;
    }
}

public class FractionalKnapsack {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int w = in.nextInt();
        List<Item> items = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            items.add(new Item(in.nextInt(), in.nextInt()));
        }
        items.sort(Comparator.comparing(Item::getRatio, Comparator.reverseOrder()));
        double totalValue = 0;
        for (Item item : items) {
            if (item.weight < w) {
                totalValue+=item.value;
                w-=item.weight;
            } else {
                totalValue+= ((double)w/item.weight) * item.value;
                break;
            }
        }
        System.out.println(totalValue);
    }
}
