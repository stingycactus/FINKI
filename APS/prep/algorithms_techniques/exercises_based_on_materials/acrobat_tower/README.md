# Acrobat tower

Greedy with a sort key you have to find yourself (the swap test). It's the same idea as Lab 4 (sort tasks by `T / W`), but the key is different and you minimize a **maximum**, not a sum.

## The task

N acrobats have to stand on each other's shoulders in one tower. Acrobat i has a weight Wᵢ and a strength Sᵢ.

An acrobat's **risk** is the total weight of everyone standing above them, minus their own strength:

```
risk = (weight of everyone above you) − (your strength)
```

Your own weight never counts for you; it presses on whoever is below you. The top acrobat has nobody above, so their risk is −Sᵢ. Risks can be negative, which means the acrobat is comfortable.

Find the order from top to bottom that makes the **largest risk in the tower as small as possible**. If several acrobats are equivalent for the ordering, keep them in input order.

**Output:** on the first line, the smallest possible maximum risk. On the second, the acrobat numbers (1 to N, in input order) from top to bottom, separated by spaces.

## Example

Weights `10 2 3`, strengths `3 5 3`. The best order, top to bottom, is acrobat 3, then 2, then 1:

| Position | Acrobat | Weight above | Risk |
|---|---|---|---|
| top | 3 (W=3, S=3) | 0 | 0 − 3 = −3 |
| middle | 2 (W=2, S=5) | 3 | 3 − 5 = −2 |
| bottom | 1 (W=10, S=3) | 3 + 2 = 5 | 5 − 3 = 2 |

The largest risk is **2**, and no order does better.

```
2
3 2 1
```

## Tests

`main` calls `tower(weight, strength)` once per test:

| # | Weights | Strengths | Expected output | What it checks |
|---|---|---|---|---|
| 1 | 10 2 3 | 3 5 3 | `2` / `3 2 1` | the example; "weakest on top" gives 8 here |
| 2 | 5 | 8 | `-8` / `1` | one acrobat, negative risk: the max must start at `Long.MIN_VALUE`, not 0 |
| 3 | 3 2 4 1 | 2 3 1 4 | `5` / `1 2 3 4` | all four tie on W + S: input order must be kept |
| 4 | 1 4 2 6 3 | 6 1 3 2 5 | `8` / `2 3 1 4 5` | a general case |
| 5 | 10 1 | 1 20 | `-1` / `1 2` | "lightest on top" gives 0 here |
| 6 | 4 × 1000000000 | 1 1 1 1 | `2999999999` / `1 2 3 4` | needs `long` |

## How to find the sort key: the swap test

The obvious guesses fail ("lightest on top" fails test 5, "weakest on top" fails test 1), so the key comes from comparing two acrobats A and B that stand next to each other.

**With numbers first.** Two acrobats, nobody else: A has W=6, S=2 and B has W=3, S=7.

```
A on top:  A carries 0   -> risk 0 − 2 = −2
           B carries 6   -> risk 6 − 7 = −1
           largest = −1

B on top:  B carries 0   -> risk 0 − 7 = −7
           A carries 3   -> risk 3 − 2 =  1
           largest = 1
```

A on top is better (−1 < 1).

**Then with letters.**

```
A on top:  A's risk = −S_A,   B's risk = W_A − S_B
B on top:  B's risk = −S_B,   A's risk = W_B − S_A
```

The top acrobat's risk can never decide the comparison: `−S_A ≤ W_B − S_A` and `−S_B ≤ W_A − S_B`. So it comes down to the bottom acrobat in each order. A on top is better when:

```
W_A − S_B  <  W_B − S_A     →     W_A + S_A  <  W_B + S_B
```

**Sort by weight + strength, ascending: the smallest sum goes on top.**

If other acrobats stand above the pair (total weight X), every risk above gets `+ X`. It cancels out of the comparison, so the key is the same. Everyone below the pair carries the same total either way, so their risks don't change.

## Traps

- **Own weight goes in after the risk.** Walking from the top: compute this acrobat's risk with the current `weightAbove`, then add their weight. (In Lab 4 it was the other way round: a task's time was added to the clock before computing its cost.)
- **`Long.MIN_VALUE` for the max,** because risks can be negative (test 2).
- **Ties keep input order.** `List.sort` is stable, so equal sums stay in input order. With bubble sort, swap only on strict `>`. The aud's exchange sort is not stable.
- **Ids are 1-based.** Use `i + 1`, not `i++` (that skips every other acrobat).
- **`long` everywhere** (test 6).

The classic name of this problem is "Cow Acrobats" (USACO / POJ 3045).
