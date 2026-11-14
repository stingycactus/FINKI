# Mock midterm 1 – Task 3

Define a generic interface `Transformer` with a single method `R transform(T input)` which transforms an object of type `T` into an object of type `R`.

Define a generic class `DataSet` which stores a list of elements that are comparable to each other. The class should define the following methods:

* Constructor `DataSet()`
* Method `void add(T element)` – for adding an element to the data set
* Method `DataSet filter(Predicate condition)` – returns a new data set composed only of the elements that satisfy the condition
* Method `DataSet map(Transformer transformer)` – returns a new data set composed of the transformed elements. The transformed elements must also be comparable.
* Method `T max()` – returns the largest element. If the data set is empty, throws an exception of type `EmptyDataSetException` with the message `DataSet is empty`.
* Method `toString()` – according to the test examples

Define a class `Stats` with a single generic static method `maxOfAll` that accepts a list of data sets and returns the largest element of all of them. Empty data sets are skipped. If all data sets are empty, an `EmptyDataSetException` is thrown.

In the `main` function, define with lambda expressions:

* a condition that keeps only the even numbers
* a transformer that transforms a number into its square
* a transformer that transforms a word into its length
* a condition that keeps only the words longer than `minLength`

The class `DataSetTest` is given (see `src`); only the four marked lines in it may be changed.

## Examples

Input
```text
5 12 7 20 3 8
banana kiwi apple fig cherry
4
```
Result
```text
=== NUMBERS ===
[3, 5, 7, 8, 12, 20]
even: [8, 12, 20]
squares: [9, 25, 49, 64, 144, 400]
=== WORDS ===
[apple, banana, cherry, fig, kiwi]
lengths: [3, 4, 5, 6, 6]
longer than 4: [apple, banana, cherry]
=== MAX ===
max number: 20
max word: kiwi
max of even and squares: 400
max even: 20
```

Input
```text
9 1 3
sun moon star
5
```
Result
```text
=== NUMBERS ===
[1, 3, 9]
even: []
squares: [1, 9, 81]
=== WORDS ===
[moon, star, sun]
lengths: [3, 4, 4]
longer than 5: []
=== MAX ===
max number: 9
max word: sun
max of even and squares: 81
DataSet is empty
```

