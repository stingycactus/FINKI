# Mock midterm 1.1 – Task 1 (entry)

Define a class `MovieRatings` for processing the ratings that users gave to movies. The class should have the following functionalities:

* Constructor `MovieRatings(int minRatings)` with one argument – the minimum number of valid ratings a movie must have to appear in the result.
* Method `public void evaluate(InputStream is, OutputStream os)` which reads from the input stream the ratings of the movies (for each movie, the information is provided on a separate line in the format `TITLE R1 R2 … Rn`), and outputs to the output stream the movies with their average rating and the number of valid ratings, sorted in descending order by the average rating. Movies with an equal average are sorted in descending order by the number of valid ratings, and then by title.
  * A rating is valid only if it is between 1 and 10 (inclusive). Invalid ratings are ignored.
  * Movies with fewer than `minRatings` valid ratings are not printed.
  * Each movie is printed in the format `%-10s %5.2f (%d)`.

The class `MovieRatingsTest` is given (see `src`).

## Examples

Input
```text
3
Inception 9 10 8 9
Titanic 7 8 6
Avatar 10 11 9 0 8
Shrek 9 9 9
Cars 5 6
Up 8 10 8 9
Jaws 9 9 9 9
```
Result
```text
Inception   9.00 (4)
Jaws        9.00 (4)
Avatar      9.00 (3)
Shrek       9.00 (3)
Up          8.75 (4)
Titanic     7.00 (3)
```

Input
```text
1
matrix 10
alien 2 15 -3 4
heat 0 11
seven 10 10
fargo 6 7 8
```
Result
```text
seven      10.00 (2)
matrix     10.00 (1)
fargo       7.00 (3)
alien       3.00 (2)
```
