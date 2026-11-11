# NP prep: Aud 3 (generics, generic methods, generic data structures)

**Based on:** Aud 3 only (tasks 1–5: Box, Priority Queue, standard deviation, ArrayList vs arrays, ExecuteAndSort). It builds on what you know from Auds 1–2 (interfaces, lambdas, `Function`) and from the Warehouse lab (`Pair<K, V>`, `Container<T extends Product>`). Anything Aud 3 doesn't use is in the last section, **Extra (not covered in auds)**.

Part 1 builds one practice project, a small **raffle**: a `Bag` you draw prizes from, prize rankings and some statistics. Each exercise extends the previous one. Part 2 maps every Aud 3 task to the exercises that already cover it, with test inputs and expected outputs.

Setup: new IntelliJ module `prepExercise3`, everything in `CarTest.java`, only `Main` is `public`. Keep earlier test code in `main` (comment it out) so you can re-run it.

---

# 1. Concepts

## 1.1 Generic class with an `ArrayList` inside (Aud 3 tasks 1 and 4)

- Same syntax as your `Pair<K, V>` / `Container<T>`: `class Bag<T>`, and inside, `T` is used like a real type.
- Aud 3 stores items in an `ArrayList<T>` instead of an array. Methods you need: `add(x)`, `get(i)`, `size()`, `isEmpty()`, `remove(i)`.
- **ArrayList vs array (task 4):** an array has a fixed length, while an `ArrayList` grows by itself (internally it's an array it copies when full, like your `Garage.park`). Why not always use `ArrayList`:
  - it's slower than an array
  - no `[]` syntax: `list.get(i)`, not `list[i]`
  - the element type must be a class: `ArrayList<Integer>`, never `ArrayList<int>`
- `ArrayList`'s `toString()` already prints `[a, b, c]`.

```java
import java.util.ArrayList;

private ArrayList<T> items = new ArrayList<>();
```

**Exercise:**
1. `class Bag<T>` with a private `ArrayList<T> items`, and `void add(T item)`, `int size()`, `boolean isEmpty()`, `toString()` returning `items.toString()`.
2. Test with a `Bag<String>` (`Ana`, `Bob`, `Cleo`) and an empty `Bag<Integer>`, printing `bag + " " + size() + " " + isEmpty()`:
   ```text
   [Ana, Bob, Cleo] 3 false
   [] 0 true
   ```
3. Break it: try `Bag<int>` and read the error ("unexpected type ... required: reference").

## 1.2 Random choice (Aud 3 task 1)

- `import java.util.Random;`, then `random.nextInt(n)` returns a random `int` from `0` to `n - 1`. So `items.get(random.nextInt(items.size()))` picks a random item.
- The aud creates `new Random()` inside `drawItem()` on every call. It works, but one `Random` field created once is the usual way.
- `list.remove(int index)` removes **and returns** that element.
- **Trap with `ArrayList<Integer>`:** `remove(2)` means "remove index 2", not "remove the value 2". For `[10, 2, 30]`, `remove(2)` gives `[10, 2]`, while `remove(Integer.valueOf(2))` gives `[10, 30]`.

**Exercise:**
1. Add a `Random random` field to `Bag`.
2. `T draw()`: a random item **without** removing it. `null` if the bag is empty.
3. `T take()`: a random item that's **removed** (use the return value of `remove(index)`). `null` if empty.
4. Test (the order is random, so check properties):
   - `draw()` 10 times on `[Ana, Bob, Cleo]`: always one of the three, and `size()` stays `3`.
   - `take()` until `isEmpty()`: you get each name exactly once, then `take()` returns `null`.

## 1.3 Generic methods and `? extends Number` (Aud 3 task 3)

- A **generic method** declares its own type variable **before the return type**: `static <T> T first(List<T> list)`. It works in any class, generic or not.
- **Bounded type:** `<T extends Number>` means `T` is `Integer`, `Double`, or another `Number` subclass, so you can call `x.doubleValue()` on it. Same idea as your `Container<T extends Product>`.
- **Wildcard (the aud's way):** `ArrayList<? extends Number>` means "a list of some `Number` type" without naming it. Use it when you don't need the name `T` anywhere else.
- Why not `ArrayList<Number>`? An `ArrayList<Integer>` is **not** an `ArrayList<Number>`, the same rule as `Container<Food>` not being a `Container<Product>`.

```java
static double mean(List<? extends Number> list) { ... n.doubleValue() ... }   // wildcard
static <T extends Number> double sum(List<T> list) { ... }                     // named bound
```

**Exercise:**
1. Add `List<T> getItems()` to `Bag`, returning a **copy**: `new ArrayList<>(items)`.
2. `class Stats` with `static double mean(List<? extends Number> list)` and `static <T extends Number> double sum(List<T> list)`. Both loop and use `doubleValue()`.
3. Test: a `Bag<Integer>` with `2 4 4 4 5 5 7 9` gives mean `5.0` and sum `40.0`. A `Bag<Double>` with `1.5 2.5` gives `2.0` and `4.0`.
4. Break it:
   - `Stats.mean(names.getItems())` (Strings) doesn't compile.
   - `mean` of an empty list prints `NaN` (`0.0 / 0`). Remember this for task 3.

## 1.4 Keeping a list sorted while inserting (Aud 3 task 2)

- `list.add(i, x)` inserts at index `i` and shifts the rest right. `list.remove(0)` removes the first element.
- Priority-queue idea from the aud: keep the list **sorted by priority, highest first**. To add, walk until you find a lower priority, then insert there. To remove, take index `0`.
- The aud uses **two parallel lists** (`queue` for items, `priorities` for numbers). Here you'll use one list of small objects that hold both, like your `Pair`.
- **Trap:** `<` vs `<=` decides the order of **equal** priorities. Stopping at the first *lower* priority keeps ties in the order they were added (first in, first out).

**Exercise:**
1. `class Entry<T>` with `private final T item` and `private final int priority`, getters, and `toString()` returning `item(priority)`.
2. `class RankedBag<T>` with an `ArrayList<Entry<T>> entries`:
   - `void add(T item, int priority)`: find the first index whose priority is **lower** than the new one, and insert there (at the end if none).
   - `T removeTop()`: remove and return the item at index `0`, or `null` if empty.
   - `List<Entry<T>> getEntries()` (a copy) and `toString()`.
3. Test: add `bronze 1`, `gold 10`, `silver 5`, `gold2 10`:
   ```text
   [gold(10), gold2(10), silver(5), bronze(1)]
   gold gold2 silver bronze null
   ```
   The second line is five `removeTop()` calls.
4. Change your comparison so ties flip (`gold2` before `gold`), see it, and change it back.

## 1.5 `Comparable` and `compareTo` (Aud 3 task 5, `Student`)

- `class X implements Comparable<X>` promises `int compareTo(X o)`: **negative** if `this` comes first (is "smaller"), **0** if equal, **positive** if `this` is "bigger".
- `Integer`, `Double` and `String` already implement it (numbers by value, strings alphabetically).
- The aud's `Student` compares with a `Comparator`: `Comparator.comparing(Student::labAssistantPoints).thenComparing(Student::average).compare(this, o)`. That means compare by points, and on a tie by average.
- Bound a generic method by it: `<T extends Comparable<T>>` lets you call `a.compareTo(b)` on any `T`.

```java
class Entry<T> implements Comparable<Entry<T>> {
    @Override
    public int compareTo(Entry<T> o) {
        return Comparator.comparing(Entry<T>::getPriority).compare(this, o);
    }
}
```

Write `Entry<T>::getPriority`, not `Entry::getPriority`. The plain version doesn't compile inside a generic class ("cannot infer type-variable(s)").

**Exercise:**
1. Make `Entry<T>` implement `Comparable<Entry<T>>`, comparing by `priority`.
2. Test: `a(3).compareTo(b(7))` is negative, `b(7).compareTo(a(3))` is positive, and `a(3).compareTo(c(3))` is `0`.
3. Add `static <T extends Comparable<T>> T maxOf(List<T> list)` to `Stats`: `null` for an empty list, otherwise keep the best with `compareTo(...) > 0`.
4. Test (one method, three types):
   - `maxOf(scores.getItems())` gives `9`
   - `maxOf(Arrays.asList("pear", "apple", "zebra", "kiwi"))` gives `zebra`
   - `maxOf(ranked.getEntries())` gives `gold(10)` (for `bronze 1`, `gold 10`, `silver 5`)

## 1.6 Generic method + `Function` + sorting with streams (Aud 3 task 5, `execute`)

- `execute` combines it all: a generic method `<E extends Comparable>`, a list, and a `Function<E, E>` (from Aud 2) applied to every element. The result is sorted.
- The aud writes it with **streams**, which are new syntax. Read the chain left to right:
  - `list.stream()` turns the list into a stream of its elements
  - `.map(f)` applies the function to each one (like your `mapToLabels`, but keeping the type)
  - `.sorted()` sorts by `compareTo` (ascending), and `.sorted(Comparator.reverseOrder())` sorts descending
  - `.collect(Collectors.toList())` turns the stream back into a `List`
- Needs `import java.util.stream.Collectors;` and `import java.util.function.Function;`.
- **Trap: change vs create.** The aud's student lambdas **modify** the object they get (`a.id = a.id + "_FCSE"; return a;`), so the original list's students change too. A lambda that returns a **new** object leaves the original untouched.

```java
return list.stream().map(f).sorted().collect(Collectors.toList());
```

**Exercise:**
1. `class Transform` with `static <E extends Comparable<E>> List<E> applyAndSort(List<E> list, Function<E, E> f)`, sorting **ascending** (the aud task is descending).
2. Test on integers: `applyAndSort(Arrays.asList(5, 120, 30), x -> x < 100 ? x + 1 : x - 1)` gives `[6, 31, 119]`.
3. Test on the ranked entries (`gold 10`, `silver 5`, `bronze 1`) with `e -> new Entry<>(e.getItem().toUpperCase(), e.getPriority() * 2)`:
   ```text
   [BRONZE(2), SILVER(10), GOLD(20)]
   ```
   Print the original list afterwards. It's unchanged (`[gold(10), silver(5), bronze(1)]`), because the lambda created new entries.
4. Break it: remove `extends Comparable<E>` from the method.
   - Plain `.sorted()` still compiles. Call it on a class that isn't `Comparable` and it crashes at runtime: `ClassCastException: ... cannot be cast to class java.lang.Comparable`.
   - With `.sorted(Comparator.reverseOrder())`, it doesn't even compile ("inference variable T has incompatible bounds"). The bound is what makes the descending sort in task 5 legal.

---

# 2. The auds

Try each task yourself first, then compare with the posted solution. Run with Java 11 if NP's checker is Java 11 (`.toList()` on streams is Java 16, so use `Collectors.toList()`).

## 2.1 Task 1: Box (= 1.1, 1.2)

Generic `Box<T>` with `add`, `isEmpty` and `drawItem()` (random item, `null` if empty), plus a `main` with a `Box<String>` and a `Box<Integer>`. This is your `Bag` without `take`.

Test:
- an empty box's `drawItem()` prints `null`
- drawing many times from `Dexter, Seinfeld, Barney, Sheldon, Costanza, Hank` only ever prints those names
- `drawItem()` doesn't remove anything (`isEmpty()` stays `false`)

Sample `main` (the draws are random, so run it a few times):

```java
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
```

## 2.2 Task 2: Priority Queue (= 1.4)

`PriorityQueue<T>` on `ArrayList`: `add(item, priority)`, and `remove()` returning the highest priority (`null` if empty).

- **Posted solution bug:** its `main` adds `X 0`, `Y 1`, `Z 3` but the comments say it prints X, Z, Y. It actually prints:
  ```text
  Z
  Y
  X
  ```
  The comments belong to the statement's example (`X 10`, `Y 1`, `Z 3`), not to this `main`.
- **Name clash:** `import java.util.PriorityQueue;` makes Java use **its** class, not yours: `error: method add in class PriorityQueue<E> cannot be applied to given types`. `import java.util.*;` is fine, because your own class wins.

Tests (`remove()` calls, in order):

| Added | Removed |
|---|---|
| `X 10`, `Y 1`, `Z 3` (statement) | `X Z Y null` |
| `A 1`, `B 2`, `C 3` (ascending) | `C B A` |
| `C 3`, `B 2`, `A 1` (descending) | `C B A` |
| `first 5`, `second 5`, `low 1`, `third 5` (ties) | `first second third low` |

Sample `main` (runs all four rows, plus an `Integer` queue):

```java
public static void main(String[] args) {
    PriorityQueue<String> q = new PriorityQueue<>();
    q.add("X", 10);
    q.add("Y", 1);
    q.add("Z", 3);
    System.out.println(q.remove() + " " + q.remove() + " " + q.remove() + " " + q.remove());   // X Z Y null

    q.add("A", 1);
    q.add("B", 2);
    q.add("C", 3);
    System.out.println(q.remove() + " " + q.remove() + " " + q.remove());                      // C B A

    q.add("C", 3);
    q.add("B", 2);
    q.add("A", 1);
    System.out.println(q.remove() + " " + q.remove() + " " + q.remove());                      // C B A

    q.add("first", 5);
    q.add("second", 5);
    q.add("low", 1);
    q.add("third", 5);
    System.out.println(q.remove() + " " + q.remove() + " " + q.remove() + " " + q.remove());   // first second third low

    PriorityQueue<Integer> nums = new PriorityQueue<>();
    nums.add(100, 2);
    nums.add(200, 9);
    System.out.println(nums.remove() + " " + nums.remove());                                   // 200 100
}
```

## 2.3 Task 3: Standard deviation (= 1.3)

`MyMathClass.standardDeviation(ArrayList<? extends Number>)`: first the mean, then the square root of the average squared distance from it (divide by `N`, not `N - 1`).

| List | Output (`%.2f`) |
|---|---|
| `1 10 20 30 40 50` (the aud's `main`) | `STD: 16.84` |
| `3.4` | `STD: 0.00` |
| `2 4 4 4 5 5 7 9` (your 1.3 bag) | `STD: 2.00` |
| empty list | `STD: NaN` (the posted solution doesn't guard it) |

Sample `main` (needs `import java.util.Arrays;`):

```java
public static void main(String[] args) {
    ArrayList<Integer> ints = new ArrayList<>(Arrays.asList(1, 10, 20, 30, 40, 50));
    System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(ints)));     // STD: 16.84

    ArrayList<Double> doubles = new ArrayList<>(Arrays.asList(3.4));
    System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(doubles)));  // STD: 0.00

    ArrayList<Integer> bag = new ArrayList<>(Arrays.asList(2, 4, 4, 4, 5, 5, 7, 9));
    System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(bag)));      // STD: 2.00

    ArrayList<Double> two = new ArrayList<>(Arrays.asList(1.5, 2.5));
    System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(two)));      // STD: 0.50

    System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(new ArrayList<Integer>())));   // STD: NaN
}
```

## 2.4 Task 4: ArrayList vs arrays (= 1.1)

Theory only: the three reasons in 1.1 (slower, no `[]`, no primitives) and that it grows by copying an internal array.

## 2.5 Task 5: ExecuteAndSort (= 1.5, 1.6)

The aud's task, reworded as an exam statement. Do the steps in order.

**What's given** (copy from the aud, don't change):
- **`Student implements Comparable<Student>`** with:
  - fields `String id` and `List<Integer> grades`
  - `double average()`, `int getYear()`, `int totalCourses()`, `double labAssistantPoints()`
  - `compareTo`: students are compared by `labAssistantPoints()`, and on a tie by `average()`
  - `toString()` in the required output format
- **`ExecuteAndSortTest.main`**, which reads the input and creates either a `List<Student>` or a `List<Integer>`. It's the task's own `main`, so there's no separate sample `main` here: run it with Redirect input and the examples below.

**Step 1: `Student.mapGrades`.** Implement `public static List<Integer> mapGrades(List<Integer> grades)`. It returns a **new** list in which every grade is converted to the new grading system: `10 → 1`, `9 → 2`, `8 → 3`, `7 → 4`, `6 → 5`. The input list must not be modified. *Hint:* every pair adds up to 11. Use a loop or a stream `map` (1.6).

**Step 2: `ExecuteAndSort.execute`.** Create a class `ExecuteAndSort` with a **static generic method** `execute`:
- **Type parameter:** `E`, restricted to types that are `Comparable` (so they can be sorted).
- **Parameters:** `List<E> elements` (the objects) and `Function<E, E> function` (takes an `E`, returns an `E`).
- **Returns:** a `List<E>` with the result of applying `function` to **every** element, sorted in **descending** order (largest first, by `compareTo`).

*Hint:* it's your `Transform.applyAndSort` from 1.6, with `sorted(Comparator.reverseOrder())` instead of `sorted()`.

**Step 3: the three TODO calls in `main`.** In each case, call `ExecuteAndSort.execute` with the list and a **lambda** for the function, store the result back in the same variable, and print it with `System.out.println(list)`.
1. **Students, scenario 1:** every student's `id` gets the suffix `_FCSE` (`211001` → `211001_FCSE`).
2. **Students, scenario 2:** every student's grades are converted with `Student.mapGrades`.
3. **Integers:** every number under `100` becomes 10 times larger, and every number `100` or above 2 times larger.

For 1 and 2, the lambda receives a `Student` and must return a `Student`. Either change the student's field and return the same student (the aud's way), or build a new `Student` with the changed value.

**Input format:**
```text
TEST_CASE          (1 = students, 2 = integers)
N                  (number of elements)
SCENARIO           (only for students: 1 = add _FCSE, 2 = map grades)
N lines:           students: ID GRADE GRADE ...   |   integers: one number per line
```

**Checklist before you run:**
- `execute` is `static` and generic, with the bound before the return type: `<E extends Comparable<E>>`.
- It sorts **descending**: `Comparator.reverseOrder()`, not plain `sorted()`.
- It collects with `Collectors.toList()` (not `.toList()`, which is Java 16+).
- Imports: `java.util.*`, `java.util.function.Function`, `java.util.stream.Collectors`.
- Each lambda returns the right type: `Student` → `Student`, `Integer` → `Integer`.

**Integers** (×10 if under 100, otherwise ×2):

INPUT
```text
2
4
5
150
99
100
```
OUTPUT
```text
[990, 300, 200, 50]
```

**Students, scenario 1** (`_FCSE` suffix):

INPUT
```text
1
3
1
211001 10 9 8 10 9
221002 7 8 9
231003 10 10
```
OUTPUT
```text
[Student 231003_FCSE (1 year) - 2/10 passed exam, average grade 10.00.
Lab assistant points: 1.60, Student 211001_FCSE (3 year) - 5/30 passed exam, average grade 9.20.
Lab assistant points: 1.43, Student 221002_FCSE (2 year) - 3/20 passed exam, average grade 8.00.
Lab assistant points: 1.04]
```

**Students, scenario 2** (grades 10→1 … 6→5): same students with `2` as the third line:
```text
[Student 221002 (2 year) - 3/20 passed exam, average grade 3.00.
Lab assistant points: 0.39, Student 211001 (3 year) - 5/30 passed exam, average grade 1.80.
Lab assistant points: 0.28, Student 231003 (1 year) - 2/10 passed exam, average grade 1.00.
Lab assistant points: 0.16]
```

Notes on the posted solution:
- `<E extends Comparable>` is a **raw** type: it compiles, but with 5 unchecked warnings (`-Xlint:unchecked`). `<E extends Comparable<E>>` is the clean version, and then the `(List<E>)` cast isn't needed.
- The student lambdas **change** the original `Student` objects (1.6 trap), so the old list changes too.
- `getYear()` is `24 - first two digits of the ID`, hardcoded for 2024. An ID starting with `24` gives year 0, so `totalCourses()` is 0 and the lab assistant points become `Infinity` (division by zero with doubles doesn't throw).
- `average()` crashes (`NoSuchElementException`) for a student with no grades.

---

# 3. Extra (not covered in auds)

- **Testing random code:** `new Random(42)` (a seed) gives the same sequence every run, so a test can expect exact output. Pass the `Random` in through the constructor to use it in `Bag`/`Box`.
- **Sorting a list in place:** `Collections.sort(list)` (ascending, needs `Comparable`) and `Collections.sort(list, Collections.reverseOrder())`. It's an alternative to the stream chain in 1.6.
- **Simpler `compareTo`:** `return Integer.compare(this.priority, o.priority);`. Avoid `this.priority - o.priority`, which can overflow for huge values.
- **Execute without streams:** a new `ArrayList`, `add(function.apply(x))` in a loop, then `Collections.sort(result, Collections.reverseOrder())`. Same result as the aud's stream version.

Sources: Aud 3 (Advanced Programming, Auditory Exercise 3, generics), from your project's NP Auditory Exercises link.
