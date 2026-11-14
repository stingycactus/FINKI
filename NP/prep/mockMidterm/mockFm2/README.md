# Mock midterm 1 – Task 2

Define a class `DeliveryService` for managing the packages of a delivery company. The company delivers two types of packages:

* standard packages
* express packages

Every package has an id, the city it is delivered to and its weight in kg. For express packages, the distance in km is also kept.

The class should implement the following methods:

* Constructor `DeliveryService(double maxWeight)` – with a single argument, the maximum allowed weight of a package.
* Method `void readPackages(InputStream is)` – reads the packages from the input stream. Each line is one package in the format `S id city weight` for a standard package or `E id city weight distance` for an express package.
  * With an exception of type `OverweightPackageException`, prevent adding a package heavier than the maximum allowed weight. The exception should not stop the reading of the other packages. When it is caught, print the message `Package [id] exceeds the maximum weight of [maxWeight]`.
* Method `void printPackages(OutputStream os)` – prints all packages in the format shown in the test examples, sorted by their price in descending order. Packages with an equal price are sorted by id.
  * The price of a standard package is 150 if the weight is ≤ 2 kg, otherwise 150 + 40 · (weight − 2).
  * The price of an express package is 1.5 times the price of a standard package with the same weight, plus 10 for each km of distance.
* Method `Map<String, Double> revenuePerCity()` – returns a map where the keys are the cities, sorted alphabetically, and the values are the total price of all packages delivered to that city.

The class `DeliveryServiceTest` is given (see `src`).

## Examples

Input
```text
20
S P01 Skopje 1.5
S P02 Bitola 5
E P03 Skopje 2 30
E P04 Ohrid 4 10
S P05 Ohrid 25
E P06 Bitola 22.5 5
S P07 Skopje 2
```
Result
```text
=== READING PACKAGES ===
Package P05 exceeds the maximum weight of 20.00
Package P06 exceeds the maximum weight of 20.00
=== PACKAGES SORTED BY PRICE ===
Express[P03, Skopje, 2.00 kg, 30 km] -> 525.00
Express[P04, Ohrid, 4.00 kg, 10 km] -> 445.00
Standard[P02, Bitola, 5.00 kg] -> 270.00
Standard[P01, Skopje, 1.50 kg] -> 150.00
Standard[P07, Skopje, 2.00 kg] -> 150.00
=== REVENUE PER CITY ===
Bitola: 270.00
Ohrid: 445.00
Skopje: 825.00
```

Input
```text
10
E X10 Tetovo 10 40
S X02 Kumanovo 10.5
S X03 Tetovo 7.25
E X01 Kumanovo 0.5 12
S X04 Kumanovo 3
```
Result
```text
=== READING PACKAGES ===
Package X02 exceeds the maximum weight of 10.00
=== PACKAGES SORTED BY PRICE ===
Express[X10, Tetovo, 10.00 kg, 40 km] -> 1105.00
Standard[X03, Tetovo, 7.25 kg] -> 360.00
Express[X01, Kumanovo, 0.50 kg, 12 km] -> 345.00
Standard[X04, Kumanovo, 3.00 kg] -> 190.00
=== REVENUE PER CITY ===
Kumanovo: 535.00
Tetovo: 1465.00
```


---

# Part 2 (extra): filtering with predicates

Extend the class `DeliveryService` with the following methods:

* Method `List<DeliveryPackage> filter(Predicate<? super DeliveryPackage> condition)` – returns a new list with the packages that satisfy the condition, sorted the same way as in `printPackages`. If `condition` is `null`, throw `IllegalArgumentException`.
* Method `double totalPrice(Predicate<? super DeliveryPackage> condition)` – returns the total price of the packages that satisfy the condition.

The common parent class of both package types is called `DeliveryPackage` (rename yours, or change the type in `main`).

In the `main` function, define with lambda expressions:

* a condition that keeps only the packages delivered to `city`
* a condition that keeps only the express packages
* a condition that keeps only the packages with a price greater than `minPrice`

The input now ends with a line `FILTERS`, followed by the city and the minimum price. Replace the given test class with the one below; only the three marked lines in it may be changed.

```java
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
        String city = sc.nextLine().trim();
        double minPrice = Double.parseDouble(sc.nextLine().trim());

        DeliveryService service = new DeliveryService(maxWeight);
        System.out.println("=== READING PACKAGES ===");
        service.readPackages(new ByteArrayInputStream(sb.toString().getBytes()));
        System.out.println("=== PACKAGES SORTED BY PRICE ===");
        service.printPackages(System.out);
        System.out.println("=== REVENUE PER CITY ===");
        Map<String, Double> revenue = service.revenuePerCity();
        revenue.forEach((c, total) -> System.out.printf("%s: %.2f%n", c, total));

        // ===== TODO: define the following three conditions with lambda expressions =====
        Predicate<DeliveryPackage> inCity = null;          // packages delivered to city
        Predicate<DeliveryPackage> express = null;         // only express packages
        Predicate<DeliveryPackage> expensive = null;       // price greater than minPrice
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
```

The new test class needs `import java.util.function.Predicate;` at the top.

## Examples

Input
```text
20
S P01 Skopje 1.5
S P02 Bitola 5
E P03 Skopje 2 30
E P04 Ohrid 4 10
S P05 Ohrid 25
E P06 Bitola 22.5 5
S P07 Skopje 2
FILTERS
Skopje
400
```
Result
```text
=== READING PACKAGES ===
Package P05 exceeds the maximum weight of 20.00
Package P06 exceeds the maximum weight of 20.00
=== PACKAGES SORTED BY PRICE ===
Express[P03, Skopje, 2.00 kg, 30 km] -> 525.00
Express[P04, Ohrid, 4.00 kg, 10 km] -> 445.00
Standard[P02, Bitola, 5.00 kg] -> 270.00
Standard[P01, Skopje, 1.50 kg] -> 150.00
Standard[P07, Skopje, 2.00 kg] -> 150.00
=== REVENUE PER CITY ===
Bitola: 270.00
Ohrid: 445.00
Skopje: 825.00
=== PACKAGES FOR Skopje ===
Express[P03, Skopje, 2.00 kg, 30 km] -> 525.00
Standard[P01, Skopje, 1.50 kg] -> 150.00
Standard[P07, Skopje, 2.00 kg] -> 150.00
=== EXPRESS PACKAGES MORE EXPENSIVE THAN 400.00 ===
Express[P03, Skopje, 2.00 kg, 30 km] -> 525.00
Express[P04, Ohrid, 4.00 kg, 10 km] -> 445.00
Total price of express packages: 970.00
Total price of packages not in Skopje: 715.00
IllegalArgumentException
```

Input
```text
10
E X10 Tetovo 10 40
S X02 Kumanovo 10.5
S X03 Tetovo 7.25
E X01 Kumanovo 0.5 12
S X04 Kumanovo 3
FILTERS
Kumanovo
1200
```
Result
```text
=== READING PACKAGES ===
Package X02 exceeds the maximum weight of 10.00
=== PACKAGES SORTED BY PRICE ===
Express[X10, Tetovo, 10.00 kg, 40 km] -> 1105.00
Standard[X03, Tetovo, 7.25 kg] -> 360.00
Express[X01, Kumanovo, 0.50 kg, 12 km] -> 345.00
Standard[X04, Kumanovo, 3.00 kg] -> 190.00
=== REVENUE PER CITY ===
Kumanovo: 535.00
Tetovo: 1465.00
=== PACKAGES FOR Kumanovo ===
Express[X01, Kumanovo, 0.50 kg, 12 km] -> 345.00
Standard[X04, Kumanovo, 3.00 kg] -> 190.00
=== EXPRESS PACKAGES MORE EXPENSIVE THAN 1200.00 ===
Total price of express packages: 1450.00
Total price of packages not in Kumanovo: 1465.00
IllegalArgumentException
```
