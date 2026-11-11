# Lab 4, part B

You are given N tasks that must be executed sequentially (one after another). For each task i, its execution time (Ti) and its priority weight (Wi) are given.

The first task in the sequence begins execution at time t = 0. Every subsequent task begins immediately after the preceding task completes.

The execution cost of an individual task is calculated as: Cost = (finish time of the task) × (priority weight)

Write a program to find an optimal sequence for executing all tasks such that the total cost (the sum of costs across all tasks) is minimized. If several sequences give the same minimum cost, print the one in which tasks with an equal ratio Ti/Wi are ordered by their position in the input (the one entered earlier goes first).

## Input

The first line contains an integer N, the number of tasks. Each of the next N lines contains two space-separated integers: the execution time Ti and the priority weight Wi of a task.

Example:

```
3
2 3
1 2
4 1
```

## Output

The first line prints the minimum possible total cost. The second line prints the numbers of the tasks (from 1 to N, in input order), separated by spaces, in the order in which they are executed.

Example:

```
18
2 1 3
```

## Explanation

Optimal sequence: task 2 (T=1, W=2), task 1 (T=2, W=3), task 3 (T=4, W=1).
- Task 2 finishes at t = 1. Cost = 1 × 2 = 2.
- Task 1 finishes at t = 1 + 2 = 3. Cost = 3 × 3 = 9.
- Task 3 finishes at t = 3 + 4 = 7. Cost = 7 × 1 = 7.

Total cost = 2 + 9 + 7 = 18.

## For example

### Test 1

Input:
```
3
2 3
1 2
4 1
```
Result:
```
18
2 1 3
```

### Test 2

Input:
```
1
5 7
```
Result:
```
35
1
```

### Test 3

Input:
```
3
2 4
1 2
3 6
```
Result:
```
50
1 2 3
```

### Test 4

Input:
```
4
4 2
1 1
2 1
1 2
```
Result:
```
24
4 2 1 3
```

### Test 5

Input:
```
4
3 2
3 2
3 2
3 2
```
Result:
```
60
1 2 3 4
```

### Test 6

Input:
```
4
5 1
2 1
8 1
1 1
```
Result:
```
28
4 2 1 3
```

### Test 7

Input:
```
4
4 2
4 9
4 5
4 1
```
Result:
```
116
2 3 1 4
```

### Test 8

Input:
```
4
1 10
2 5
4 2
8 1
```
Result:
```
54
1 2 3 4
```

### Test 9

Input:
```
4
8 1
4 2
2 5
1 10
```
Result:
```
54
4 3 2 1
```

### Test 10

Input:
```
3
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000
```
Result:
```
6000000000000000000
1 2 3
```
