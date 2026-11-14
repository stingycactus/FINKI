import java.io.*;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

class OverweightPackageException extends Exception {
    public OverweightPackageException(String message) {
        super(message);
    }
}

class DeliveryService {
    private double maxWeight;
    List<Package> packages = new ArrayList<>();

    public DeliveryService(double maxWeight) {
        this.maxWeight = maxWeight;
    }

    public void readPackages(InputStream is) {
        Scanner in = new Scanner(is);
        while (in.hasNextLine()) {
            String line = in.nextLine().trim();
            String[] parts = line.split("\\s+");
            try {
                double weight = Double.parseDouble(parts[3]);
                if (weight > maxWeight) {
                    throw new OverweightPackageException(String.format("Package %s exceeds the maximum weight of %.2f", parts[1], maxWeight));
                }
                if (parts[0].equals("S")) {
                    packages.add(new StandardPackage(parts[1], parts[2], weight));
                } else {
                    packages.add(new ExpressPackage(parts[1], parts[2], weight, Integer.parseInt(parts[4])));
                }
            } catch (OverweightPackageException e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public void printPackages(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        packages.stream()
                .sorted(Comparator.comparing(Package::getPrice, Comparator.reverseOrder())
                        .thenComparing(Package::getId)).forEach(pw::println);
        pw.flush();
    }

    public Map<String, Double> revenuePerCity() {
        return packages.stream()
                .collect(Collectors.groupingBy(
                        p -> p.city,                               // key: the city
                        TreeMap::new,                                   // map type: sorted by key
                        Collectors.summingDouble(Package::getPrice)));     // value: total price
    }

    public List<Package> filter(Predicate<? super Package> condition) {
        if (condition == null) {
            throw new IllegalArgumentException();
        }
        return packages.stream()
                .filter(condition)
                .sorted(Comparator.comparing(Package::getPrice, Comparator.reverseOrder())
                        .thenComparing(Package::getId))
                .collect(Collectors.toList());
    }

    public double totalPrice(Predicate<? super Package> condition) {
        if (condition == null) {
            throw new IllegalArgumentException();
        }
        return packages.stream()
                        .filter(condition)
                .mapToDouble(Package::getPrice)
                .sum();
    }
}

abstract class Package {
    protected String id;
    protected String city;
    protected double weight;

    public Package(String id, String city, double weight) {
        this.id = id;
        this.city = city;
        this.weight = weight;
    }

    abstract public double getPrice();

    protected double standardPrice() {                  // shared formula
        return weight <= 2 ? 150 : 150 + 40 * (weight - 2);
    }

    public String getId() {
        return id;
    }

    @Override
    public String toString() { // P03, Skopje, 2.00 kg, 30 km
        return String.format("%s, %s, %.2f kg", id, city, weight);
    }

    public String getCity() {
        return city;
    }

    public double getWeight() {
        return weight;
    }
}

class StandardPackage extends Package {
    public StandardPackage(String id, String city, double weight) {
        super(id, city, weight);
    }

    @Override
    public double getPrice() {
        return standardPrice();
    }

    @Override
    public String toString() {
        return String.format("Standard[%s] -> %.2f", super.toString(), getPrice());
    }
}

class ExpressPackage extends Package {
    private int distance;

    public ExpressPackage(String id, String city, double weight, int distance) {
        super(id, city, weight);
        this.distance = distance;
    }

    @Override
    public double getPrice() {
        return super.standardPrice() * 1.5 + 10 * distance;
    }

    @Override
    public String toString() {
        return String.format("Express[%s, %d km] -> %.2f", super.toString(), distance, getPrice());
    }
}

public class DeliveryServiceTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double maxWeight = Double.parseDouble(sc.nextLine());

        StringBuilder sb = new StringBuilder();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if (line.trim().equals("FILTERS")) break;
            sb.append(line).append("\n");
        }

        DeliveryService service = new DeliveryService(maxWeight);
        System.out.println("=== READING PACKAGES ===");
        service.readPackages(new ByteArrayInputStream(sb.toString().getBytes()));
        System.out.println("=== PACKAGES SORTED BY PRICE ===");
        service.printPackages(System.out);
        System.out.println("=== REVENUE PER CITY ===");
        Map<String, Double> revenue = service.revenuePerCity();
        revenue.forEach((c, total) -> System.out.printf("%s: %.2f%n", c, total));

        String city = sc.nextLine().trim();
        double minPrice = Double.parseDouble(sc.nextLine().trim());
        // ===== TODO: define the following three conditions with lambda expressions =====
        Predicate<Package> inCity = p -> p.getCity().equals(city);          // packages delivered to city
        Predicate<Package> express = p -> p.getClass() == ExpressPackage.class;
        Predicate<Package> expensive = p -> p.getPrice() > minPrice;       // price greater than minPrice
        // ================================================================================

        System.out.println("=== PACKAGES FOR " + city + " ===");
        service.filter(inCity).forEach(System.out::println);
        System.out.println("=== EXPRESS PACKAGES MORE EXPENSIVE THAN " + String.format("%.2f", minPrice) + " ===");
        service.filter(express.and(expensive)).forEach(System.out::println);
        System.out.printf("Total price of express packages: %.2f%n", service.totalPrice(express));
        System.out.printf("Total price of packages not in %s: %.2f%n", city, service.totalPrice(inCity.negate()));
        try {
            service.filter(null);
            System.out.println("No exception");
        } catch (IllegalArgumentException e) {
            System.out.println("IllegalArgumentException");
        }
    }
}