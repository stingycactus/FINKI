# NP prep: Aud 4 (lists and sets, reading from standard input, Comparable and Comparator)

**Based on:** Aud 4 only (tasks 1–4: Book, Car, F1 Race, Weather) and the posted solutions in `np-code-2025/src/class4`. It builds on Aud 3 (`Comparable`, `compareTo`, `ArrayList`) and on your Lab 1–2 code. Anything Aud 4 doesn't use is in the last section, **Extra (not covered in auds)**.

Part 1 builds one practice project, a **running club**: runners in a club, sorted and filtered several ways, then race results and a training log read from input. Each exercise extends the previous one. Part 2 has each Aud 4 task: the original text, a lab-style spec of what to implement, the given test `main`, and test inputs with verified expected output.

Setup: new IntelliJ module `prepExercise4`, everything in `src/Main.java`, only `Main` is `public`. Keep earlier test code in `main` (comment it out) so you can re-run it. For reading input: Run → Edit Configurations → **Redirect input from** → pick a `.txt` file in the module folder.

---

# 1. Concepts

## 1.1 A collection class with a `List` inside (Aud 4 tasks 1–2)

- Every Aud 4 task has the same shape: an **item class** (`Book`, `Car`) with private fields, a constructor, getters and `toString()`, plus a **collection class** (`BookCollection`, `CarCollection`) that holds a `List<Item>`.
- The field is declared as the interface and created as the class: `private List<Book> books = new ArrayList<>();`
- `getList()` in Car returns the field itself, not a copy. The test calls `sortByPrice(...)` and then prints `getList()`, so it has to see the sorted order.

**Exercise:**
1. `class Runner` with `private String name, club; private int age; private float weeklyKm;`, constructor `Runner(String name, String club, int age, float weeklyKm)`, getters, and `toString()` → `String.format("%s (%s) %d %.1fkm", name, club, age, weeklyKm)`.
2. `class RunClub` with `private List<Runner> runners`, `public void addRunner(Runner r)` and `public List<Runner> getList()`.
3. In `main`, add these 6 runners in this order and print `getList()` one per line (`float` literals need `f`: `31.5f`):
   ```text
   Ana (Vardar) 24 31.5km
   Marko (Rabotnicki) 31 42.0km
   Bojan (vardar) 24 18.5km
   Elena (Rabotnicki) 19 42.0km
   Ana (Vardar) 22 27.0km
   Ivan (Skopje) 45 12.0km
   ```
   Keep this data: every later exercise uses it. `vardar` in lowercase is on purpose.

## 1.2 `Comparator` as a class, with a tie-break (Aud 4 task 1, `BookTitleAndPriceComparator`)

- Aud 3's `Comparable` is the **one natural order**, built into the class (`compareTo`). A `Comparator<T>` is a **separate** order you pass in, so one class can be sorted many ways.
- The aud writes each order as its own class: `class X implements Comparator<Book>` with `public int compare(Book o1, Book o2)`. It returns negative if `o1` goes first, `0` if equal, positive if `o2` goes first.
- Compare by type: `Integer.compare(a, b)`, `Float.compare(a, b)`, strings with `a.compareTo(b)` or `a.compareToIgnoreCase(b)`. Don't subtract floats: `(int)(1.5f - 1.2f)` is `0`.
- **Tie-break:** compare the first field; only if it's `0`, return the second comparison.
- Sort with `list.sort(new X())` or `Collections.sort(list, new X())`. Both sort **that** list in place.
- Case-insensitive match: `a.equalsIgnoreCase(b)` (Car), or `a.compareToIgnoreCase(b) == 0` (Book). Both work.

```java
class NameAndAgeComparator implements Comparator<Runner> {
    @Override
    public int compare(Runner o1, Runner o2) {
        int byName = o1.getName().compareTo(o2.getName());
        if (byName == 0) return Integer.compare(o1.getAge(), o2.getAge());
        return byName;
    }
}
```

**Exercise:**
1. Write `NameAndAgeComparator` (above).
2. `public void printByClub(String club)`: collect the runners whose club matches (case-insensitive) into a **new** list, sort it with the comparator, then print each one.
3. `printByClub("vardar")`, `printByClub("RABOTNICKI")`, `printByClub("Pelister")`, with `--` printed after each call:
   ```text
   Ana (Vardar) 22 27.0km
   Ana (Vardar) 24 31.5km
   Bojan (vardar) 24 18.5km
   --
   Elena (Rabotnicki) 19 42.0km
   Marko (Rabotnicki) 31 42.0km
   --
   --
   ```
   The two Anas show the tie-break (same name → younger first). `Bojan (vardar)` shows the case-insensitive match.

## 1.3 Ascending and descending (Aud 4 task 2, `sortByPrice(boolean ascending)`)

- The basic aud solution writes a second comparator class with `o1`/`o2` swapped. The advanced one calls `.reversed()` on the first: `new AgeAndKmComparator().reversed()`.
- Trap: `.reversed()` flips the **whole** order, tie-break included. Car expects that: descending by price, and equal prices also by power descending.
- **Aud streams version:** `Comparator.comparing(Book::getTitle).thenComparing(Book::getPrice)` builds the same comparator with no class.
- Trap when chaining: `Comparator.comparing(r -> r.getAge()).reversed()` doesn't compile (`cannot find symbol: method getAge() ... variable r of type Object`). Chaining hides the type from the lambda. Use a method reference `Runner::getAge` or a typed lambda `(Runner r) -> r.getAge()`.

**Exercise:**
1. `AgeAndKmComparator`: by age, ties by `weeklyKm` (both ascending).
2. `public void sortByAge(boolean ascending)`: sorts `runners` itself; descending uses `.reversed()`.
3. `sortByAge(true)`, print `getList()`; then `sortByAge(false)`, print again:
   ```text
   ASC
   Elena (Rabotnicki) 19 42.0km
   Ana (Vardar) 22 27.0km
   Bojan (vardar) 24 18.5km
   Ana (Vardar) 24 31.5km
   Marko (Rabotnicki) 31 42.0km
   Ivan (Skopje) 45 12.0km
   DESC
   Ivan (Skopje) 45 12.0km
   Marko (Rabotnicki) 31 42.0km
   Ana (Vardar) 24 31.5km
   Bojan (vardar) 24 18.5km
   Ana (Vardar) 22 27.0km
   Elena (Rabotnicki) 19 42.0km
   ```
   The two age-24 runners swap, which is the reversed tie-break.
4. Rewrite the comparator with `Comparator.comparing(...).thenComparing(...)`. The output must not change.

## 1.4 Returning a new sorted list: top N and filter (Aud 4 task 1 `getCheapestN`, task 2 `filterByManufacturer`)

- "Return a list" means build a **new** `List`, fill it, sort it and return it. Don't sort the collection's own list: that silently changes the order the next method sees.
- Top N: sort a copy (`new ArrayList<>(runners)`), then take `Math.min(n, size)` items. "If there are fewer than N, return all" is exactly the `Math.min`.
- Descending by one field and ascending by another: swap the arguments for that field only, e.g. `Float.compare(o2.getWeeklyKm(), o1.getWeeklyKm())`.
- **Aud streams version** (`getCheapestNWithStreams`): `stream().sorted(cmp).limit(n).collect(Collectors.toList())`. `limit(n)` already stops at the list size, and `sorted` doesn't touch the original list.

**Exercise:**
1. `KmDescComparator`: `weeklyKm` descending, ties by name ascending.
2. `public List<Runner> getTopN(int n)` with a loop and `Math.min`.
3. `public List<Runner> filterByClub(String club)`: case-insensitive, sorted by `NameAndAgeComparator`. Write it with a stream: `filter`, `sorted`, `collect`.
4. Print `getTopN(3)`, then `getTopN(10).size()`, then `filterByClub("rabotnicki")`, then `getList()`:
   ```text
   TOP 3
   Elena (Rabotnicki) 19 42.0km
   Marko (Rabotnicki) 31 42.0km
   Ana (Vardar) 24 31.5km
   TOP 10: 6
   FILTER
   Elena (Rabotnicki) 19 42.0km
   Marko (Rabotnicki) 31 42.0km
   LIST
   Ana (Vardar) 24 31.5km
   Marko (Rabotnicki) 31 42.0km
   ...
   ```
   `LIST` must still be in insertion order, not sorted.
5. Break it: loop `i < n` instead of `Math.min` and call `getTopN(10)`: `IndexOutOfBoundsException: Index 6 out of bounds for length 6`.

## 1.5 Sets: `TreeSet` and `HashSet` (Aud 4 task 1, `BooksTest.fillCollection`)

- A `Set` holds each value **once**; `add` of a duplicate does nothing (it returns `false`).
- `HashSet`: no order. `TreeSet`: kept **sorted** (by `compareTo`, so strings alphabetically and uppercase before lowercase).
- `BooksTest` collects the categories in a `TreeSet<String>` so it can print every category once, in order.
- Trap: a `TreeSet<String>` is case-sensitive, so `Vardar` and `vardar` are **two** entries. Because `printByCategory` matches case-insensitively, the books of that group are printed **twice**. That's how the given test behaves, so your output must match it.

**Exercise:**
1. `public Set<String> getClubs()`: a `TreeSet` with every runner's club.
2. Print `getClubs()`, then loop over it: `"CLUB: " + club` and `printByClub(club)`:
   ```text
   [Rabotnicki, Skopje, Vardar, vardar]
   CLUB: Rabotnicki
   Elena (Rabotnicki) 19 42.0km
   Marko (Rabotnicki) 31 42.0km
   CLUB: Skopje
   Ivan (Skopje) 45 12.0km
   CLUB: Vardar
   Ana (Vardar) 22 27.0km
   Ana (Vardar) 24 31.5km
   Bojan (vardar) 24 18.5km
   CLUB: vardar
   Ana (Vardar) 22 27.0km
   Ana (Vardar) 24 31.5km
   Bojan (vardar) 24 18.5km
   ```
3. Switch to `HashSet` and print it: same 4 clubs, order not guaranteed.

## 1.6 Reading from standard input (Aud 4 tasks 1–2 with `Scanner`, tasks 3–4 with `BufferedReader`)

- The tests pass `System.in`, an `InputStream`. Your method takes `InputStream in`, so it also works with a file.
- **Scanner** (Book/Car tests): `while (sc.hasNextLine()) { String line = sc.nextLine(); ... }`.
- **BufferedReader** (F1/Weather solutions): `new BufferedReader(new InputStreamReader(in))`, then either `br.lines()` (a `Stream<String>`, one element per line) or `readLine()` in a loop until `null`. `readLine()` throws the checked `IOException`; `lines()` doesn't.
- The aud parses each line in a **static factory** on the item class: `static Driver createDriver(String line)` splits with `line.split("\\s+")` (one or more spaces) and calls the constructor. Book's input uses `split(":")`.
- Trap (`BooksTest`): after `nextInt()` the rest of that line is still waiting, so the next `nextLine()` returns `""`. That's why the test calls `scanner.nextLine()` once right after `nextInt()`.

```java
public void readRunners(InputStream in) {
    BufferedReader br = new BufferedReader(new InputStreamReader(in));
    runners = br.lines().map(Runner::createRunner).collect(Collectors.toList());
}
```

**Exercise:**
1. Put the 6 runners in `runners.txt` in the module folder, one per line: `Ana Vardar 24 31.5`.
2. `public static Runner createRunner(String line)` in `Runner` (`Integer.parseInt`, `Float.parseFloat`), then `readRunners` (above).
3. Replace the 6 `addRunner` calls in `main` with `club.readRunners(System.in)` and redirect input from `runners.txt`. Re-run 1.2–1.5: every output must be identical.
4. Write `readRunnersScanner(InputStream in)` with a `Scanner` loop and `addRunner`. Same output again.

## 1.7 `Comparable` on parsed times (Aud 4 task 3, `Driver`)

- The natural order of a result is "best time first", so `RaceResult implements Comparable<RaceResult>`. Then `Collections.sort(results)` needs no comparator.
- Times like `4:49` are strings. To compare them, convert to a number (`m * 60 + s` seconds). Keep the original string for printing, because the output must use "the same format as it was read".
- Trap: comparing the strings themselves. `"10:02".compareTo("9:59")` is negative (`'1' < '9'`), so 10 minutes would beat 9.
- Best of several: loop and keep the smallest, comparing by **seconds**.

**Exercise:**
1. `class RaceResult implements Comparable<RaceResult>` with `String name`, `List<String> splits`, a `static RaceResult createResult(String line)` and `private static int toSeconds(String split)` (`split(":")`).
2. `public String getBestSplit()` (the smallest by seconds), and `compareTo` comparing the best splits' seconds with `Integer.compare`.
3. In `RunClub`: `List<RaceResult> results` and `void readRace(InputStream in)`. Put this in `race.txt`:
   ```text
   Ana 4:55 5:02 4:49
   Marko 4:40 4:52 4:47
   Ivan 10:15 9:58 10:02
   Elena 4:41 4:39 4:50
   ```
   After `Collections.sort`, print `name + " " + getBestSplit()`:
   ```text
   Elena 4:39
   Marko 4:40
   Ana 4:49
   Ivan 9:58
   ```
4. Break it: pick the best with `s.compareTo(best) < 0` instead of seconds. Ivan's best becomes `10:02`.

## 1.8 Writing to an `OutputStream` with fixed widths (Aud 4 task 3 `printSorted`, task 4 `writeDailyStats`)

- The method gets `OutputStream out` (the test passes `System.out`). Wrap it: `PrintWriter pw = new PrintWriter(out);`, then `pw.println(...)`.
- **Always `pw.flush()` at the end.** `PrintWriter` buffers, so without `flush` nothing is printed.
- Don't `close()` it. That also closes `System.out`, and every print after it silently disappears. The posted F1 solution closes it; it only works because nothing prints afterwards.
- Widths: `%-10s` = 10 characters, left-aligned; `%10s` = 10 characters, right-aligned; `%6.2f` = 6 characters in total with 2 decimals; `%3d` = an int in 3 characters.

**Exercise:**
1. `public void printRace(OutputStream out)`: sort, then print each result as `String.format("%d. %-10s%8s", rank, name, bestSplit)`, ranks from 1.
2. Call `printRace(System.out)` with `race.txt` (the spaces matter):
   ```text
   1. Elena         4:39
   2. Marko         4:40
   3. Ana           4:49
   4. Ivan          9:58
   ```
3. Break it twice: remove `flush()` (nothing is printed); then add `pw.close()` and a `System.out.println("after")` in `main` after the call (`after` never appears).

## 1.9 Converting units and min/max/avg statistics (Aud 4 task 4, `DailyTemperatures`)

- Each line is a key followed by an unknown number of values, each with a unit suffix. Parse from index 1 to `parts.length`.
- **Store everything in one base unit** (`Double`, as the aud's note says). Convert only when printing, into a **new** list. Never overwrite the stored values: the posted solution does, so printing in the other unit twice converts twice.
- Remove the suffix before parsing: `s.substring(0, s.length() - 2)`. Trap: Java parses `"68F"` as `68.0` (an `F` suffix means float), but `"23C"` throws `NumberFormatException`. Always cut the suffix.
- Min/max/avg: a loop with `Math.min`/`Math.max` and a sum, or `Collections.min(list)` / `Collections.max(list)`.
- Sort by the key: make the line class `Comparable` by day, then sort a copy.

**Exercise:**
1. `class DayLog implements Comparable<DayLog>`: `int day`, `List<Double> km`, `static DayLog createDayLog(String line)`. Values are `5km` or `3.1mi`, and miles are stored as km (`× 1.609344`). `compareTo` is by day.
2. `public String stats(char unit)` (`'K'` or `'M'`): convert into a new list, then return `String.format("%3d: Count: %2d Min: %6.2f%s Max: %6.2f%s Avg: %6.2f%s", ...)` with `km`/`mi` as the unit.
3. In `RunClub`: `readLog(InputStream)` and `writeLogStats(OutputStream out, char unit)`, sorted by day (1.8 rules). `log.txt`:
   ```text
   12 5km 3.1mi 10km
   3 8.5km
   7 2mi 4mi
   ```
   Print with `'K'`, then `'M'`, then `'M'` again:
   ```text
   === km ===
     3: Count:  1 Min:   8.50km Max:   8.50km Avg:   8.50km
     7: Count:  2 Min:   3.22km Max:   6.44km Avg:   4.83km
    12: Count:  3 Min:   4.99km Max:  10.00km Avg:   6.66km
   === mi ===
     3: Count:  1 Min:   5.28mi Max:   5.28mi Avg:   5.28mi
     7: Count:  2 Min:   2.00mi Max:   4.00mi Avg:   3.00mi
    12: Count:  3 Min:   3.10mi Max:   6.21mi Avg:   4.14mi
   === mi again ===
   (same as === mi ===)
   ```
4. Break it: in `stats`, overwrite `km` with the converted list. The second `mi` block shrinks: day 3 shows `3.28mi`.

---

# 2. The auds

After Part 1, every Aud 4 mechanic is already in your practice project. Each task below lists what to implement, the given test `main` (from the course repo, without `package`), and verified test cases. Run each in its own module or file, with only the test class `public`.

## Aud 4 task 1: Book (= 1.1, 1.2, 1.4, 1.5, 1.6)

> Write a class for a book Book which stores: title, category, and price.
>
> Implement a constructor with the following arguments: Book(String title, String category, float price).
>
> Then write a class BookCollection which stores a collection of books. In this class, the following methods should be implemented:
>
> - public void addBook(Book book) – adds a book to the collection
> - public void printByCategory(String category) – prints all books from the given category (the string comparison should be case-insensitive), sorted by the book title (if the title is the same, sort by price).
> - public List\<Book> getCheapestN(int n) – returns a list of the N cheapest books (if there are fewer than N books in the collection, return all).

**In class `Book` implement:**
- `public Book(String title, String category, float price)`
- getters `getTitle()`, `getCategory()`, `getPrice()`
- `public String toString()` → `String.format("%s (%s) %.2f", title, category, price)`

**In class `BookCollection` implement:**
- `public BookCollection()` – creates an empty list.
- `public void addBook(Book book)`
- `public void printByCategory(String category)` – matching category, case-insensitive; sorted by title, then price; one `toString()` per line.
- `public List<Book> getCheapestN(int n)` – a **new** list sorted by price, ties by title. At most `n` books, all of them if there are fewer. Doesn't reorder the collection.

<details><summary>Given test: BooksTest</summary>

```java
import java.util.*;

public class BooksTest {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine();
        BookCollection booksCollection = new BookCollection();
        Set<String> categories = fillCollection(scanner, booksCollection);
        System.out.println("=== PRINT BY CATEGORY ===");
        for (String category : categories) {
            System.out.println("CATEGORY: " + category);
            booksCollection.printByCategory(category);
        }
        System.out.println("=== TOP N BY PRICE ===");
        print(booksCollection.getCheapestN(n));
    }

    static void print(List<Book> books) {
        for (Book book : books) {
            System.out.println(book);
        }
    }

    static TreeSet<String> fillCollection(Scanner scanner, BookCollection collection) {
        TreeSet<String> categories = new TreeSet<String>();
        while (scanner.hasNext()) {
            String line = scanner.nextLine();
            String[] parts = line.split(":");
            Book book = new Book(parts[0], parts[1], Float.parseFloat(parts[2]));
            collection.addBook(book);
            categories.add(parts[1]);
        }
        return categories;
    }
}
```
</details>

INPUT 1
```text
3
Clean Code:Programming:39.99
Dune:SciFi:12.50
Refactoring:programming:45.00
Foundation:SciFi:9.99
Clean Code:Programming:29.99
Neuromancer:SciFi:12.50
```
EXPECTED 1
```text
=== PRINT BY CATEGORY ===
CATEGORY: Programming
Clean Code (Programming) 29.99
Clean Code (Programming) 39.99
Refactoring (programming) 45.00
CATEGORY: SciFi
Dune (SciFi) 12.50
Foundation (SciFi) 9.99
Neuromancer (SciFi) 12.50
CATEGORY: programming
Clean Code (Programming) 29.99
Clean Code (Programming) 39.99
Refactoring (programming) 45.00
=== TOP N BY PRICE ===
Foundation (SciFi) 9.99
Dune (SciFi) 12.50
Neuromancer (SciFi) 12.50
```

INPUT 2 (fewer books than N)
```text
10
Dune:SciFi:12.50
Foundation:SciFi:9.99
```
EXPECTED 2
```text
=== PRINT BY CATEGORY ===
CATEGORY: SciFi
Dune (SciFi) 12.50
Foundation (SciFi) 9.99
=== TOP N BY PRICE ===
Foundation (SciFi) 9.99
Dune (SciFi) 12.50
```

**Posted solution bugs (verified):**
- `getCheapestN` loops `i < n`, so INPUT 2 crashes with `IndexOutOfBoundsException: Index 2 out of bounds for length 2`. That breaks the "return all" rule.
- `getCheapestN` sorts `books` itself, so the collection's order changes.
- `printByCategoryWithStreams` uses `equals` (case-sensitive), unlike the spec.

## Aud 4 task 2: Car (= 1.1, 1.3, 1.4)

> Write a class for a car Car which stores: manufacturer, model, price, and power. Implement a constructor with the following arguments: Car(String manufacturer, String model, int price, float power).
>
> Then write a class CarCollection which stores a collection of cars. In this class, the following methods should be implemented:
>
> - public void addCar(Car car) – adds a car to the collection
> - public void sortByPrice(boolean ascending) – sorts the collection by car price (in ascending order if the argument ascending is true, otherwise in descending order). If the car prices are the same, sorting should be done by their power.
> - public List\<Car> filterByManufacturer(String manufacturer) – returns a list of cars from a given manufacturer (the comparison is case-insensitive). The cars in this list should be sorted by model in ascending order.
> - public List\<Car> getList() – returns the list of cars from the collection.

**In class `Car` implement:**
- `public Car(String manufacturer, String model, int price, float power)`
- getters for all four
- `public String toString()` → `String.format("%s %s (%.0fKW) %d", manufacturer, model, power, price)`

**In class `CarCollection` implement:**
- `public void addCar(Car car)`
- `public void sortByPrice(boolean ascending)` – sorts the collection's own list by price, ties by power. Descending reverses both.
- `public List<Car> filterByManufacturer(String manufacturer)` – a new list, case-insensitive match, sorted by model ascending.
- `public List<Car> getList()` – the collection's list (in its current, possibly sorted, order).

<details><summary>Given test: CarTest</summary>

```java
import java.util.List;
import java.util.Scanner;

public class CarTest {
    public static void main(String[] args) {
        CarCollection carCollection = new CarCollection();
        String manufacturer = fillCollection(carCollection);
        carCollection.sortByPrice(true);
        System.out.println("=== Sorted By Price ASC ===");
        print(carCollection.getList());
        carCollection.sortByPrice(false);
        System.out.println("=== Sorted By Price DESC ===");
        print(carCollection.getList());
        System.out.printf("=== Filtered By Manufacturer: %s ===\n", manufacturer);
        List<Car> result = carCollection.filterByManufacturer(manufacturer);
        print(result);
    }

    static void print(List<Car> cars) {
        for (Car c : cars) {
            System.out.println(c);
        }
    }

    static String fillCollection(CarCollection cc) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] parts = line.split("\\s+");
            if (parts.length == 1)
                return line;
            String manufacturer = parts[0];
            String model = parts[1];
            int price = Integer.parseInt(parts[2]);
            float power = Float.parseFloat(parts[3]);
            cc.addCar(new Car(manufacturer, model, price, power));
        }
        return "";
    }
}
```
</details>

The last line (a single word) is the manufacturer to filter by.

INPUT
```text
Audi A4 30000 110
BMW X5 55000 195
audi Q7 60000 170
Toyota Corolla 22000 90
BMW 320d 30000 140
Audi A3 30000 85
audi
```
EXPECTED
```text
=== Sorted By Price ASC ===
Toyota Corolla (90KW) 22000
Audi A3 (85KW) 30000
Audi A4 (110KW) 30000
BMW 320d (140KW) 30000
BMW X5 (195KW) 55000
audi Q7 (170KW) 60000
=== Sorted By Price DESC ===
audi Q7 (170KW) 60000
BMW X5 (195KW) 55000
BMW 320d (140KW) 30000
Audi A4 (110KW) 30000
Audi A3 (85KW) 30000
Toyota Corolla (90KW) 22000
=== Filtered By Manufacturer: audi ===
Audi A3 (85KW) 30000
Audi A4 (110KW) 30000
audi Q7 (170KW) 60000
```

Both posted solutions (basic: two comparator classes; advanced: `.reversed()` + streams) give this exact output.

## Aud 4 task 3: Race (= 1.6, 1.7, 1.8)

> Implement a class F1Race that reads from an input stream (standard input, file, etc.) data about the lap times of the last 3 laps for several F1 race drivers. The data is in the following format: Driver_name lap1 lap2 lap3, where each lap is in the format mm:ss:nnn, where mm = minutes, ss = seconds, and nnn = milliseconds (thousandths of a second).
>
> Example: Vetel 1:55:523 1:54:987 1:56:134.
>
> Your task is to implement the following methods:
>
> - F1Race() – default constructor
> - void readResults(InputStream inputStream) – method for reading the data
> - void printSorted(OutputStream outputStream) – method that prints all drivers sorted by their best time (the shortest time among their last 3 laps) in the format Driver_name best_lap, with 10 spaces for the driver's name (left-aligned) and 10 spaces for the best lap time (right-aligned). The time should be printed in the same format as it was read.

**In class `Driver implements Comparable<Driver>` implement:**
- `public static Driver createDriver(String line)` – name + 3 lap strings.
- a lap-to-milliseconds helper: `m * 60 * 1000 + s * 1000 + ms`.
- `public String getBestLap()` – the original string of the fastest lap.
- `public int compareTo(Driver other)` – by best lap in milliseconds.

**In class `F1Race` implement:**
- `public F1Race()`
- `public void readResults(InputStream inputStream)` – one driver per line.
- `public void printSorted(OutputStream outputStream)` – sorted, each line `String.format("%d. %-10s%10s", rank, name, bestLap)` with ranks from 1. The rank prefix comes from the posted solution; the aud text doesn't mention it. `flush()`, don't `close()`.

<details><summary>Given test: F1Test</summary>

```java
public class F1Test {
    public static void main(String[] args) {
        F1Race f1Race = new F1Race();
        f1Race.readResults(System.in);
        f1Race.printSorted(System.out);
    }
}
```
</details>

INPUT
```text
Vetel 1:55:523 1:54:987 1:56:134
Alonso 1:56:000 1:55:111 1:54:999
Hamilton 1:54:312 1:55:100 1:54:950
Verstappen 1:53:999 1:56:500 1:55:000
```
EXPECTED
```text
1. Verstappen  1:53:999
2. Hamilton    1:54:312
3. Vetel       1:54:987
4. Alonso      1:54:999
```
`Verstappen` is exactly 10 characters, so `%-10s` adds no space after it, and the two spaces before the time come from `%10s`.

**Posted solution bugs (verified):**
- `laps.getLast()` only exists from Java 21, so it **doesn't compile on Java 11** (`cannot find symbol: method getLast()`). Use `laps.get(laps.size() - 1)`.
- `printSorted` takes a `PrintStream`, not the `OutputStream` from the text. It still works with `System.out`, but `OutputStream` is what the spec says.
- `printSorted` calls `writer.close()`, which closes `System.out` (see 1.8).
- `printSortedWithStreams` numbers from `0.`, not `1.`.

## Aud 4 task 4: Weather (= 1.6, 1.8, 1.9)

> Implement a class DailyTemperatures that reads air temperatures (integer values) for different days of the year (numbers from 1 to 366). The temperatures for one day are in one line in the following format (example): 137 23C 15C 28C. The first number represents the day of the year, followed by an unknown number of temperature readings for that day, in either Celsius (C) or Fahrenheit (F).
>
> In this class, implement the following methods:
>
> - DailyTemperatures() – default constructor
> - void readTemperatures(InputStream inputStream) – method for reading data from the input stream
> - void writeDailyStats(OutputStream outputStream, char scale) – method for printing daily statistics (total measurements, minimum temperature, maximum temperature, average temperature) for each day, sorted in ascending order by day. The second argument scale determines in which scale the temperatures are printed: C – Celsius, F – Fahrenheit. The format for printing the statistics for a day is: [day]: Count: [total measurements - 3 spaces] Min: [min temperature] Max: [max temperature] Avg: [average]
>
> The minimum, maximum, and average temperatures are printed with 6 characters in total, of which 2 are decimal places, followed by the temperature scale (C/F).
>
> Conversion formulas: From Celsius to Fahrenheit: (T * 9) / 5 + 32. From Fahrenheit to Celsius: ((T - 32) * 5) / 9.
>
> Note: To achieve the same precision as in the reference results, for calculating the average and conversions between scales, temperatures should be stored as type Double.

**In class `DailyMeasurement implements Comparable<DailyMeasurement>` implement:**
- `public static DailyMeasurement createMeasurement(String line)` – the day, then every reading converted to **Celsius** and stored as `Double`.
- `public int compareTo(DailyMeasurement o)` – by day.
- a stats method that converts into a **new** list when the scale is `F` and returns `String.format("%3d: Count: %3d Min: %6.2f%c Max: %6.2f%c Avg: %6.2f%c", day, count, min, scale, max, scale, avg, scale)`.

**In class `DailyTemperatures` implement:**
- `public DailyTemperatures()`
- `public void readTemperatures(InputStream inputStream)`
- `public void writeDailyStats(OutputStream outputStream, char scale)` – sorted by day, `flush()` at the end.

<details><summary>Given test: DailyTemperatureTest</summary>

```java
public class DailyTemperatureTest {
    public static void main(String[] args) {
        DailyTemperatures dailyTemperatures = new DailyTemperatures();
        dailyTemperatures.readTemperatures(System.in);
        System.out.println("=== Daily temperatures in Celsius (C) ===");
        dailyTemperatures.writeDailyStats(System.out, 'C');
        System.out.println("=== Daily temperatures in Fahrenheit (F) ===");
        dailyTemperatures.writeDailyStats(System.out, 'F');
    }
}
```
</details>

INPUT
```text
137 23C 15C 28C
12 50F 41F 45F
300 -5C 0C
45 77F
```
EXPECTED
```text
=== Daily temperatures in Celsius (C) ===
 12: Count:   3 Min:   5.00C Max:  10.00C Avg:   7.41C
 45: Count:   1 Min:  25.00C Max:  25.00C Avg:  25.00C
137: Count:   3 Min:  15.00C Max:  28.00C Avg:  22.00C
300: Count:   2 Min:  -5.00C Max:   0.00C Avg:  -2.50C
=== Daily temperatures in Fahrenheit (F) ===
 12: Count:   3 Min:  41.00F Max:  50.00F Avg:  45.33F
 45: Count:   1 Min:  77.00F Max:  77.00F Avg:  77.00F
137: Count:   3 Min:  59.00F Max:  82.40F Avg:  71.60F
300: Count:   2 Min:  23.00F Max:  32.00F Avg:  27.50F
```

**Posted solution bugs (verified):**
- Its format has no `:` after the day (`137 Count:`), but the text says `[day]: Count:`. The original course version of this task prints `%3d: Count:`, as above.
- `getMeasurementStats` overwrites the stored list with Fahrenheit values. Calling `writeDailyStats(out, 'F')` twice prints `138.20F` instead of `59.00F` for day 137, and a `'C'` call after that prints Fahrenheit numbers labelled `C`.
- It picks the scale from the **first** reading of a line and splits all readings by it. On `5 20C 68F` it reads `68F` as 68 °C, with no error, because `Double.parseDouble("68F")` is `68.0`.

---

# 3. Checklist for Aud 4-style tasks

- Item class: private fields, constructor, getters, `toString()` in the exact test format.
- `List` field created in the constructor or at the declaration.
- Comparators: compare the first field; on `0`, the tie-break. `Integer.compare`/`Float.compare`, not subtraction for floats.
- "Return a list": a new list. "Sort the collection": sort the field itself.
- "Fewer than N": `Math.min(n, size)` or `limit(n)`.
- Case-insensitive: `equalsIgnoreCase`.
- Reading: `BufferedReader` + `lines()` or `Scanner` + `hasNextLine()`; a static `createX(String line)` factory.
- Writing: `PrintWriter(out)`, exact widths, `flush()`, no `close()`.
- Parsed values (times, temperatures): compare as numbers, print the original or formatted string, store in one unit, never overwrite on print.
- Java 11: `Collectors.toList()`, no `getLast()`.

---

# Extra (not covered in auds)

Only if there's time. These are common in this kind of task but Aud 4 doesn't use them:

- `new TreeSet<>(String.CASE_INSENSITIVE_ORDER)` treats `Vardar` and `vardar` as one entry. That fixes the duplicate group from 1.5, but the Book test expects the case-sensitive output, so don't use it there.
- `Comparator.comparingInt(Runner::getAge)` / `comparingDouble(...)` avoid boxing, and `Comparator.reverseOrder()` gives the reverse of the natural order.
- `DoubleSummaryStatistics stats = list.stream().mapToDouble(Double::doubleValue).summaryStatistics();` gives `getMin()`, `getMax()`, `getAverage()`, `getCount()` in one pass.
- `TreeMap<Integer, List<Double>>`: if the same day can appear on several lines, merge them under one key, already sorted by day.
- `list.subList(0, Math.min(n, list.size()))` gives the top N in one call. It's a view, so wrap it in `new ArrayList<>(...)` before returning.

Sources: Aud 4 text; course code `np-code-2025/src/class4` (https://github.com/atodorovska/np-code-2025/tree/main/src/class4).
