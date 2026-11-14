# Lab: choose as many tasks as possible, then minimize cost

You are given N tasks and a total available time L. For each task i, its execution time (Ti) and its priority weight (Wi) are given. All execution times Ti are distinct.

The tasks are executed sequentially (one after another): the first one starts at t = 0 and every next one starts right after the previous one finishes. All chosen tasks must finish no later than time L, so not all tasks have to be executed.

First, as many tasks as possible must be chosen. If there are several such choices, the one with the smallest total execution time is taken (since all Ti are distinct, that choice is unique).

The execution cost of an individual task is calculated as: Cost = (start time of the task) × (priority weight)

The chosen tasks are executed in an optimal order so that the total cost is minimal. Write a program that finds the number of chosen tasks and the minimum possible total cost for them.

## Input

The first line contains two integers: the number of tasks N and the total time L. Each of the next N lines contains two space-separated integers: the execution time Ti and the priority weight Wi of a task.

Example:

```
4 10
6 2
3 5
2 1
4 3
```

## Output

The first line prints the number of chosen tasks. The second line prints the minimum possible total cost of the chosen tasks.

Example:

```
3
16
```

## Explanation

The shortest tasks have Ti = 2, 3, 4 (total 9 ≤ 10). Adding the task with Ti = 6 would give 15 > 10, so 3 tasks are chosen.

Optimal sequence: (T=3, W=5), (T=4, W=3), (T=2, W=1).
- (T=3, W=5) starts at t = 0. Cost = 0 × 5 = 0.
- (T=4, W=3) starts at t = 3. Cost = 3 × 3 = 9.
- (T=2, W=1) starts at t = 7. Cost = 7 × 1 = 7.

Total cost = 0 + 9 + 7 = 16.

## Tests

### Test 1

Input:
```
4 10
6 2
3 5
2 1
4 3
```
Result:
```
3
16
```

### Test 2

Input:
```
2 1
5 2
3 4
```
Result:
```
0
0
```

### Test 3

Input:
```
4 100
6 2
3 5
2 1
4 3
```
Result:
```
4
34
```

### Test 4

Input:
```
4 9
6 2
3 5
2 1
4 3
```
Result:
```
3
16
```

### Test 5

Input:
```
1 7
5 3
```
Result:
```
1
0
```

### Test 6

Input:
```
1 4
5 3
```
Result:
```
0
0
```

### Test 7

Input:
```
4 8
5 100
1 1
2 1
3 1
```
Result:
```
3
4
```

### Test 8

Input:
```
4 5
1 1
2 2
3 3
4 4
```
Result:
```
2
2
```

### Test 9

Input:
```
6 15
7 2
1 9
5 5
3 1
9 4
2 8
```
Result:
```
4
31
```

### Test 10

Input:
```
3 2000000000
1000000000 1000000000
999999999 1000000000
999999998 1000000000
```
Result:
```
2
999999998000000000
```

### Extra test (not from the checker)

Choosing by T / W instead of by T gets the count wrong here: the task with T = 4 has the best ratio but blocks the other two.

Input:
```
3 5
4 100
2 1
3 1
```
Result:
```
2
2
```
