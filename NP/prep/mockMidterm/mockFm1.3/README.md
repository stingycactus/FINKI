# Mock midterm 1.3 – Task 1 (entry + generics)

Define a generic class `Leaderboard<T>` that keeps elements that can be compared with each other (the type `T` must implement `Comparable<T>`). The class should have the following functionalities:

* `void add(T item)` – adds an element.
* `List<T> top(int n)` – returns the `n` largest elements, in descending order. If there are fewer than `n` elements, all of them are returned.
* `Leaderboard<T> filter(Predicate<? super T> condition)` – returns a new leaderboard with only the elements that satisfy the condition.
* `void print(OutputStream os)` – prints all elements in descending order, each in the format `%d. %s` (rank starting from 1, the element).

Define a class `Player` that implements `Comparable<Player>`, with a name, number of wins and number of losses.

* The points of a player are `3 * wins - losses`.
* Players are compared by points. If the points are equal, the player with fewer losses is greater.
* `toString()` returns `NAME (POINTS)`.

Define a class `PlayerReader` with a static method `List<Player> read(InputStream is)` that reads players from the input stream, each on a separate line in the format `NAME WINS LOSSES`. If a line does not have exactly 3 parts, or the wins/losses are not integers, `Invalid line: LINE` is printed to standard output and **the reading should not stop**.

The class `LeaderboardTest` is given (see `src`). Complete the two lambda expressions marked with TODO.

## Examples

Input
```text
5 3 9 1 7 4
3
ana 5 2
marko 3 4
ivana 4 0
petar 2 0
bojan x 3
sara 5 2 1
luka 1 5
mia 6 5
```
Result
```text
=== NUMBERS ===
1. 9
2. 7
3. 5
4. 4
5. 3
6. 1
=== TOP 3 NUMBERS ===
[9, 7, 5]
=== READING PLAYERS ===
Invalid line: bojan x 3
Invalid line: sara 5 2 1
=== PLAYERS ===
1. ana (13)
2. mia (13)
3. ivana (12)
4. petar (6)
5. marko (5)
6. luka (-2)
=== TOP 3 PLAYERS ===
[ana (13), mia (13), ivana (12)]
=== PLAYERS WITH MORE WINS THAN LOSSES ===
1. ana (13)
2. mia (13)
3. ivana (12)
4. petar (6)
=== EVEN NUMBERS ===
1. 4
```

Input
```text
10 20
5
bob 1 1
alice 2 4
```
Result
```text
=== NUMBERS ===
1. 20
2. 10
=== TOP 5 NUMBERS ===
[20, 10]
=== READING PLAYERS ===
=== PLAYERS ===
1. bob (2)
2. alice (2)
=== TOP 5 PLAYERS ===
[bob (2), alice (2)]
=== PLAYERS WITH MORE WINS THAN LOSSES ===
=== EVEN NUMBERS ===
1. 20
2. 10
```
