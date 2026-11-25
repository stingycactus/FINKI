# Lab 5A: Swapped places (counting inversions)

After the first APS midterm, `n` students are ranked from 1 to `n` (the student with rank 1 has the most points; no two students share a rank). After the second midterm a new ranking list is made. The teaching assistant wrote the students down in the order of the new ranking list and, for each student, wrote their rank from the **first** midterm. This gives a sequence of `n` distinct integers from 1 to `n`.

Two students have **swapped places** if the student who is higher on the new ranking list had a worse (larger) rank on the first midterm. In other words, count the pairs `(i, j)` with `i < j` such that `a[i] > a[j]`.

Write a program that computes the number of pairs of students who swapped places. There can be up to 70 000 students, so the program must run in `O(n log n)` time in the worst case.

## Input

- The first line contains the number `n` (1 ≤ `n` ≤ 70 000), the number of students.
- The second line contains `n` distinct integers from 1 to `n`: the first-midterm ranks, in the order of the new ranking list.

## Output

Print the number of pairs of students who swapped places on a single line.

**Note:** the result can be larger than the maximum value of `int`.

## Example

Input:

```
5
3 1 5 2 4
```

Output:

```
4
```

The pairs are (3, 1), (3, 2), (5, 2) and (5, 4).
