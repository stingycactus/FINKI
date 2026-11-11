# Lab 3 Part B practice: FINKI Shop (ratings, ranking, report, filters)

> **This task text is guessed.** It was reconstructed from the real Part B test cases (at the bottom of this file) and written in the same format as the Part A text. The commands, inputs and expected outputs are real. Class names, method names and signatures are guesses: when you see the real text, follow its names. Every guessed signature below was checked against all 8 test cases with a test class written to match them.

Part B extends your Part A solution. Everything from Part A stays and is still tested (`SORTED`, `CATEGORY`, `STATS`).

Setup: `src/StoreTest.java` here is a copy of your Part A file. Work in it, and replace its `StoreTest` class with the one in section 4. Extra imports: `java.util.function.Predicate` (and `java.util.*` already covers `Map`, `TreeMap`, `DoubleSummaryStatistics`).

---

## 1. Ratings (changes in `Product` and `createProduct`)

A product can now have customer ratings. Each rating is an integer from `1` to `5`.

The class `Product` additionally stores `List<Integer> ratings` (empty by default; the constructor does not change). It must provide:

- `void addRating(int rating)` – adds a rating. If `rating` is less than `1` or greater than `5`, throws `IllegalArgumentException`.
- `List<Integer> getRatings()` – returns the ratings (read-only).
- `int getRatingCount()` – returns the number of ratings.
- `boolean hasRatings()` – returns `true` if the product has at least one rating.
- `double getAverageRating()` – returns the average of the ratings, or `0.0` if there are none.

### Line format

A line now has **6 or 7** fields:

```text
TYPE;id;name;category;basePrice;extra[;ratings]
```

The optional 7th field is a comma-separated list of ratings, for example `P;101;Laptop;electronics;45000;2.5;5,4,5`. Trim every rating before parsing.

`createProduct` additionally throws `InvalidProductException` if:

- the number of fields is not 6 or 7;
- the 7th field exists but is empty (e.g. `P;408;BadEmpty;x;10;1;`);
- a rating cannot be parsed as `int` (e.g. `4,a`);
- a rating is less than `1` or greater than `5` (e.g. `0,5`, `6`, `9`).

All the Part A rules stay the same.

## 2. Class `ProductFilters`

A helper class with static methods that return conditions (`Predicate<Product>`) for filtering products:

- `static Predicate<Product> priceBetween(double min, double max)` – true for products whose **final price** is between `min` and `max`, both inclusive.
- `static Predicate<Product> minAverageRating(double minRating)` – true for products that **have ratings** and whose average rating is at least `minRating`. Products without ratings are never included.
- `static Predicate<Product> heavierThan(double kg)` – true only for **physical** products whose weight is strictly greater than `kg`. Digital products are never included.

## 3. Class `Store`: new methods

- `void printTopRated(OutputStream os, int n)` – using a `PrintWriter`, prints the `n` best-rated products. Only products with at least one rating are included. They are sorted by average rating descending, then by number of ratings descending, then by the natural order. If there are fewer than `n` rated products, prints all of them. Each line is printed with `String.format("%d. %-15s %.2f (%d)", rank, name, averageRating, ratingCount)`, with ranks starting from `1`. If `n <= 0`, throws `IllegalArgumentException`. If there are no rated products, prints only `No rated products`.
- `Map<String, DoubleSummaryStatistics> categoryStatistics()` – returns a map from each category to the statistics of the **final prices** of its products. The categories must be sorted alphabetically.
- `void printCategoryReport(OutputStream os)` – using a `PrintWriter`, prints one line per category, in alphabetical order: `String.format("%-12s count: %d, min: %.2f, max: %.2f, avg: %.2f", category, count, min, max, avg)`. If there are no products, prints only `No products`.
- `List<Product> filter(Predicate<? super Product> condition)` – returns a **new** list of the products that satisfy the condition, in natural order. If `condition` is `null`, throws `IllegalArgumentException`.

As in Part A: call `flush()` on the `PrintWriter` at the end of every printing method, but do not `close()` it.

## 4. Test class

The `StoreTest` class is given and must not be changed. The input consists of product lines, then a line `COMMANDS`, followed by commands: `SORTED`, `CATEGORY <name>`, `STATS`, `TOP <n>`, `REPORT`, `FILTER_PRICE <min> <max>`, `FILTER_RATING <min>`, `FILTER_HEAVY <kg>` and `FILTER_NULL`.

<details><summary>Given StoreTest (guessed; matches all 8 test cases)</summary>

```java
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
```
</details>

---

## Exceptions and edge cases

| Situation | Result |
|---|---|
| line with a number of fields other than 6 or 7 | `InvalidProductException` (line skipped, counted as invalid) |
| 7th field empty, rating not an `int`, rating outside `1`–`5` | `InvalidProductException` (line skipped, counted as invalid) |
| `addRating` with a rating outside `1`–`5` | `IllegalArgumentException` |
| `printTopRated` with `n <= 0` | `IllegalArgumentException` (thrown before printing anything) |
| `filter(null)` | `IllegalArgumentException` |
| `printTopRated` with no rated products | prints `No rated products` |
| `printCategoryReport` with no products | prints `No products` |

Also keep in mind:
- **Two descending keys** in `printTopRated`: reverse each of them on its own, e.g. `comparingDouble(Product::getAverageRating).reversed()` then `.thenComparing(Product::getRatingCount, Comparator.reverseOrder())`. A single `.reversed()` at the end would also flip the natural-order tie-break (`.reversed()` flips everything to its left).
- **`categoryStatistics` must be sorted by category:** use a `TreeMap`, not a `HashMap`.
- **The 7th field:** `split(";", -1)` is what makes an empty 7th field show up as `""` instead of disappearing.

---

## Test cases (real)

### Test 1

INPUT
```text
P;101;Laptop;electronics;45000;2.5;5,4,5
P;102;Mouse;electronics;800;0.2;4,4
D;103;Antivirus;software;2500;350;3,5,4
D;104;Photo Editor;software;6000;1200;5,5
P;105;Desk Lamp;home;1500;1.2
P;106;chair;home;5500;7;4
D;107;E-book Java;books;900;5;5,4,4,5
P;108;Java Book;books;1200;0.8;4
D;109;Music Pack;audio;800;2048
P;110;Headphones;electronics;3200;0.4;3,4
D;111;Atlas;books;1000;50;4,5
P;112;Atlas;books;900;0.5
COMMANDS
TOP 3
TOP 20
TOP 0
```
EXPECTED
```text
Read products: 12
Invalid lines: 0
=== TOP 3 ===
1. Photo Editor    5.00 (2)
2. Laptop          4.67 (3)
3. E-book Java     4.50 (4)
=== TOP 20 ===
1. Photo Editor    5.00 (2)
2. Laptop          4.67 (3)
3. E-book Java     4.50 (4)
4. Atlas           4.50 (2)
5. Antivirus       4.00 (3)
6. Mouse           4.00 (2)
7. Java Book       4.00 (1)
8. chair           4.00 (1)
9. Headphones      3.50 (2)
=== TOP 0 ===
IllegalArgumentException
```

### Test 2

INPUT
```text
P;101;Laptop;electronics;45000;2.5;5,4,5
P;102;Mouse;electronics;800;0.2;4,4
D;103;Antivirus;software;2500;350;3,5,4
D;104;Photo Editor;software;6000;1200;5,5
P;105;Desk Lamp;home;1500;1.2
P;106;chair;home;5500;7;4
D;107;E-book Java;books;900;5;5,4,4,5
P;108;Java Book;books;1200;0.8;4
D;109;Music Pack;audio;800;2048
P;110;Headphones;electronics;3200;0.4;3,4
D;111;Atlas;books;1000;50;4,5
P;112;Atlas;books;900;0.5
COMMANDS
REPORT
STATS
```
EXPECTED
```text
Read products: 12
Invalid lines: 0
=== REPORT ===
audio        count: 1, min: 720.00, max: 720.00, avg: 720.00
books        count: 4, min: 810.00, max: 1260.00, avg: 982.50
electronics  count: 3, min: 860.00, max: 45105.00, avg: 16408.33
home         count: 2, min: 1566.00, max: 5740.00, avg: 3653.00
software     count: 2, min: 2250.00, max: 5400.00, avg: 3825.00
=== STATS ===
Total: 12 (physical: 7, digital: 5)
Cheapest: D 109   Music Pack      audio            720.00 | 2048 MB
Most expensive: P 101   Laptop          electronics    45105.00 | 2.50 kg
Average price: 5735.92
```

### Test 3

INPUT
```text
P;101;Laptop;electronics;45000;2.5;5,4,5
P;102;Mouse;electronics;800;0.2;4,4
D;103;Antivirus;software;2500;350;3,5,4
D;104;Photo Editor;software;6000;1200;5,5
P;105;Desk Lamp;home;1500;1.2
P;106;chair;home;5500;7;4
D;107;E-book Java;books;900;5;5,4,4,5
P;108;Java Book;books;1200;0.8;4
D;109;Music Pack;audio;800;2048
P;110;Headphones;electronics;3200;0.4;3,4
D;111;Atlas;books;1000;50;4,5
P;112;Atlas;books;900;0.5
COMMANDS
FILTER_PRICE 800 2500
FILTER_PRICE 100000 200000
FILTER_RATING 4.5
FILTER_HEAVY 1
FILTER_HEAVY 10
```
EXPECTED
```text
Read products: 12
Invalid lines: 0
=== FILTER_PRICE 800 2500 ===
D 107   E-book Java     books            810.00 | 5 MB
P 102   Mouse           electronics      860.00 | 0.20 kg
D 111   Atlas           books            900.00 | 50 MB
P 112   Atlas           books            960.00 | 0.50 kg
P 108   Java Book       books           1260.00 | 0.80 kg
P 105   Desk Lamp       home            1566.00 | 1.20 kg
D 103   Antivirus       software        2250.00 | 350 MB
=== FILTER_PRICE 100000 200000 ===
No products
=== FILTER_RATING 4.5 ===
D 107   E-book Java     books            810.00 | 5 MB
D 111   Atlas           books            900.00 | 50 MB
D 104   Photo Editor    software        5400.00 | 1200 MB
P 101   Laptop          electronics    45105.00 | 2.50 kg
=== FILTER_HEAVY 1 ===
P 105   Desk Lamp       home            1566.00 | 1.20 kg
P 106   chair           home            5740.00 | 7.00 kg
P 101   Laptop          electronics    45105.00 | 2.50 kg
=== FILTER_HEAVY 10 ===
No products
```

### Test 4

INPUT
```text
P;401;Alpha;x;100;1;4,5
P;402;Beta;x;100;1;5,4
D;403;Gamma;y;200;10;5,4
P;404;Delta;y;300;2;3,5,5,5
D;405;Eps;y;400;1;4,4,5,5
P;406;BadZero;x;10;1;0,5
P;407;BadSix;x;10;1;6
P;408;BadEmpty;x;10;1;
D;409;BadText;y;10;1;4,a
P;410;Solo;z;50;0.3;5
COMMANDS
TOP 10
REPORT
FILTER_RATING 4.5
```
EXPECTED
```text
Read products: 6
Invalid lines: 4
=== TOP 10 ===
1. Solo            5.00 (1)
2. Eps             4.50 (4)
3. Delta           4.50 (4)
4. Alpha           4.50 (2)
5. Beta            4.50 (2)
6. Gamma           4.50 (2)
=== REPORT ===
x            count: 2, min: 160.00, max: 160.00, avg: 160.00
y            count: 3, min: 180.00, max: 390.00, avg: 310.00
z            count: 1, min: 110.00, max: 110.00, avg: 110.00
=== FILTER_RATING 4.5 ===
P 410   Solo            z                110.00 | 0.30 kg
P 401   Alpha           x                160.00 | 1.00 kg
P 402   Beta            x                160.00 | 1.00 kg
D 403   Gamma           y                180.00 | 10 MB
D 405   Eps             y                360.00 | 1 MB
P 404   Delta           y                390.00 | 2.00 kg
```

### Test 5

INPUT
```text
P;101;Laptop;electronics;45000;2.5;5,4,5
P;102;Mouse;electronics;800;0.2;4,4
D;103;Antivirus;software;2500;350;3,5,4
D;104;Photo Editor;software;6000;1200;5,5
P;105;Desk Lamp;home;1500;1.2
P;106;chair;home;5500;7;4
D;107;E-book Java;books;900;5;5,4,4,5
P;108;Java Book;books;1200;0.8;4
D;109;Music Pack;audio;800;2048
P;110;Headphones;electronics;3200;0.4;3,4
D;111;Atlas;books;1000;50;4,5
P;112;Atlas;books;900;0.5
P;113;Tent;travel;9000;4
COMMANDS
SORTED
CATEGORY books
CATEGORY sport
STATS
FILTER_NULL
```
EXPECTED
```text
Read products: 13
Invalid lines: 0
=== SORTED ===
D 109   Music Pack      audio            720.00 | 2048 MB
D 107   E-book Java     books            810.00 | 5 MB
P 102   Mouse           electronics      860.00 | 0.20 kg
D 111   Atlas           books            900.00 | 50 MB
P 112   Atlas           books            960.00 | 0.50 kg
P 108   Java Book       books           1260.00 | 0.80 kg
P 105   Desk Lamp       home            1566.00 | 1.20 kg
D 103   Antivirus       software        2250.00 | 350 MB
P 110   Headphones      electronics     3260.00 | 0.40 kg
D 104   Photo Editor    software        5400.00 | 1200 MB
P 106   chair           home            5740.00 | 7.00 kg
P 113   Tent            travel          9150.00 | 4.00 kg
P 101   Laptop          electronics    45105.00 | 2.50 kg
=== CATEGORY books ===
P 112   Atlas           books            960.00 | 0.50 kg
D 111   Atlas           books            900.00 | 50 MB
D 107   E-book Java     books            810.00 | 5 MB
P 108   Java Book       books           1260.00 | 0.80 kg
=== CATEGORY sport ===
Category sport not found
=== STATS ===
Total: 13 (physical: 8, digital: 5)
Cheapest: D 109   Music Pack      audio            720.00 | 2048 MB
Most expensive: P 101   Laptop          electronics    45105.00 | 2.50 kg
Average price: 5998.54
=== FILTER_NULL ===
IllegalArgumentException
```

### Test 6

INPUT
```text
P;1;Bad;none;10;1;9
COMMANDS
TOP 3
REPORT
FILTER_PRICE 0 1000
FILTER_HEAVY 0
STATS
```
EXPECTED
```text
Read products: 0
Invalid lines: 1
=== TOP 3 ===
No rated products
=== REPORT ===
No products
=== FILTER_PRICE 0 1000 ===
No products
=== FILTER_HEAVY 0 ===
No products
=== STATS ===
No products
```

### Test 7

INPUT
```text
P;101;Laptop;electronics;45000;2.5
P;102;Mouse;electronics;800;0.2
D;103;Antivirus;software;2500;350
D;104;Photo Editor;software;6000;1200
P;105;Desk Lamp;home;1500;1.2
P;106;chair;home;5500;7
D;107;E-book Java;books;900;5
P;108;Java Book;books;1200;0.8
D;109;Music Pack;audio;800;2048
P;110;Headphones;electronics;3200;0.4
D;111;Atlas;books;1000;50
P;112;Atlas;books;900;0.5
COMMANDS
SORTED
STATS
```
EXPECTED
```text
Read products: 12
Invalid lines: 0
=== SORTED ===
D 109   Music Pack      audio            720.00 | 2048 MB
D 107   E-book Java     books            810.00 | 5 MB
P 102   Mouse           electronics      860.00 | 0.20 kg
D 111   Atlas           books            900.00 | 50 MB
P 112   Atlas           books            960.00 | 0.50 kg
P 108   Java Book       books           1260.00 | 0.80 kg
P 105   Desk Lamp       home            1566.00 | 1.20 kg
D 103   Antivirus       software        2250.00 | 350 MB
P 110   Headphones      electronics     3260.00 | 0.40 kg
D 104   Photo Editor    software        5400.00 | 1200 MB
P 106   chair           home            5740.00 | 7.00 kg
P 101   Laptop          electronics    45105.00 | 2.50 kg
=== STATS ===
Total: 12 (physical: 7, digital: 5)
Cheapest: D 109   Music Pack      audio            720.00 | 2048 MB
Most expensive: P 101   Laptop          electronics    45105.00 | 2.50 kg
Average price: 5735.92
```

### Test 8

INPUT
```text
D;301;Zeta;misc;1000;10
P;302;Alpha;misc;840;0.5
D;303;Beta;misc;1000;20
P;304;Alpha;misc;840;1.0
D;305;alpha;misc;100;1
P;306;Gamma;misc;100;3
COMMANDS
SORTED
CATEGORY misc
STATS
```
EXPECTED
```text
Read products: 6
Invalid lines: 0
=== SORTED ===
D 305   alpha           misc              90.00 | 1 MB
P 306   Gamma           misc             220.00 | 3.00 kg
P 302   Alpha           misc             900.00 | 0.50 kg
P 304   Alpha           misc             900.00 | 1.00 kg
D 303   Beta            misc             900.00 | 20 MB
D 301   Zeta            misc             900.00 | 10 MB
=== CATEGORY misc ===
P 302   Alpha           misc             900.00 | 0.50 kg
P 304   Alpha           misc             900.00 | 1.00 kg
D 305   alpha           misc              90.00 | 1 MB
D 303   Beta            misc             900.00 | 20 MB
P 306   Gamma           misc             220.00 | 3.00 kg
D 301   Zeta            misc             900.00 | 10 MB
=== STATS ===
Total: 6 (physical: 3, digital: 3)
Cheapest: D 305   alpha           misc              90.00 | 1 MB
Most expensive: D 301   Zeta            misc             900.00 | 10 MB
Average price: 651.67
```
