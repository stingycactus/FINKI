import java.util.ArrayList;
import java.util.Scanner;

class Product {
    private String name;
    private double price;

    public String getName() {
        return name;
    }

    public double getPrice() {
        return price;
    }

    public Product(String name, double price) {
        this.name = name;
        this.price = price;
    }

    public double finalPrice() {
        return price;
    }

    @Override
    public String toString() {
        return String.format("%s price=%.2f final=%.2f", name, price, finalPrice());
    }
}

class Food extends Product {
    private int daysToExpiry;

    public Food(String name, double price, int daysToExpiry) {
        super(name, price);
        this.daysToExpiry = daysToExpiry;
    }

    @Override
    public double finalPrice() {
        return daysToExpiry <= 3 ? super.finalPrice() * 0.5 : super.finalPrice();
    }

    @Override
    public String toString() {
        return String.format("%s days=%d", super.toString(), daysToExpiry);
    }

    public int getDaysToExpiry() {
        return daysToExpiry;
    }
}

class Electronics extends Product {
    private int warrantyMonths;

    public Electronics(String name, double price, int warrantyMonths) {
        super(name, price);
        this.warrantyMonths = warrantyMonths;
    }

    @Override
    public double finalPrice() {
        return warrantyMonths > 24 ? super.finalPrice() * 1.15 : super.finalPrice();
    }

    public int getWarrantyMonths() {
        return warrantyMonths;
    }

    @Override
    public String toString() {
        return String.format("%s warranty=%d", super.toString(), warrantyMonths);
    }
}

class Pair<K, V> {
    private K key;
    private V value;

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    @Override
    public String toString() {
        return String.format("(%s, %s)", key, value);
    }
}

class Container<T extends Product> {
    private String name;
    private int capacity;
    ArrayList<T> list = new ArrayList<>();

    public Container(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
    }

    boolean add(T item) {
        if (list.size() == capacity) {
            return false;
        }
        list.add(item);
        return true;
    }

    int size() {
        return list.size();
    }

    double totalValue() {
        double sum = 0;
        for (int i = 0; i < size(); i++) {
            sum += list.get(i).finalPrice();
        }
        return sum;
    }

    T mostExpensive() {
        if (size() == 0) {
            return null;
        }
        int index = 0;
        for (int i = 1; i < size(); i++) {
            if (list.get(i).finalPrice() > list.get(index).finalPrice()) {
                index = i;
            }
        }
        return list.get(index);
    }

    Pair<String, Double> summary() {
        return new Pair<>(name, totalValue());
    }

    void print(){
        System.out.printf("=== %s (%d/%d) ===%n", name, size(), capacity);
        for (int i = 0; i < size(); i++) {
            System.out.println(list.get(i));
        }
        System.out.printf("Total: %.2f%n", totalValue());
        if(mostExpensive()!=null){
            T mostExpensiveProduct = mostExpensive();
            System.out.printf("Most expensive: %s (%.2f)%n", mostExpensiveProduct.getName(), mostExpensiveProduct.finalPrice());
        }
        else {
            System.out.println("Most expensive: none");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int fridgeCapacity = in.nextInt();
        int techCapacity = in.nextInt();
        int overflowCapacity = in.nextInt();
        Container<Food> foodContainer = new Container<>("Fridge", fridgeCapacity);
        Container<Electronics> techContainer = new Container<>("Tech", techCapacity);
        Container<Product> overflowContainer = new Container<>("Overflow", overflowCapacity);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            String type = in.next();
            String name = in.next();
            double price = in.nextDouble();
            if (type.equals("F")){
                int days = in.nextInt();
                Food f = new Food(name, price, days);
                if (!foodContainer.add(f)) {
                    if (!overflowContainer.add(f)){
                        System.out.printf("Rejected: %s%n", name);
                    }
                }
            }
            else if (type.equals("E")){
                int warranty = in.nextInt();
                Electronics e = new Electronics(name, price, warranty);
                if (!techContainer.add(e)) {
                    if(!overflowContainer.add(e)){
                        System.out.printf("Rejected: %s%n", name);
                    }
                }
            }
        }
        foodContainer.print();
        techContainer.print();
        overflowContainer.print();
        Food mostExpensiveFood = foodContainer.mostExpensive();
        Electronics mostExpensiveElectronic = techContainer.mostExpensive();
        Product mostExpensiveOverflow = overflowContainer.mostExpensive();
        Product expensive = mostExpensiveFood;
        if (mostExpensiveElectronic!=null && mostExpensiveElectronic.finalPrice() > expensive.finalPrice()) {
            expensive = mostExpensiveElectronic;
        }
        if (mostExpensiveOverflow!=null && mostExpensiveOverflow.finalPrice() > expensive.finalPrice()) {
            expensive = mostExpensiveOverflow;
        }
//        System.out.printf("Most expensive: %s (%.2f)%n", expensive.getName(), expensive.finalPrice());
        Pair<String, Double> f = foodContainer.summary();
        Pair<String, Double> t = techContainer.summary();
        Pair<String, Double> o = overflowContainer.summary();
        Pair<String, Double> best = f;
        if (t.getValue()>best.getValue()){
            best=t;
        }
        if (o.getValue() > best.getValue()) {
            best=o;
        }
        System.out.printf("Most valuable container: %s (%.2f)%n", best.getKey(), best.getValue());
        if (foodContainer.size()!=0){
            System.out.printf("Top food expires in %d days%n", mostExpensiveFood.getDaysToExpiry());
        }
        if (techContainer.size()!=0){
            System.out.printf("Top electronics warranty: %d months%n", mostExpensiveElectronic.getWarrantyMonths());
        }
    }
}
