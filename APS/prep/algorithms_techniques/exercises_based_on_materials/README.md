# APS prep: Algorithm techniques (brute force, greedy, divide and conquer, DP)

**The exercises:** 9 tasks (Part 2) that each need one technique: build the largest number from digits, minimum train platforms, max earnings in 40 hours, minimum meeting rooms, street lights, positive binary substrings, max product of an increasing sequence, recursive binary search, and fewest squares to reach 0.

**Based on:** Aud 03 "Algorithms techniques" (brute force slides 2-8, greedy 9-17, knapsack 18-26, divide and conquer 27-39), Aud 04 "Algorithms techniques" (mergesort and pow again, then dynamic programming: Pascal's triangle, Mars robot, cheapest flights, 0-1 knapsack, longest common subsequence), and lectures 04/05 "Algorithms techniques" (greedy scheduling and bin packing, D&C max, dynamic programming). Things the exercises need that none of them shows as code are marked **not in auds**.

Wherever there's a shorter way than the aud's hand-written code, a **Modern:** line gives it. Both work in the checker (Java 11, `java.util` allowed).

Part 1 is a practice theme, a **delivery depot**: packages with weights and values, trucks that arrive and leave, charging stations along a road. Each section is its own module with its own `Main.java`: expand **Main.java for this module** at the end of a section, paste it, and fill in the empty methods. `main` already calls them on hardcoded test cases, and the expected output is right below the code. Part 2 is the exercise set, with hints and tests but no solutions.

**Workflow (IntelliJ):** right-click the parent folder → **New → Module…**, build system IntelliJ, no sample code. Never "Mark Directory as Sources Root" on a folder meant to be its own module (that's what broke your run configs). Run with the gutter ▶ next to `main`. Suggested module names: `brute_force`, `greedy_coins`, `fractional_knapsack`, `max_overlap`, `covering`, `divide_and_conquer`, `dynamic_programming`, `dp_tables`.

---

# 1. Concepts

## 1.1 Brute force: try every possibility (Aud 03 slides 2-8)

- Brute force = check **all** candidates, keep the best/count. Always correct, often slow. The aud's two examples are both nested loops.
- **Pairs** (closest points, slide 5): `for i in 0..n-2, for j in i+1..n-1`. Starting `j` at `i + 1` means every pair once and never an element with itself.
- **All positions** (two queens, slide 8): 4 loops over 8×8 = 8⁴ = 4096 checks. It counts **ordered** placements (queen A on x, B on y is different from A on y, B on x): the result is 2576, i.e. 1288 unordered pairs. Same-square placements count as "attacking" (same row), so they drop out.
- **Every contiguous segment** (subarray) `a[i..j]`: two loops. Don't add a third loop to sum the segment: keep a running total that grows as `j` moves right. That's O(n²) instead of O(n³), same answer.

```java
for (int i = 0; i < n; i++) {
    int sum = 0;                       // reset for each start
    for (int j = i; j < n; j++) {
        sum += weights[j];                   // sum of weights[i..j]
        if (sum > 20) count++;
    }
}
```

**Exercise:**
1. The weights are hardcoded in `main`: `int[] weights = {3, 8, 5, 12, 2, 7};`.
2. Fill `closestDiff` and `pairsAtMost`: the smallest difference between two weights (aud slide 5 pattern, `Math.abs`). Then count pairs `i < j` with `weights[i] + weights[j] <= 10`.
   ```
   closest weights differ by 1
   pairs with sum <= 10: 6
   ```
3. Break it on purpose: start the inner loop at `j = 0`. The pair count becomes `15` (pairs counted twice, plus `3+3`, `5+5`, `2+2`). Put it back.
4. Fill `segmentsOver` (its own loop, not the pairs loop): count contiguous segments with total weight `> 20` using the running sum above: `8`. A segment is a block of neighbors summed together, e.g. `8 5 12` = 25 and `12 2 7` = 21; a pair like `weights[i] + weights[j]` is not a segment (no pair here goes over 20). Optional: write the 3-loop version and check it also gives 8.

<details>
<summary><b>Main.java for this module</b> (<code>brute_force</code>)</summary>

```java
public class Main {
    public static void main(String[] args) {
        int[] weights = {3, 8, 5, 12, 2, 7};
        System.out.println("closest weights differ by " + closestDiff(weights));
        System.out.println("pairs with sum <= 10: " + pairsAtMost(weights, 10));
        System.out.println("segments with total > 20: " + segmentsOver(weights, 20));
    }

    static int closestDiff(int[] weights) { return 0; }
    static int pairsAtMost(int[] weights, int limit) { return 0; }
    static int segmentsOver(int[] weights, int limit) { return 0; }
}
```

Expected output once every method is filled in:

```
closest weights differ by 1
pairs with sum <= 10: 6
segments with total > 20: 8
```

</details>

## 1.2 Greedy: take the best thing right now (Aud 03 slides 9-17, lecture 04)

- Greedy = in each step pick the **locally best** choice and never undo it. Fast, but only correct for some problems. You must be able to argue why the local choice can't hurt.
- Almost every greedy starts with **sorting** by the right key. The aud sorts by hand with a swap loop (slide 14):
  ```java
  for (i = 0; i < n; i++)
      for (j = i + 1; j < n; j++)
          if (coins[i] < coins[j]) { tmp = coins[i]; coins[i] = coins[j]; coins[j] = tmp; }   // descending
  ```
- **Modern:** `Arrays.sort(a)` sorts `int[]` ascending. For descending you need `Integer[]` (a comparator doesn't work on `int[]`): `Arrays.sort(a, Collections.reverseOrder())`. Or sort ascending and loop backwards.
- **Coins** (slides 13-16): sort descending, take `sum / coin` of each coin, continue with the remainder.
- **Greedy can fail** (slide 17, lecture 05): coins {1, 2, 5, 8, 10}, sum 13: greedy takes `10 2 1` (3 coins), but `8 5` is 2. Coins {1, 5, 8, 10}, sum 23: greedy `10 10 1 1 1` (5 coins), optimal `10 8 5` (3). The fix is DP (1.7).
- **Scheduling** (lecture 04, "shortest job first"). Picture **one barber and four customers** who all walk in at 9:00. Their haircuts take 16, 9, 5 and 11 minutes. He does one at a time, and each customer only cares about **when they personally get to leave**. The question: in what order should he serve them so people leave as early as possible **on average**? (The lecture says processor and jobs; same thing.)

  | Order | Each customer leaves after | Average |
  |---|---|---|
  | as they came: 16, 9, 5, 11 | 16, 16+9 = 25, 25+5 = 30, 30+11 = 41 | (16+25+30+41) / 4 = **28** |
  | quickest first: 5, 9, 11, 16 | 5, 5+9 = 14, 14+11 = 25, 25+16 = 41 | (5+14+25+41) / 4 = **21.25** |

  The barber always finishes at 41 (the total work), but with quickest-first the customers leave 7 minutes sooner on average. Why it's optimal: whoever goes first makes **everyone behind them** wait their length, so the shortest haircut belongs there; then the next shortest, and so on. The whole greedy algorithm is: **sort ascending**.

**Exercise:**
1. `greedyCoins(int[] coins, int sum)`: sort descending (aud loop first, then try the modern one), print the coins used and return the count.
   ```
   coins {1,2,5,10,50}, 87  ->  50 10 10 10 5 2   (6 coins)
   coins {1,5,8,10},    23  ->  10 10 1 1 1       (5 coins, NOT optimal)
   coins {1,2,5,8,10},  13  ->  10 2 1            (3 coins, NOT optimal)
   ```
   The two NOT optimal ones can't be fixed by tweaking the greedy loop: greedy commits to the biggest coin and never reconsiders, and here that first choice is already wrong. They get fixed later with dynamic programming (1.7, step 3: `[5, 8, 10]` and `[5, 8]`). For now, just see that greedy gets them wrong.
2. `averageFinish(int[] jobs)`: the barber's "score" for one order. `jobs` holds the haircut lengths in the order he does them; return the average time at which customers leave (the 28 / 21.25 from the table). It does **not** pick the order: the greedy algorithm is the `Arrays.sort(sortedJobs)` line in `main`, and `averageFinish` is how you see it helped.
   - Keep a clock `time` that starts at 0. For each job: `time += job` (the clock moves forward by this haircut; now `time` is when this customer leaves), then `total += time`.
   - Return `(double) total / n`. Without the cast, `int / int` is integer division: `85 / 4` gives `21`, not `21.25`.
   - Don't just add up the lengths: (16+9+5+11) / 4 = 10.25 is the average haircut length, the same in any order.

   `main` calls it on `{16, 9, 5, 11}` as they came (`28.0`) and on a sorted copy (`21.25`).
3. `smallestNumber`: the depot prints a shipment code from digit labels: given digits `3 0 7 1 0`, build the **smallest** number with no leading zero (`10037`). Idea: sort ascending, then swap the first non-zero digit to the front. Print digits one after another into a `StringBuilder`; don't try to fit them into an `int`.

<details>
<summary><b>Main.java for this module</b> (<code>greedy_coins</code>)</summary>

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.println("count: " + greedyCoins(new int[]{1, 2, 5, 10, 50}, 87));
        System.out.println("count: " + greedyCoins(new int[]{1, 5, 8, 10}, 23));
        System.out.println("count: " + greedyCoins(new int[]{1, 2, 5, 8, 10}, 13));
        int[] jobs = {16, 9, 5, 11};
        System.out.println("average finish: " + averageFinish(jobs));
        int[] sortedJobs = jobs.clone();
        Arrays.sort(sortedJobs);
        System.out.println("average finish, shortest first: " + averageFinish(sortedJobs));
        System.out.println("smallest code: " + smallestNumber(new int[]{3, 0, 7, 1, 0}));
    }

    // greedyCoins also prints the coins it uses
    static int greedyCoins(int[] coins, int sum) { return 0; }
    static double averageFinish(int[] jobs) { return 0; }
    static String smallestNumber(int[] digits) { return ""; }
}
```

Expected output once every method is filled in:

```
50 10 10 10 5 2
count: 6
10 10 1 1 1
count: 5
10 2 1
count: 3
average finish: 28.0
average finish, shortest first: 21.25
smallest code: 10037
```

</details>

## 1.3 Fractional knapsack: greedy by ratio (Aud 03 slides 18-26)

- A knapsack holds at most `capacity` kg; item `i` weighs `weight[i]` and is worth `profit[i]`. (The aud calls these `C`, `t` (tezina) and `p`.) **Fractional**: you may take part of an item. **0-1**: whole item or nothing.
- Fractional greedy: sort by **profit per unit** `profit[i] / weight[i]` descending. Take whole items while they fit; take the fraction `capacity / weight[i]` of the first one that doesn't, then stop.
- The aud sorts **two parallel arrays** together (slide 23): when it swaps `profit[i]` and `profit[j]`, it also swaps `weight[i]` and `weight[j]`. Forget one and items get mixed up.
- Trap: `profit[i] / weight[i]` with two `int`s is integer division (`25 / 18 == 1`). The aud casts: `profit[i] / (float) weight[i]`. Use `double`.
- The 0-1 version **can't** be solved greedily (slide 26): items (10 kg, 60), (20, 100), (30, 120), C = 50. Greedy by ratio takes the first two = 160. Best is 20 + 30 = 220.
- **Modern:** an `Item` class with fields `weight`, `profit` plus `Arrays.sort(items, (a, b) -> Double.compare(b.profit / b.weight, a.profit / a.weight))`. No parallel-array swapping.

```java
for (i = 0; i < n; i++) {
    if (capacity >= weight[i]) { capacity -= weight[i]; totalProfit += profit[i]; }        // whole item
    else { totalProfit += profit[i] * (capacity / weight[i]); break; }          // part of it, then full
}
```

**Exercise:**
1. `fractionalKnapsack(double[] profit, double[] weight, double capacity)`: `profit[i]` is item `i`'s value, `weight[i]` its weight, `capacity` how much the knapsack holds; return the best total profit (`totalProfit`). Sort with the aud's sort-both-arrays loop. Aud example slide 22: 3 items, `profit = {25, 24, 15}`, `weight = {18, 15, 10}`, `capacity = 20`:
   ```
   profit per kg: 25/18 = 1.39, 24/15 = 1.6, 15/10 = 1.5   -> order: item 2, item 3, item 1
   item 2: 15 kg fits whole       -> profit 24,  capacity left 5
   item 3: 10 kg doesn't fit      -> take 5/10 of it = 0.5 * 15 = 7.5, capacity 0, stop
   total = 31.5
   ```
2. Aud slide 20 (student's suitcase, capacity 20 kg), as (value, weight): clothes (200, 10), books (150, 20), games (5, 0.5), CD player (80, 5) → `318.75` (clothes, CD player, games whole, then 4.5 of the 20 kg of books). Note the 0.5 kg weight: this is why `weight` is `double`.
3. Run `profit = {60, 100, 120}`, `weight = {10, 20, 30}` with `capacity = 50` (`240.0`) and `capacity = 40` (`200.0`). Note `println` of a `double` prints `200.0`, not `200`.
4. Rewrite it with an `Item` class and the modern sort; same outputs.

<details>
<summary><b>Main.java for this module</b> (<code>fractional_knapsack</code>)</summary>

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.println(fractionalKnapsack(new double[]{25, 24, 15}, new double[]{18, 15, 10}, 20));
        System.out.println(fractionalKnapsack(new double[]{200, 150, 5, 80}, new double[]{10, 20, 0.5, 5}, 20));
        System.out.println(fractionalKnapsack(new double[]{60, 100, 120}, new double[]{10, 20, 30}, 50));
        System.out.println(fractionalKnapsack(new double[]{60, 100, 120}, new double[]{10, 20, 30}, 40));
    }

    static double fractionalKnapsack(double[] profit, double[] weight, double capacity) { return 0; }
}
```

Expected output once every method is filled in:

```
31.5
318.75
240.0
200.0
```

</details>

## 1.4 Maximum overlap: sort start and end times (**not in auds**)

- Question: intervals `[start, end]`; what's the most that are active at the same moment? Platforms, meeting rooms, docks: all this.
- Brute force (1.1 style): walk the clock minute by minute, and at each minute count how many intervals contain it; the answer is the biggest count. For the trucks in the exercise below:
  ```
  minute:   1  2  3  4  5  6  7  8  9  10 11 12
  present:  1  2  2  2  3  2  2  2  3  1  1  1     -> max 3
  ```
  Correct, but (minutes × intervals) checks: times up to 10⁹ mean a billion loop steps. And `minute++` only works for whole-number times (an arrival at 9.5 would be skipped). Better brute force: the busiest moment is always **at some arrival** (the count only goes up when someone arrives), so check only the arrival times: O(n²), any size, decimals fine.
- Sweep: put all starts in one array and all ends in another, **sort both**. Walk with two indexes like merging (`merge` in Aud 03 slide 31): if the next start comes before the next end, someone arrives (`cur++`, update max), otherwise someone leaves (`cur--`).
- **The tie rule decides the answer.** Interval ending at 5 and another starting at 5:
  - overlapping (a train arriving at 5 while another is still on the platform at 5): process the start first: `start <= end`
  - not overlapping (a meeting ending at 5 frees the room for one starting at 5): process the end first: `start < end`
- This is exactly what you did with two `PriorityQueue`s from Aud 05 (`arrivalQ`, `departureQ`). Sorted arrays are the same thing with less code.

```java
Arrays.sort(start); Arrays.sort(end);
int i = 0, j = 0, cur = 0, max = 0;
while (i < n) {
    if (start[i] <= end[j]) { cur++; i++; max = Math.max(max, cur); }
    else { cur--; j++; }
}
```

**Exercise:**
1. Five trucks use the depot; each needs a loading dock from the minute it arrives to the minute it leaves: `1-4, 2-5, 9-12, 5-9, 5-9`. `main` passes them as two arrays (`arrive[i]`, `leave[i]` are truck `i`). `maxDocks` returns the most trucks at the depot at the same moment, which is how many docks you need.
   - With `<=` (a truck leaving at minute 5 still blocks its dock at minute 5): at minute 5 the trucks `2-5`, `5-9` and `5-9` are all there → `3`.
   - Change to `<` (a truck leaving at 5 frees its dock for one arriving at 5): `2-5` is gone before the two `5-9`s arrive, so at most 2 at once → `2`.
2. `bruteDocks(arrive, leave)`: the minute-by-minute brute force. Find the first arrival and last departure; for every `minute` in between, count trucks with `arrive[i] <= minute && minute <= leave[i]`; return the biggest count (`3`, the table above). Then try the "only check arrival times" version (loop over `k` and use `arrive[k]` instead of `minute`): also `3`. The tie rule shows up here as `minute <= leave[i]` vs `minute < leave[i]`.

<details>
<summary><b>Main.java for this module</b> (<code>max_overlap</code>)</summary>

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        int[] arrive = {1, 2, 9, 5, 5};
        int[] leave  = {4, 5, 12, 9, 9};
        System.out.println("docks needed: " + maxDocks(arrive, leave));
        System.out.println("brute force: " + bruteDocks(arrive, leave));
    }

    static int maxDocks(int[] arrive, int[] leave) { return 0; }
    static int bruteDocks(int[] arrive, int[] leave) { return 0; }
}
```

Expected output once every method is filled in:

```
docks needed: 3
brute force: 3
```

</details>

## 1.5 Greedy covering (**not in auds**) and bin packing (lecture 04/05)

- Covering a line: a road has positions `1, 2, ..., roadLength`. You may build a charging station only at some listed positions (`positions`). A station at position `station` covers itself and `reach` positions to each side: `station - reach .. station + reach`. Every road position must be covered; use as few stations as possible. (Exercise 5's street lights are this with `reach = 2`.)
- Greedy: let `uncovered` = leftmost position not yet covered (starts at 1). Among the allowed positions that reach `uncovered` (`station - reach <= uncovered`), build at the **rightmost** one: it covers furthest to the right, so it can only help. Then everything up to `station + reach` is covered, so `uncovered = station + reach + 1`. Repeat while `uncovered <= roadLength`. If no allowed position reaches `uncovered`, it's impossible.
- Sort the positions first (input may be unsorted). Because `uncovered` only grows, one index moving forward is enough.
- Bin packing (lecture, theory question material): packages of size ≤ 1 into bins of size 1. **Next fit**: only look at the current bin, open a new one if it doesn't fit (linear, at worst 2× the optimum). **First fit**: put it in the first bin that has room. Sizes 0.2 0.5 0.4 0.7 0.1 0.3 0.8: next fit uses 5 bins, first fit 4, optimal is 3 (0.2+0.8, 0.3+0.7, 0.1+0.4+0.5).
- Trap: in `double`, `0.4 + 0.3 + 0.2 + 0.1` is `0.9999999999999999`, not `1.0`, so "is the bin exactly full?" checks go wrong. Store sizes in tenths as `int` (2, 5, 4, ...) and bins of size 10.

**Exercise:**
1. `minStations(int[] positions, int roadLength, int reach)` returns the minimum number of stations, or `-1` if the road can't be covered. With `reach = 1` (a station covers itself and 1 each side), road `1..10`, allowed `{2, 3, 5, 8, 10}`:
   ```
   uncovered = 1:  allowed spots reaching 1 are 2 (and not 3: 3-1 = 2 > 1) -> build at 2, covers 1-3, uncovered = 4
   uncovered = 4:  spots reaching 4: 3, 5                                  -> build at 5, covers 4-6, uncovered = 7
   uncovered = 7:  spots reaching 7: 8                                     -> build at 8, covers 7-9, uncovered = 10
   uncovered = 10: spots reaching 10: 10                                   -> build at 10, covers 9-11, done
   ```
   ```
   positions {2,3,5,8,10}, roadLength = 10  ->  4
   positions {10,5,3,8,2}, roadLength = 10  ->  4   (unsorted input, same answer)
   positions {2,8},        roadLength = 10  ->  -1  (nothing reaches position 4)
   ```
2. `nextFit(sizes, binSize)` and `firstFit(sizes, binSize)` return how many bins each strategy uses. The lecture's packages 0.2 0.5 0.4 0.7 0.1 0.3 0.8 are written in tenths as `{2, 5, 4, 7, 1, 3, 8}` with bin size 10 → `5` and `4`:
   ```
   next fit:  [2 5] [4] [7 1] [3] [8]      -> 5 bins (4 doesn't fit next to 2+5=7, and it never looks back)
   first fit: [2 5 1] [4 3] [7] [8]        -> 4 bins (1 goes back into the first bin, 3 into the second)
   ```

<details>
<summary><b>Main.java for this module</b> (<code>covering</code>)</summary>

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.println(minStations(new int[]{2, 3, 5, 8, 10}, 10, 1));
        System.out.println(minStations(new int[]{10, 5, 3, 8, 2}, 10, 1));
        System.out.println(minStations(new int[]{2, 8}, 10, 1));
        int[] sizes = {2, 5, 4, 7, 1, 3, 8};   // tenths, bin size 10
        System.out.println("next fit " + nextFit(sizes, 10) + ", first fit " + firstFit(sizes, 10));
    }

    static int minStations(int[] positions, int roadLength, int reach) { return 0; }
    static int nextFit(int[] sizes, int binSize) { return 0; }
    static int firstFit(int[] sizes, int binSize) { return 0; }
}
```

Expected output once every method is filled in:

```
4
4
-1
next fit 5, first fit 4
```

</details>

## 1.6 Divide and conquer: recursion on halves (Aud 03 slides 27-39, lecture 05)

- Divide into smaller subproblems → solve them recursively → combine. Always has a **base case** that stops the recursion.
- Lecture example, max of an array: the max of `array[left..right]` is the larger of the max of the left half and the max of the right half; base case `left == right` (one element) → `array[left]`. Example `29 14 15 1 6 10 32 12` → 32.
- `pow(base, exponent)` (slide 36): compute `half = pow(base, exponent / 2)` **once**, return `half * half` (or `base * half * half` if the exponent is odd): O(log n). Solution 2 (slide 38) calls `pow(base, exponent / 2)` **twice**: same result, but O(n) calls. Lesson: never recompute the same recursive call.
- Mergesort (slides 29-34): split at `mid = (left + right) / 2`, sort both halves, `merge`. O(n log n). The aud writes `a, l, r` for `array, left, right` and `x, n` for `base, exponent`. Two bugs in the Aud 03 code: `int I = l` (capital I, then uses `i` → compile error; Aud 04's copy fixes this one) and `int temp[] = new int[100]` (in both auds; crashes for more than 100 elements; use `new int[numel]`).
- Binary search works the same way on a **sorted** array: look at the middle; if that's not it, recurse into the one half that can contain the answer. O(log n). Return a special value (like `-1`) when `left > right` (nothing left to search).

**Exercise:**
1. `dcMax(int[] array, int left, int right)` → `32` on the lecture array.
2. Type in both `pow` versions with a `static int calls` counter incremented at the top of each:
   ```
   pow1(2, 16) = 65536, calls 6        pow2(2, 16) = 65536, calls 63
   pow1(3, 13) = 1594323, calls 5      pow2(3, 13) = 1594323, calls 31
   ```
3. Copy the aud's `merge`/`mergesort`, read the compile error from `int I`, fix both bugs. `{5, 2, 9, 1, 7, 3}` → `[1, 2, 3, 5, 7, 9]` (`Arrays.toString`).
4. Delivery days are sorted: `{2, 4, 4, 7, 9, 13}`. Recursive `firstAtLeast(days, left, right, target)`: the first index whose day is `>= target`, `-1` if none. Hint: if `days[mid] >= target`, the answer is `mid` or something to its left; otherwise it's on the right.
   ```
   target = 4 -> 1    target = 8 -> 4    target = 14 -> -1    target = 1 -> 0
   ```

<details>
<summary><b>Main.java for this module</b> (<code>divide_and_conquer</code>)</summary>

```java
import java.util.*;

public class Main {
    static int calls = 0;   // call counter

    public static void main(String[] args) {
        int[] numbers = {29, 14, 15, 1, 6, 10, 32, 12};
        System.out.println("max: " + dcMax(numbers, 0, numbers.length - 1));
        calls = 0; System.out.println("pow1(2, 16) = " + pow1(2, 16) + ", calls " + calls);
        calls = 0; System.out.println("pow2(2, 16) = " + pow2(2, 16) + ", calls " + calls);
        int[] toSort = {5, 2, 9, 1, 7, 3};
        mergesort(toSort, 0, toSort.length - 1);
        System.out.println(Arrays.toString(toSort));
        int[] days = {2, 4, 4, 7, 9, 13};
        int lastIndex = days.length - 1;
        System.out.println(firstAtLeast(days, 0, lastIndex, 4) + " " + firstAtLeast(days, 0, lastIndex, 8) + " "
                + firstAtLeast(days, 0, lastIndex, 14) + " " + firstAtLeast(days, 0, lastIndex, 1));
    }

    // pow1 and pow2 start with calls++
    static int dcMax(int[] array, int left, int right) { return 0; }
    static int pow1(int base, int exponent) { return 0; }
    static int pow2(int base, int exponent) { return 0; }
    static void merge(int[] array, int left, int mid, int right) { }
    static void mergesort(int[] array, int left, int right) { }
    static int firstAtLeast(int[] days, int left, int right, int target) { return -1; }
}
```

Expected output once every method is filled in:

```
max: 32
pow1(2, 16) = 65536, calls 6
pow2(2, 16) = 65536, calls 63
[1, 2, 3, 5, 7, 9]
1 4 -1 0
```

</details>

## 1.7 Dynamic programming: remember subproblem answers (lecture 05)

This section uses the lecture's 1D examples (Fibonacci, coins, sequences). Aud 04's 2D-table problems come right after, in 1.8.

- DP = the recursion asks the **same subproblem many times**, so store each answer in an array once. Fibonacci recursively is O(2ⁿ); with an array it's O(n).
- Recipe: (1) **state**: what `dp[i]` means in words; (2) **transition**: how `dp[i]` is built from smaller states; (3) **base case**; (4) **order**: fill so the states you need are already done; (5) where the answer is (`dp[n]`, or max over all `dp[i]`).
- Coin change (fewest coins that add up to `sum`, each coin usable any number of times): `dp[amount]` = fewest coins that add up to `amount`. `dp[0] = 0`, `dp[amount] = 1 + min(dp[amount - coin])` over coins `coin <= amount`. Fill `amount = 1, 2, ..., sum`. This always finds the optimum, unlike greedy in 1.2.
- The lecture's code does it the other way round (its array is called `sum[]`; it pushes from `sum[i]` to `sum[i + coins[j]]`) and indexes past the end of the array: with `SUMS = 24` it throws `ArrayIndexOutOfBoundsException: Index 24 out of bounds for length 24`. The `dp[amount - coin]` version above has no such problem.
- Mark "unreachable" with `Integer.MAX_VALUE` and check it before adding 1, or `MAX_VALUE + 1` wraps to a negative number and wins every `min`.
- **Sequence DP** ("best chain ending at i"): `dp[i]` = best value of a chain that **ends** with element `i`. `dp[i] = own value combined with the best dp[j]`, for `j < i` that may come right before `i`. Answer = max of all `dp[i]`. O(n²).

**Exercise:**
1. `fib(30)` recursively and `memoFib(30, memo)` with a `long[] memo` (0 = not computed yet), counting calls: `1346269, calls 2692537` vs `1346269, calls 59` (lecture convention `fib(0) = fib(1) = 1`).
2. `minCoins(int[] coins, int sum)`, printing the whole `dp` array:
   ```
   coins {1,5,8,10}, sum = 23
   0 1 2 3 4 1 2 3 1 2 1 2 3 2 3 2 2 3 2 3 2 3 4 3   -> 3
   ```
   Compare with greedy's 5 from 1.2.
3. Worked example, the fix for 1.2's NOT optimal cases: `dpCoins` is `minCoins` plus **which coins** it used. Next to `dp`, keep `last[amount]` = the coin that gave the best answer for `amount`. At the end, walk back from `sum` like breadcrumbs: take `last[sum]`, go to `sum - last[sum]`, repeat until 0. Type it in and run it:
   ```java
   static int dpCoins(int[] coins, int sum) {
       int[] dp = new int[sum + 1];       // dp[amount] = fewest coins that add up to amount
       int[] last = new int[sum + 1];     // last[amount] = the coin used last to reach amount
       Arrays.fill(dp, Integer.MAX_VALUE);
       dp[0] = 0;
       for (int amount = 1; amount <= sum; amount++) {
           for (int coin : coins) {
               if (coin <= amount && dp[amount - coin] != Integer.MAX_VALUE && dp[amount - coin] + 1 < dp[amount]) {
                   dp[amount] = dp[amount - coin] + 1;
                   last[amount] = coin;
               }
           }
       }
       if (dp[sum] == Integer.MAX_VALUE) return -1;    // sum can't be made
       List<Integer> used = new ArrayList<>();
       for (int amount = sum; amount > 0; amount -= last[amount]) used.add(last[amount]);   // walk back
       System.out.println(used);
       return dp[sum];
   }
   ```
   ```
   {1,5,8,10},    23  ->  [5, 8, 10]               3   (greedy: 5)
   {1,2,5,8,10},  13  ->  [5, 8]                   2   (greedy: 3)
   {1,2,5,10,50}, 87  ->  [2, 5, 10, 10, 10, 50]   6   (same as greedy)
   {2,5},          3  ->  -1                           (greedy loops forever or crashes)
   ```
   For 23 the walk back is: `last[23] = 5` → 18, `last[18] = 8` → 10, `last[10] = 10` → 0. It doesn't need the coins sorted, and exercise 9 (squares) is this same function with the coins being 1, 4, 9, 16, …
4. `maxIncreasingSum`: packages come in a fixed order with values. Pick some of them (not necessarily next to each other, order kept) with **strictly increasing** values; maximize the **sum**. `dp[i] = values[i] + max(dp[j])` over `j < i` with `values[j] < values[i]` (or just `values[i]` if there's no such `j`).
   ```
   {1, 101, 2, 3, 100, 4, 5}  dp = [1, 102, 3, 6, 106, 10, 15]  -> 106
   {4, 6, 1, 3, 8, 4, 6}      dp = [4, 10, 1, 4, 18, 8, 14]     -> 18
   ```
   Note 106 isn't the longest chain (`1 2 3 4 5` is longer); the best value and the longest are different questions.

<details>
<summary><b>Main.java for this module</b> (<code>dynamic_programming</code>)</summary>

```java
import java.util.*;

public class Main {
    static int calls = 0;   // call counter

    public static void main(String[] args) {
        calls = 0; System.out.println("fib(30) = " + fib(30) + ", calls " + calls);
        calls = 0; System.out.println("memoFib(30) = " + memoFib(30, new long[31]) + ", calls " + calls);
        System.out.println("min coins: " + minCoins(new int[]{1, 5, 8, 10}, 23));
        System.out.println("dp coins: " + dpCoins(new int[]{1, 5, 8, 10}, 23));
        System.out.println("dp coins: " + dpCoins(new int[]{1, 2, 5, 8, 10}, 13));
        System.out.println("dp coins: " + dpCoins(new int[]{1, 2, 5, 10, 50}, 87));
        System.out.println("dp coins: " + dpCoins(new int[]{2, 5}, 3));
        System.out.println("best sum: " + maxIncreasingSum(new int[]{1, 101, 2, 3, 100, 4, 5}));
        System.out.println("best sum: " + maxIncreasingSum(new int[]{4, 6, 1, 3, 8, 4, 6}));
    }

    // fib and memoFib start with calls++; minCoins also prints the dp array
    static long fib(int n) { return 0; }
    static long memoFib(int n, long[] memo) { return 0; }
    static int minCoins(int[] coins, int sum) { return 0; }
    static int dpCoins(int[] coins, int sum) { return 0; }   // type in the worked example from step 3
    static long maxIncreasingSum(int[] values) { return 0; }
}
```

Expected output once every method is filled in:

```
fib(30) = 1346269, calls 2692537
memoFib(30) = 1346269, calls 59
0 1 2 3 4 1 2 3 1 2 1 2 3 2 3 2 2 3 2 3 2 3 4 3
min coins: 3
[5, 8, 10]
dp coins: 3
[5, 8]
dp coins: 2
[2, 5, 10, 10, 10, 50]
dp coins: 6
dp coins: -1
best sum: 106
best sum: 18
```

</details>

## 1.8 DP with tables (Aud 04, problems 2-6)

Aud 04 starts by repeating mergesort and `pow` from Aud 03 (1.6). In its mergesort the `int I` typo is fixed, but `new int[100]` is still there. The rest of the aud is dynamic programming, mostly with **2D tables**.

- Same recipe as 1.7: say in words what one cell means, how it's built from cells you already have, and what the base cases are.
- Many problems need **two numbers** to describe a subproblem ("best path to row `r`, column `c`", "best profit with the first `i` items and capacity `j`"), so the table is 2D: `best[r][c]`.
- Fill order: the **first row and first column** are the base cases, then row by row, left to right. That way the cells above and to the left are always done before you need them.
- Walking back: the table gives the best **value**. To find **which choices** produced it (which items, which letters), start at the answer cell and walk backwards, asking at each cell which option it came from. Same idea as `dpCoins` in 1.7 step 3.

### Pascal's triangle: binomial coefficients (problem 2)

- `C(n, k)` = how many ways to choose `k` things out of `n` (e.g. 2 out of 5: `C(5, 2) = 10`).
- Each number in Pascal's triangle is the sum of the two above it: `C(n, k) = C(n-1, k-1) + C(n-1, k)`, and the edges are 1.
  ```
  row 0:          1
  row 1:         1 1
  row 2:        1 2 1
  row 3:       1 3 3 1
  row 4:      1 4 6 4 1
  row 5:    1 5 10 10 5 1      -> C(5, 2) = 10
  ```
- The aud's naive recursion (`binomial(n-1, k) + binomial(n-1, k-1)`) recomputes the same cells over and over: exponential, "DO NOT RUN THIS CODE FOR LARGE INPUTS". The DP fills the triangle once: `table[row][0] = table[row][row] = 1`, then `table[row][col] = table[row-1][col-1] + table[row-1][col]`. O(n²).
- Why not just `n! / (k! (n-k)!)`? The factorials overflow long before the answer does (aud: 100! needs 525 bits).
- The aud uses `int`: `C(30, 15) = 155117520` fits, but `C(34, 17) = 2333606220` doesn't (int max is 2147483647). Use `long`.

### Mars robot: most stones on a grid (problem 3)

- A grid of numbers (stones per square). The robot starts top-left, must reach bottom-right, and may only move **right** or **down**. Maximize the stones collected.
- Trying every path is exponential. But the best path to any square must come **from the square above or the square to the left**, whichever has the better best path:

  `best[r][c] = max(best[r-1][c], best[r][c-1]) + grid[r][c]`

- Base cases: `best[0][0] = grid[0][0]`; the first row can only be reached from the left, the first column only from above (just running sums).
- Example:
  ```
  grid:           best:
  1 3 1 2         1  4  5  7
  2 1 5 1         3  5 10 11
  4 2 1 3         7  9 11 14     -> 14
  ```
  For example `best[1][2] = max(best[0][2] = 5, best[1][1] = 5) + 5 = 10`.
- The aud's variations: diagonal moves add a third option `best[r-1][c-1]` to the `max`; a cylindrical map lets the robot wrap from the last row to the first.

### Cheapest flights west to east (problem 4)

- Cities `0..n-1` from west to east; you may only fly east. Each city has an airport tax `tax[c]` (paid in every city you visit, including the first), and flying from city `i` to a later city `j` costs `cost[i][j]`. Find the cheapest way from the first city to the last.
- `best[city]` = cheapest total price to arrive in `city`. You arrived from **some** earlier city `from`, so try them all:

  `best[city] = min over from < city of (best[from] + cost[from][city] + tax[city])`, with `best[0] = tax[0]`.

- This is the same "best ending here, built from all earlier ones" shape as `maxIncreasingSum` (1.7 step 4) and exercise 7.
- Example: `tax = {5, 2, 8, 3}`, flights `0→1: 10, 0→2: 15, 0→3: 40, 1→2: 4, 1→3: 25, 2→3: 6`:
  ```
  best[0] = 5
  best[1] = 5 + 10 + 2 = 17
  best[2] = min(5 + 15 + 8 = 28,  17 + 4 + 8 = 29)                   = 28
  best[3] = min(5 + 40 + 3 = 48,  17 + 25 + 3 = 45,  28 + 6 + 3 = 37)  = 37
  ```

### 0-1 knapsack (problem 5)

- Like 1.3, but items **can't be split**: take an item whole or leave it. Greedy by ratio fails here (1.3: 160 instead of 220).
- `D[i][j]` = best profit using only the **first `i` items** with a knapsack of capacity `j`. For item `i` there are two options:
  - skip it: `D[i-1][j]` (best with the first `i-1` items, same capacity)
  - take it, if it fits (`weight <= j`): its profit + `D[i-1][j - weight]` (the best you can do with the space that's left)

  `D[i][j]` is the larger of the two. Row 0 (no items) and column 0 (no capacity) are all 0.
- The aud's example, capacity 50, items (weight, profit) = (10, 60), (20, 100), (30, 120), shown every 10 kg:
  ```
  capacity:    0   10   20   30   40   50
  no items:    0    0    0    0    0    0
  item 1:      0   60   60   60   60   60
  items 1-2:   0   60  100  160  160  160
  items 1-3:   0   60  100  160  180  220     -> 220
  ```
  `D[3][50] = max(skip: D[2][50] = 160, take item 3: 120 + D[2][20] = 220) = 220`.
- **Which items?** Walk back from `D[n][capacity]`: if `D[i][j] == D[i-1][j]`, item `i` wasn't needed, so go up. Otherwise item `i` was taken: record it and go to `D[i-1][j - weight[i]]`. Here: `D[3][50] = 220 ≠ 160` → item 3, go to `D[2][20] = 100 ≠ 60` → item 2, go to `D[1][0] = 0` → stop. Items **2 and 3**. (This is the aud's homework.)
- Time θ(n · C): one cell per item per capacity value.
- The aud's analysis slide writes the condition as `if (j > t[i])`, but its code uses `t[i-1] <= j`. The code is right: an item that exactly fills the knapsack fits.

### Longest common subsequence (problem 6, homework)

- A **subsequence** keeps the order but may skip letters (`ace` is a subsequence of `abcde`). Find the longest one that two strings share.
- `T[i][j]` = LCS length of the first `i` letters of `x` and the first `j` letters of `y`:
  - last letters equal (`x.charAt(i-1) == y.charAt(j-1)`): that letter is part of the LCS → `T[i-1][j-1] + 1`
  - different: drop the last letter of one string or the other, whichever is better → `max(T[i-1][j], T[i][j-1])`
- The string itself: walk back from `T[N][M]`. Equal letters → take it, go diagonally up-left; otherwise move to the neighbour (`up` or `left`) with the same value. The letters come out backwards, so reverse at the end.
- The aud's example: `ggcaccacg` and `acggcggatacg` → length 7, `ggcaacg`.
- Two notes on the posted code: the length method's initialization loops open `{` that are never closed (it won't compile as printed; copy the loops from the String method). And the zero-initialization isn't needed at all: Java arrays start filled with 0.

**Exercise:**
1. `binomial(n, k)` with a `long[][]` table → `10`, `120`, `155117520`. Break it on purpose: switch to `int` and try `binomial(34, 17)`.
2. `maxStones(grid)`: fill `best`, print it row by row (`Arrays.toString(row)`), return the bottom-right cell. Check against the table above.
3. `cheapestTrip(tax, cost)`: print the `best` array, return the last one. `cost[i][j]` is only used for `i < j`.
4. `knapsack01(weight, profit, capacity)` → `220`. Then `knapsackItems`: the walk back, returning the item numbers (1-based, like the aud) in increasing order → `[2, 3]`. The second test, (1, 1), (3, 4), (4, 5), (5, 7) with capacity 7, is another case where greedy by ratio fails: it takes the 5 kg item (ratio 1.4) and then the 1 kg one for 8, but items 2 and 3 give **9**.
5. `lcsLength(x, y)` and `lcsString(x, y)` → `7` and `ggcaacg`. Third test (a textbook example): `ABCBDAB` / `BDCABA` → 4.

<details>
<summary><b>Main.java for this module</b> (<code>dp_tables</code>)</summary>

```java
import java.util.*;

public class Main {
    public static void main(String[] args) {
        // Pascal's triangle
        System.out.println("C(5, 2) = " + binomial(5, 2));
        System.out.println("C(10, 3) = " + binomial(10, 3));
        System.out.println("C(30, 15) = " + binomial(30, 15));

        // Mars robot
        int[][] grid = {
                {1, 3, 1, 2},
                {2, 1, 5, 1},
                {4, 2, 1, 3}
        };
        System.out.println("most stones: " + maxStones(grid));

        // Cheapest flights west to east (cost[i][j] only matters for i < j)
        int[] tax = {5, 2, 8, 3};
        int[][] cost = {
                {0, 10, 15, 40},
                {0, 0, 4, 25},
                {0, 0, 0, 6},
                {0, 0, 0, 0}
        };
        System.out.println("cheapest trip: " + cheapestTrip(tax, cost));

        // 0-1 knapsack
        int[] weight = {10, 20, 30};
        int[] profit = {60, 100, 120};
        System.out.println("best profit: " + knapsack01(weight, profit, 50));
        System.out.println("items taken: " + knapsackItems(weight, profit, 50));
        int[] weight2 = {1, 3, 4, 5};
        int[] profit2 = {1, 4, 5, 7};
        System.out.println("best profit: " + knapsack01(weight2, profit2, 7));
        System.out.println("items taken: " + knapsackItems(weight2, profit2, 7));

        // Longest common subsequence
        System.out.println("LCS length: " + lcsLength("ggcaccacg", "acggcggatacg"));
        System.out.println("LCS: " + lcsString("ggcaccacg", "acggcggatacg"));
        System.out.println("LCS length: " + lcsLength("ABCBDAB", "BDCABA"));
    }

    // TODO: Pascal's triangle table, return C(n, k)
    static long binomial(int n, int k) { return 0; }

    // TODO: fill best[][], print it row by row, return the bottom-right cell
    static int maxStones(int[][] grid) { return 0; }

    // TODO: fill best[], print it, return the price to reach the last city
    static int cheapestTrip(int[] tax, int[][] cost) { return 0; }

    // TODO: D[i][j] table, return the best profit
    static int knapsack01(int[] weight, int[] profit, int capacity) { return 0; }

    // TODO: walk back through the table, return the taken item numbers (1-based, increasing)
    static List<Integer> knapsackItems(int[] weight, int[] profit, int capacity) { return new ArrayList<>(); }

    // TODO: T[i][j] table, return the LCS length
    static int lcsLength(String x, String y) { return 0; }

    // TODO: walk back through the table, return the LCS itself
    static String lcsString(String x, String y) { return ""; }
}
```

Expected output once every method is filled in:

```
C(5, 2) = 10
C(10, 3) = 120
C(30, 15) = 155117520
[1, 4, 5, 7]
[3, 5, 10, 11]
[7, 9, 11, 14]
most stones: 14
[5, 17, 28, 37]
cheapest trip: 37
best profit: 220
items taken: [2, 3]
best profit: 9
items taken: [2, 3]
LCS length: 7
LCS: ggcaacg
LCS length: 4
```

</details>

---

# 2. The exercises

One module each. The checker gives input on standard input, so the version you submit reads it with `Scanner` on `System.in`; while practicing, hardcode the test cases in `main` like in Part 1 (or type them into the Run window). Read the technique, try it, then check against the tests. Expected outputs below were all checked by running a solution.

| # | Exercise | Technique | Section |
|---|---|---|---|
| 1 | Largest number from digits | greedy + sort | 1.2 |
| 2 | Train platforms | max overlap, `<=` | 1.4 |
| 3 | Max earnings in 40 h | fractional knapsack | 1.3 |
| 4 | Meeting rooms | max overlap | 1.4 |
| 5 | Street lights | greedy covering, R = 2 | 1.5 |
| 6 | Positive binary substrings | brute force + running count | 1.1 |
| 7 | Max product increasing sequence | sequence DP | 1.7 |
| 8 | Binary search | divide and conquer | 1.6 |
| 9 | Fewest squares to 0 | DP like coins | 1.7 |

**1. Largest number.** Sort descending, print digit by digit (N digits overflow `long` fast). Test: `5` / `3 9 0 4 9` → `99430`; `1` / `7` → `7`. Unspecified: all zeros (`000` vs `0`); try plain concatenation first.

**2. Trains.** Given example → `2`. Arrival at the same minute another train departs counts as a conflict, so `<=`. Extra: `3` / `1 5` / `5 8` / `2 6` → `3` with `<=` (`2` with `<`). If the checker disagrees on a tie case, flip the comparison.

**3. 40 hours.** Capacity is fixed at 40; "time" is the weight, "amount" is the profit. Given example → `200`. Read the format carefully: the expected output is `200`, but `println(200.0)` prints `200.0`. Extra: `3` / `30 45` / `20 50` / `10 7` → 80; `2` / `30 100` / `30 50` → `116.666...` (find out what rounding the checker wants: a non-integer result is where you'll learn it).

**4. Meeting rooms.** Same as 2. Given example → `2`. Here a meeting ending at 10 frees the room for one starting at 10, so `<` is the natural rule. The given example can't tell the two rules apart; the extra test from 2 can.

**5. Street lights.** 1.5 with `R = 2`, street positions `1..M`. Given: `5 5` / `1 2 3 4 5` → 1; `3 10` / `3 8 9` → 2. Extra: `3 10` / `9 3 8` → 2 (sort first); `4 12` / `1 5 6 11` → 3; `2 10` / `3 9` → impossible (nothing reaches position 6). The task doesn't say what to print then; `-1` is the usual guess.

**6. Positive substrings.** All `i..j` pairs with a running balance: `+1` for `'1'`, `-1` for `'0'`; count when balance `> 0`. Read the string with `in.next()` and use `charAt`. Given: `10011` → 6, `101` → 3. Extra: `0000` → 0, `1111` → 10, `110100` → 8.

**7. Max product.** "Increasing subarray" here means **not contiguous**: the example's answer `3, 100, 150` skips elements. So it's 1.7 step 4 (`maxIncreasingSum`) with `*` instead of `+`: `dp[i] = a[i] * max dp[j]` (for `j < i`, `a[j] < a[i]`), or just `a[i]`. Use `long`. Given: 45000 and 21780000. Extra: `4` / `5 4 3 2` → 5; `3` / `2 2 2` → 2 (strictly increasing); `6` / `100000 200000 300000 1 2 3` → `6000000000000000` (with `int` you get garbage: `100000 * 200000` overflows to `-1474836480`).

**8. Binary search.** 1.6, recursive `search(a, l, r, m)` returning the index or `-1`, then print `Ne postoi` for -1. Positions are 0-based. Given: `2`, `6`. Extra: `5 6` / `1 2 3 4 5` → `Ne postoi`; `1 4` / `4` → 0; `6 1` / `1 3 5 7 9 11` → 0. Input is `N M` on the first line (array size first, searched number second).

**9. Fewest squares.** Greedy "subtract the biggest square" fails: 12 → greedy 9+1+1+1 (4), optimal 4+4+4 (3); 18 → greedy 16+1+1 (3), optimal 9+9 (2). It's coin change (1.7 step 2) where the coins are 1, 4, 9, 16, ... up to `X`. X ≤ 10⁵ → an `int[X + 1]` and O(X·√X) is fine. Tests: 13→2, 21→3, 32→2, 12→3, 25→1, 18→2, 1→1, 3→3, 99999→4. The task's own table says `32 → 16` but its explanation subtracts twice: the answer is **2** (the checker's test table agrees).

**Common mistakes**
- `p / t` with `int`s → integer division, ratios like `25/18 == 1` and a wrong sort order.
- `Arrays.sort(intArray, Collections.reverseOrder())` → compile error (no comparator on primitives). Use `Integer[]`.
- Sorting `p` without moving `t` with it → items mixed up.
- Recursion without a reachable base case → `StackOverflowError`.
- `Integer.MAX_VALUE + 1` in DP → negative, wrong minimum.
- Same `Main` class name in every module is fine, as long as each run config uses its own module (check the `-classpath ...\out\production\<module>` line).

---

# 3. Aud 03, Aud 04 and midterm theory

- **Problem 1, closest points** (= 1.1 step 2): O(n²) pairs. Test: points (0,0) (3,4) (1,1) → `1.414...`.
- **Problem 2, two queens** (= 1.1): 8⁴ checks, result 2576 (ordered pairs).
- **Problem 3, coins** (= 1.2): greedy, works for 50/10/5/2/1, fails for 1/2/5/8/10 at 13.
- **Problem 4, knapsack** (= 1.3): fractional → greedy by ratio; 0-1 → not greedy (DP, Aud 04 problem 5 = 1.8).
- **Problem 5, pow** (= 1.6): T(n) = T(n/2) + O(1) → O(log n); solution 2: T(n) = 2T(n/2) + O(1) → O(n).
- **Mergesort**: T(n) = 2T(n/2) + n → O(n log n).
- **Aud 04** (= 1.8): problem 1 is `pow` again; problem 2 Pascal's triangle (naive recursion exponential, table O(n²)); problem 3 Mars robot `best[r][c] = max(above, left) + grid[r][c]`; problem 4 cheapest flights `best[k] = min over c < k of (best[c] + cost[c][k] + tax[k])`; problem 5 0-1 knapsack θ(n·C), example 220 with items {2, 3}; problem 6 (homework) LCS, `ggcaacg`.
- Theory questions to expect: DP = remembering computed results (memoization), uses more memory for less time; use it when subproblems **overlap**; D&C is for **independent** subproblems and becomes inefficient when they overlap (recursive Fibonacci, naive Pascal); longest increasing subsequence → DP; mergesort → D&C.
- Lectures: brute force always correct but slow; greedy fast but optimum not guaranteed; D&C always correct (combine step); DP = overlapping subproblems + stored results (recursive memoization or iterative table); Fibonacci naive O(2ⁿ) vs O(n), and with 2 variables O(1) memory.
- Bin packing: next fit O(n), at worst 2× optimal; first fit O(n log n) best implementation, O(n²) simple.
- Strassen-style matrix D&C: 8 multiplications T(n) = 8T(n/2) + O(n²) is still O(n³); 7 multiplications gives O(n^log₂7) ≈ O(n^2.81).

# 4. Greedy cheat sheet: which sort key?

Most greedy problems are "sort by the right key, then go through once". If you recognize the situation, you know the key:

| Situation | Usual key | Seen in |
|---|---|---|
| Make a sum/amount with as few items as possible | biggest first (and check the "NOT optimal" case: if greedy can fail, it's DP) | coins (1.2), exercise 1 |
| Value vs. size, can take parts | value / size, biggest first | fractional knapsack (1.3), exercise 3 |
| Value vs. size, whole items only | not greedy: DP table | 0-1 knapsack (1.8) |
| Everyone waits for the ones before them | shortest first | barber / scheduling (1.2) |
| Waiting cost differs per item (weights) | time / weight, smallest first | Lab 4 A and B |
| Two numbers pulling in opposite directions | usually a ratio (or sum/difference) of the two | Lab 4, acrobat tower (weight + strength) |
| Pick as many non-overlapping intervals as possible | earliest end first | (not done yet) |
| How many intervals overlap at once | sort starts and ends separately, sweep | trains, rooms (1.4) |
| Cover a line with as few pieces as possible | leftmost uncovered point, pick the one reaching furthest | street lights (1.5) |
| Jobs with deadlines and profits (each takes 1 slot) | highest profit first, latest free slot before the deadline | Abdul Bari 3.2 |
| Pack items into as few bins as possible | no exact greedy; next fit (only the current bin), first fit (first bin with room), best fit (fullest bin that still fits) | bin packing (lecture 04/05, 1.5) |
| Shortest codes for frequent symbols | repeatedly merge the two smallest frequencies | Huffman codes (lecture 04, theory only) |

How to check a guessed key in a lab, in about a minute:
1. Sort the first example by your key, by hand.
2. Compute the answer for that order. If it matches the expected output, try the next example.
3. If it doesn't match, the key is wrong. The failing example often shows why (for example, a heavy task got pushed to the end).

Ties: if the task says "equal ones in input order", use a stable sort (`List.sort`, or bubble sort with strict `>`), or add the original index as a tie-breaker. The aud's exchange sort is not stable.

Sources: Aud 03 "Algorithms techniques" (03_Algorithms_Techniques.pdf), Aud 04 "Algorithms techniques" (04_Tehniki_Algoritmi_2_EN.pdf), lectures APS_04 and APS_05 "Tehniki algoritmi".
