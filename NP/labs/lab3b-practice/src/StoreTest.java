import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

class InvalidProductException extends Exception {
    public InvalidProductException(String line) {
        super(String.format("Invalid product: %s", line));
    }
}

class CategoryNotFoundException extends Exception {
    public CategoryNotFoundException(String category) {
        super(String.format("Category %s not found", category));
    }
}

abstract class Product implements Comparable<Product> {
    private int id;
    private String name;
    private String category;
    private double basePrice;
    List<Integer> ratings = new ArrayList<>();

    public Product(int id, String name, String category, double basePrice) {
        this.id = id;
        this.name = name;
        this.category = category;
        this.basePrice = basePrice;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getCategory() {
        return category;
    }

    public double getBasePrice() {
        return basePrice;
    }

    public abstract double getFinalPrice();

    public abstract char getTypeCode();

    public static Product createProduct(String line) throws InvalidProductException {
        String[] parts = line.trim().split(";", -1);
        if (parts.length != 6 && parts.length != 7) {
            throw new InvalidProductException(line);
        }
        String type = parts[0].trim();

        List<Integer> ratingsList = new ArrayList<>();
        try {
            int id = Integer.parseInt(parts[1].trim());
            String name = parts[2].trim();
            String category = parts[3].trim();
            double basePrice = Double.parseDouble(parts[4].trim());
            if (basePrice < 0) {
                throw new InvalidProductException(line);
            }
            if (parts.length == 7) {
                String ratings = parts[6];
                if (ratings.isEmpty()) {
                    throw new InvalidProductException(line);
                }
                String[] ratingsParts = ratings.split(",");
                for (String ratingsPart : ratingsParts) {
                    int r = Integer.parseInt(ratingsPart.trim());
                    if (r < 1 || r > 5) {
                        throw new InvalidProductException(line);
                    }
                    ratingsList.add(r);
                }
            }
            Product product;
            if (type.equals("P")) {
                double weight = Double.parseDouble(parts[5].trim());
                if (weight <= 0) {
                    throw new InvalidProductException(line);
                }
                product = new PhysicalProduct(id, name, category, basePrice, weight);
            } else if (type.equals("D")) {
                int sizeMb = Integer.parseInt(parts[5].trim());
                if (sizeMb <= 0) {
                    throw new InvalidProductException(line);
                }
                product = new DigitalProduct(id, name, category, basePrice, sizeMb);
            } else {
                throw new InvalidProductException(line);
            }
            for (int r : ratingsList) {
                product.addRating(r);
            }
            return product;
        } catch (NumberFormatException e) {
            throw new InvalidProductException(line);
        }
    }

    @Override
    public int compareTo(Product other) {
        int byPrice = Double.compare(this.getFinalPrice(), other.getFinalPrice());
        if (byPrice != 0) {
            return byPrice;
        }

        int byName = this.name.compareTo(other.name);
        if (byName != 0) {
            return byName;
        }

        return Integer.compare(this.id, other.id);
    }

    @Override
    public String toString() {
        return String.format("%c %-5d %-15s %-12s %10.2f", getTypeCode(), id, name, category, getFinalPrice());
    }

    public void addRating(int rating) {
        ratings.add(rating);
    }

    List<Integer> getRatings() {
        return ratings;
    }

    int getRatingCount() {
        return ratings.size();
    }

    boolean hasRatings() {
        return !ratings.isEmpty();
    }

    double getAverageRating() {
        if (ratings.isEmpty()) {
            return 0;
        }
        return ratings.stream().mapToInt(Integer::intValue).average().getAsDouble();
    }
}

class PhysicalProduct extends Product {
    private double weight;

    public PhysicalProduct(int id, String name, String category, double basePrice, double weight) {
        super(id, name, category, basePrice);
        this.weight = weight;
    }

    public double getWeight() {
        return weight;
    }

    public double getShippingCost() {
        return weight <= 1 ? 60 : 60 + 30 * (weight - 1);
    }

    @Override
    public double getFinalPrice() {
        return getBasePrice() + getShippingCost();
    }

    @Override
    public char getTypeCode() {
        return 'P';
    }

    @Override
    public String toString() {
        return String.format("%s | %.2f kg", super.toString(), weight);
    }
}

class DigitalProduct extends Product {
    private int sizeMb;

    public DigitalProduct(int id, String name, String category, double basePrice, int sizeMb) {
        super(id, name, category, basePrice);
        this.sizeMb = sizeMb;
    }

    public int getSizeMb() {
        return sizeMb;
    }

    @Override
    public double getFinalPrice() {
        return getBasePrice() * 0.9;
    }

    @Override
    public char getTypeCode() {
        return 'D';
    }

    @Override
    public String toString() {
        return String.format("%s | %d MB", super.toString(), sizeMb);
    }
}

class ProductFilters {
    public static Predicate<Product> priceBetween(double min, double max) {
        return product -> product.getFinalPrice() >= min && product.getFinalPrice() <= max;
    }

    public static Predicate<Product> minAverageRating(double minRating) {
        return product -> product.hasRatings() && product.getAverageRating() >= minRating;
    }

    public static Predicate<Product> heavierThan(double kg) {
        return product -> {
            if (product instanceof PhysicalProduct) {
                PhysicalProduct pp = (PhysicalProduct) product;
                return pp.getWeight() > kg;
            }
            return false;
        };
    }
}

class Store {
    List<Product> products = new ArrayList<>();
    private int invalidCount = 0;

    public int readProducts(InputStream is) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        int validCount = 0;
        String line = br.readLine();
        while (line != null) {
            if (!line.trim().isEmpty()) {
                try {
                    products.add(Product.createProduct(line));
                    validCount++;
                } catch (InvalidProductException e) {
                    invalidCount++;
                }
            }
            line = br.readLine();
        }
        return validCount;
    }

    public int getInvalidLines() {
        return invalidCount;
    }

    public void printSorted(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        products.stream().sorted().forEach(pw::println);
        pw.flush();
    }

    public void printByCategory(OutputStream os, String category) throws CategoryNotFoundException {
        PrintWriter pw = new PrintWriter(os);
        List<Product> inCategory = products.stream()
                .filter(product -> product.getCategory().equals(category))
                .sorted(Comparator.comparing(Product::getName, String.CASE_INSENSITIVE_ORDER)
                        .thenComparing(Product::getFinalPrice, Comparator.reverseOrder())
                        .thenComparing(Product::getId))
                .collect(Collectors.toList());

        if (inCategory.isEmpty()) {
            throw new CategoryNotFoundException(category);
        }
        for (Product product : inCategory) {
            pw.println(product);
        }
        pw.flush();
    }

    public void printStatistics(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        if (products.isEmpty()) {
            pw.println("No products");
        } else {
            int total = products.size();
            int digital = 0;
            for (Product product : products) {
                if (product.getClass() == DigitalProduct.class) {
                    digital++;
                }
            }
            int physical = total - digital;
            Product cheapest = Collections.min(products);
            Product mostExpensive = Collections.max(products);
            double avg = products.stream().mapToDouble(Product::getFinalPrice).average().getAsDouble();

            pw.printf("Total: %d (physical: %d, digital: %d)%n", total, physical, digital);
            pw.printf("Cheapest: %s%n", cheapest);
            pw.printf("Most expensive: %s%n", mostExpensive);
            pw.printf("Average price: %.2f%n", avg);
        }
        pw.flush();
    }

    public void printTopRated(OutputStream os, int n) {
        if (n <= 0) throw new IllegalArgumentException();
        PrintWriter pw = new PrintWriter(os);
        List<Product> filtered = products.stream()
                .filter(Product::hasRatings)
                .sorted(Comparator
                        .comparing(Product::getAverageRating, Comparator.reverseOrder())
                        .thenComparing(Product::getRatingCount, Comparator.reverseOrder())
                        .thenComparing(Comparator.naturalOrder()))
                .limit(n)
                .collect(Collectors.toList());
        if (filtered.isEmpty()) pw.println("No rated products");
        int rank = 1;
        for (Product product : filtered) {
            pw.printf("%d. %-15s %.2f (%d)%n", rank++, product.getName(), product.getAverageRating(), product.getRatingCount());
        }
        pw.flush();
    }

    public Map<String, DoubleSummaryStatistics> categoryStatistics() {
        Map<String, DoubleSummaryStatistics> map = new TreeMap<>();
        for (Product p : products) {
            map.putIfAbsent(p.getCategory(), new DoubleSummaryStatistics());
            map.get(p.getCategory()).accept(p.getFinalPrice());
        }
        return map;
    }

    void printCategoryReport(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        Map<String, DoubleSummaryStatistics> map = categoryStatistics();
        if (map.isEmpty()) {
            pw.println("No products");
        }
        for (Map.Entry<String, DoubleSummaryStatistics> e : map.entrySet()) {
            DoubleSummaryStatistics s = e.getValue();
            pw.println(String.format("%-12s count: %d, min: %.2f, max: %.2f, avg: %.2f",
                    e.getKey(), s.getCount(), s.getMin(), s.getMax(), s.getAverage()));
        }
        pw.flush();
    }

    List<Product> filter(Predicate<? super Product> condition) {
        if (condition == null) {
            throw new IllegalArgumentException();
        }
        List<Product> result = new ArrayList<>();
        for (Product product : products) {
            if (condition.test(product)) {
                result.add(product);
            }
        }
        Collections.sort(result);
        return result;
    }
}

public class StoreTest {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder productLines = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null && !line.trim().equals("COMMANDS")) {
            productLines.append(line).append("\n");
        }

        Store store = new Store();
        int read = store.readProducts(
                new ByteArrayInputStream(productLines.toString().getBytes(StandardCharsets.UTF_8)));
        System.out.println("Read products: " + read);
        System.out.println("Invalid lines: " + store.getInvalidLines());

        while ((line = br.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            String[] parts = line.split("\\s+");
            System.out.println("=== " + line + " ===");
            switch (parts[0]) {
                case "SORTED":
                    store.printSorted(System.out);
                    break;
                case "CATEGORY":
                    try {
                        store.printByCategory(System.out, parts[1]);
                    } catch (CategoryNotFoundException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "STATS":
                    store.printStatistics(System.out);
                    break;
                case "TOP":
                    try {
                        store.printTopRated(System.out, Integer.parseInt(parts[1]));
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                    }
                    break;
                case "REPORT":
                    store.printCategoryReport(System.out);
                    break;
                case "FILTER_PRICE":
                    printList(store.filter(ProductFilters.priceBetween(
                            Double.parseDouble(parts[1]), Double.parseDouble(parts[2]))));
                    break;
                case "FILTER_RATING":
                    printList(store.filter(ProductFilters.minAverageRating(Double.parseDouble(parts[1]))));
                    break;
                case "FILTER_HEAVY":
                    printList(store.filter(ProductFilters.heavierThan(Double.parseDouble(parts[1]))));
                    break;
                case "FILTER_NULL":
                    try {
                        printList(store.filter(null));
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                    }
                    break;
                default:
                    System.out.println("Unknown command");
            }
        }
    }

    private static void printList(List<Product> list) {
        if (list.isEmpty()) {
            System.out.println("No products");
            return;
        }
        for (Product p : list) {
            System.out.println(p);
        }
    }
}