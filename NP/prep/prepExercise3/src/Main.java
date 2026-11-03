import java.lang.reflect.Array;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

class Bag<T> {
    private ArrayList<T> items;
    private Random random = new Random();


    public Bag() {
        this.items = new ArrayList<>();
    }

    void add(T item) {
        items.add(item);
    }

    int size() {
        return items.size();
    }

    boolean isEmpty() {
        return items.isEmpty();
    }

    @Override
    public String toString() {
        return items.toString();
    }

    public T draw() {
        return isEmpty() ? null : items.get(random.nextInt(size()));
    }

    public T take() {
        return isEmpty() ? null : items.remove(random.nextInt(size()));
    }

    ArrayList<T> getItems() {
        return new ArrayList<>(items);
    }
}

class Stats {
    public static double mean(ArrayList<? extends Number> items) {
        return (sum(items) / items.size());
    }

    public static <T extends Number> double sum(ArrayList<T> items) {
        double sum = 0;
        for (int i = 0; i < items.size(); i++) {
            sum += items.get(i).doubleValue();
        }
        return sum;
    }

    public static <T extends Comparable<T>> T maxOf(List<T> items) {
        if (items.isEmpty()) {
            return null;
        }
        int index = 0;
        for (int i = 1; i < items.size(); i++) {
            if (items.get(i).compareTo(items.get(index)) > 0) {
                index = i;
            }
        }
        return items.get(index);
    }
}

class Entry<T> implements Comparable<Entry<T>> {
    private final T item;
    private final int priority;

    Entry(T item, int priority) {
        this.item = item;
        this.priority = priority;
    }

    @Override
    public int compareTo(Entry<T> o) {
        return Comparator.comparing(Entry<T>::getPriority).compare(this, o);
    }


    public T getItem() {
        return item;
    }

    public int getPriority() {
        return priority;
    }

    @Override
    public String toString() {
        return String.format("%s(%d)", item, priority);
    }
}

class RankedBag<T> {
    private ArrayList<Entry<T>> entries;

    public RankedBag() {
        this.entries = new ArrayList<Entry<T>>();
    }

    public void add(T item, int priority) {
        Entry<T> entry = new Entry<>(item, priority);
        for (int i = 0; i < entries.size(); i++) {
            if (entries.get(i).getPriority() < priority) {
                entries.add(i, entry);
                return;
            }
        }
        entries.add(entry);
    }

    public T removeTop() {
        if (entries.isEmpty()) {
            return null;
        }
        return entries.remove(0).getItem();
    }

    ArrayList<Entry<T>> getEntries() {
        return new ArrayList<Entry<T>>(entries);
    }

    @Override
    public String toString() {
        return entries.toString();
    }
}

class Transform {
    public static <E extends Comparable<E>> List<E> applyAndSort(List<E> list, Function<E, E> f){
        return list.stream().map(f).sorted().collect(Collectors.toList());
    }
}

public class Main {
    public static void main(String[] args) {
//        Bag<String> bag = new Bag<>();
//        bag.add("Ana");
//        bag.add("Bob");
//        bag.add("Cleo");
//        System.out.println(bag);
//        Bag<Integer> intBag = new Bag<>();
//        System.out.println(intBag);
//        for (int i = 0; i < 5; i++) {
//            System.out.println(bag.draw());          // one of Ana/Bob/Cleo each time
//        }
//        System.out.println(bag.size());              // still 3: draw doesn't remove
//
//        while (!bag.isEmpty()) {
//            System.out.println(bag.take());          // each name exactly once, random order
//        }
//        System.out.println(bag.take());              // null: empty bag
//        System.out.println(bag.isEmpty());
//
//        Bag<Integer> scores = new Bag<>();
//        for (int x : new int[]{2, 4, 4, 4, 5, 5, 7, 9}) {
//            scores.add(x);
//        }
//        System.out.println(Stats.mean(scores.getItems()) + " " + Stats.sum(scores.getItems()));   // 5.0 40.0
//
//        Bag<Double> d = new Bag<>();
//        d.add(1.5);
//        d.add(2.5);
//        System.out.println(Stats.mean(d.getItems()) + " " + Stats.sum(d.getItems()));             // 2.0 4.0
//
//        System.out.println(Stats.mean(new ArrayList<Integer>()));                                 // NaN
//        Stats.mean(bag.getItems());   // Strings: should NOT compile, so try it once, then comment it out
//        RankedBag<String> prizes = new RankedBag<>();
//        prizes.add("bronze", 1);
//        prizes.add("gold", 10);
//        prizes.add("silver", 5);
//        prizes.add("gold2", 10);
//        System.out.println(prizes);
//        // [gold(10), gold2(10), silver(5), bronze(1)]
//
//        System.out.println(prizes.removeTop() + " " + prizes.removeTop() + " "
//                + prizes.removeTop() + " " + prizes.removeTop() + " " + prizes.removeTop());
//        // gold gold2 silver bronze null
//
//        RankedBag<Integer> nums = new RankedBag<>();
//        nums.add(100, 3);
//        nums.add(200, 3);
//        nums.add(300, 7);
//        System.out.println(nums);
//        // [300(7), 100(3), 200(3)]
//        System.out.println(nums.getEntries());
//        // [300(7), 100(3), 200(3)]


        // 1.5 step 2: compareTo signs
        Entry<String> a3 = new Entry<>("a", 3);
        Entry<String> b7 = new Entry<>("b", 7);
        Entry<String> c3 = new Entry<>("c", 3);
        System.out.println(a3.compareTo(b7));   // negative
        System.out.println(b7.compareTo(a3));   // positive
        System.out.println(a3.compareTo(c3));   // 0

// 1.5 step 4: maxOf on three types
        Bag<Integer> scores = new Bag<>();
        for (int x : new int[]{2, 4, 4, 4, 5, 5, 7, 9}) {
            scores.add(x);
        }
        System.out.println(Stats.maxOf(scores.getItems()));                                // 9
        System.out.println(Stats.maxOf(Arrays.asList("pear", "apple", "zebra", "kiwi")));  // zebra

        RankedBag<String> ranked = new RankedBag<>();
        ranked.add("bronze", 1);
        ranked.add("gold", 10);
        ranked.add("silver", 5);
        System.out.println(Stats.maxOf(ranked.getEntries()));                              // gold(10)

        System.out.println(Stats.maxOf(new Bag<Integer>().getItems()));                    // null (empty list)

    }
}
