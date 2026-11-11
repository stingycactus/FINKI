# Lab 3, Part B: FINKI Shop (ratings, top rated, category report, filter)

In this part you will extend the online store you implemented in Part A. Customers can now rate products, and the store must show the top-rated products, a per-category report, and support filtering by any condition.

**Important:** Continue working on your Part A solution. All existing functionality (`printSorted`, `printByCategory`, `printStatistics`, `toString`, the natural order) must preserve its original behavior.

## 1. Product ratings

Add a list of ratings (integers) to `Product` and the methods:

- `void addRating(int rating)` – adds a rating;
- `int getRatingCount()` – returns the number of ratings;
- `double getAverageRating()` – returns the average rating, or `0.0` if there are no ratings.

`toString()` stays unchanged.

## 2. Extended line format

A product line may now have 6 or 7 fields. The seventh field, if present, contains comma-separated ratings:

```text
TYPE;id;name;category;basePrice;extra;ratings
P;101;Laptop;electronics;45000;2.5;5,4,5
```

Lines with 6 fields are still valid (a product without ratings). In addition to the Part A rules, `createProduct` throws `InvalidProductException` if the seventh field is empty (e.g. the line ends with `;`), if a rating is not an integer, or if a rating is not between 1 and 5.

## 3. New methods in `Store`

- `void printTopRated(OutputStream os, int n)` – prints the top `n` rated products. Only products with at least one rating are considered, sorted by:
  - average rating descending,
  - number of ratings descending,
  - final price ascending,
  - id ascending.

  Each product is printed as `String.format("%d. %-15s %.2f (%d)%n", rank, name, averageRating, ratingCount)`, where `rank` starts at 1. If no product has a rating, print `No rated products`. If `n < 1`, throw `IllegalArgumentException`. Tip: build the `Comparator` with `Comparator.comparingDouble(...)`, `reversed()` and `thenComparing...`.

- `void printCategoryReport(OutputStream os)` – for each category, in alphabetical order, prints statistics of the final prices as: `String.format("%-12s count: %d, min: %.2f, max: %.2f, avg: %.2f%n", category, count, min, max, average)`. If there are no products, print `No products`. Tip: `Collectors.groupingBy` with `TreeMap::new` and `Collectors.summarizingDouble`.

- `List<Product> filter(Predicate<? super Product> condition)` – returns a new list with the products satisfying the condition, in natural order. If `condition` is `null`, throw `IllegalArgumentException`.

## 4. Test class

The `StoreTest` class is given and must not be changed. In addition to the Part A commands, it supports:

| Command | Description |
|---|---|
| `TOP n` | `printTopRated(System.out, n)` |
| `REPORT` | `printCategoryReport(System.out)` |
| `FILTER_PRICE a b` | products with final price in [a, b] |
| `FILTER_RATING r` | products with at least one rating and average rating ≥ r |
| `FILTER_HEAVY w` | physical products heavier than w kg |
| `FILTER_NULL` | calls `filter(null)` |

The filter conditions are given as lambda expressions in the test class.

## Example

Input
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
Result
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

---

# Test cases

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
