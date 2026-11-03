import java.util.ArrayList;
import java.util.Random;

public class Box<T> {
    private ArrayList<T> items = new ArrayList<>();
    private Random random = new Random();

    public void add(T item) {
        items.add(item);
    }

    public boolean isEmpty() {
        return items.isEmpty();
    }

    public T drawItem() {
        if (isEmpty()) {
            return null;
        }
        return items.get(random.nextInt(items.size()));
    }

    public static void main(String[] args) {
        Box<String> stringBox = new Box<>();
        System.out.println(stringBox.drawItem());     // null: empty box

        stringBox.add("Dexter");
        stringBox.add("Seinfeld");
        stringBox.add("Barney");
        stringBox.add("Sheldon");
        stringBox.add("Costanza");
        stringBox.add("Hank");
        for (int i = 0; i < 5; i++) {
            System.out.println(stringBox.drawItem()); // one of the six names each time
        }
        System.out.println(stringBox.isEmpty());      // false: drawItem doesn't remove

        Box<Integer> intBox = new Box<>();
        intBox.add(23);
        intBox.add(15);
        intBox.add(19);
        intBox.add(3);
        intBox.add(92);
        System.out.println(intBox.drawItem());        // one of 23, 15, 19, 3, 92
    }
}