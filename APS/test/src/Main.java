import java.util.ArrayList;

class Product {
    protected String name;
    protected double price;

    public Product(String name, double price) {
        this.name = name;
        this.price = price;
    }
    public double getPrice() { return price; }

    @Override
    public String toString() { return name + " " + price; }
}

class Food extends Product {
    private int daysToExpiry;

    public Food(String name, double price, int daysToExpiry) {
        super(name, price);
        this.daysToExpiry = daysToExpiry;
    }
    public int getDaysToExpiry() { return daysToExpiry; }
}

class Electronics extends Product {
    private int warrantyMonths;

    public Electronics(String name, double price, int warrantyMonths) {
        super(name, price);
        this.warrantyMonths = warrantyMonths;
    }
    public int getWarrantyMonths() { return warrantyMonths; }
}

class Container<T extends Product> {
    private String name;
    private int capacity;
    private ArrayList<T> items = new ArrayList<>();

    public Container(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
    }

    public boolean add(T item) {
        if (items.size() >= capacity) return false;
        items.add(item);
        return true;
    }

    public T mostExpensive() {
        if (items.isEmpty()) return null;
        T best = items.get(0);
        for (T item : items) {
            if (item.getPrice() > best.getPrice()) best = item;
        }
        return best;
    }
}

public class Main {
    public static void main(String[] args) {
        // Container<Food>: add() takes a Food, mostExpensive() returns a Food
        Container<Food> fridge = new Container<>("Fridge", 2);
        fridge.add(new Food("Milk", 2.0, 2));
        fridge.add(new Food("Cheese", 10.0, 10));
        Food top = fridge.mostExpensive();                 // a Food, no cast
        System.out.println(top.getDaysToExpiry());         // 10

        // Container<Product>: add() takes any Product, so Food and Electronics both fit
        Container<Product> overflow = new Container<>("Overflow", 2);
        overflow.add(new Food("Yogurt", 3.0, 5));
        overflow.add(new Electronics("Phone", 500.0, 36));
        System.out.println(overflow.mostExpensive());      // Phone 500.0

        // Try these one at a time and read the errors:
//         Container<Product> c = new Container<Food>("x", 1);   // ERROR: Container<Food> is not a Container<Product>
//         Food f = overflow.mostExpensive();                    // ERROR: returns a Product, not a Food
        // fridge.add(new Electronics("Tv", 900.0, 12));         // ERROR: fridge only accepts Food
    }
}