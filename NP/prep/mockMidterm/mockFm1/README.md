# Mock midterm 1 – Task 1 (entry)

Define a class `GradeReport` for evaluating the results of students on an exam with several tasks. The class should have the following functionalities:

* Constructor `GradeReport(List<Integer> maxPoints)` with one argument – the maximum number of points for each task of the exam, in order.
* Method `public void evaluate(InputStream is, OutputStream os)` which reads from the input stream the points of the students (for each student, the information is provided on a separate line in the format `INDEX P1 P2 … Pn`), and outputs to the output stream the students and the percentage of the total maximum points they won, sorted in descending order by the percentage. Students with an equal percentage are sorted by their index.
  * If a student has more points on a task than the maximum for that task, only the maximum is counted.
  * A student may have points for fewer tasks than there are; the missing tasks are counted as 0.

The class `GradeReportTest` is given (see `src`).

## Examples

Input
```text
10 20 30 40
211001 10 20 30 40
211002 5 25 30
211003 10 10 10 10
211004 0 20 30 5
211005 12 0 0 0
```
Result
```text
211001 100.00%
211002 55.00%
211004 55.00%
211003 40.00%
211005 10.00%
```

Input
```text
5 5 5
b2 3
c3 6 6 6
d4 2 4
a1 5 5 5
e5 0 0 0
```
Result
```text
a1 100.00%
c3 100.00%
d4 40.00%
b2 20.00%
e5 0.00%
```

