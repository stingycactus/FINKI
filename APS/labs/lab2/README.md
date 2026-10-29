# Lab 2: Linked lists

Two tasks: 2.1 (singly linked lists, outliers) and 2.2 (doubly linked list, circular insertion). Each has the statement, the test cases (input and expected output), and notes on the tricky tests.

## Lab 2.1: Two singly linked lists, outliers

### Task

You are given two singly linked lists whose nodes contain integers. Additionally, you are given a non-negative real number x.

For each node in the first list, compare its value a with the value b at the same position in the second list. If a is outside the interval [b − x, b + x], that is, if |a − b| > x, replace its value in the first list with the text `Outlier a` and remove the corresponding node from the second list. Keep the original value of a in the label.

Compare nodes by their original positions. Removing a node from the second list does not change the pairs used in later comparisons. If the difference is exactly x, both nodes remain unchanged.

If the first list is longer than the second, replace the value of every unpaired node in the first list with `Unchecked a`, where a is its original value. If the second list is longer, its remaining nodes stay unchanged.

After the changes, print both lists, first the first list and then the second.

**Original positions example:** For the first list `10->20`, the second list `1->20`, and `x = 2`, the resulting first list is `Outlier 10->20` and the resulting second list is `20`.

**Example explained:** First, compare the nodes with values 10 and 1. Their difference exceeds 2, so replace 10 in the first list with `Outlier 10` and remove the node containing 1 from the second list. Next, compare the nodes containing 20 in both lists, because they occupied the same original position. Their difference is 0, so both remain unchanged.

**Input:** The first line contains the number of elements in the first list, N (N ≥ 0). The next N lines contain its elements. The next line contains the number of elements in the second list, M (M ≥ 0), followed by M lines containing its elements. The last line contains the real number x.

**Output:** Print the first list after the changes on the first line and the second list after the changes on the second line. Separate elements with `->`. For an empty list, print `Prazna lista!!!`.

### Test cases

#### Test 1

Input:
```
1
10
1
1
2
```
Expected:
```
Outlier 10
Prazna lista!!!
```

#### Test 2

Input:
```
0
0
0
```
Expected:
```
Prazna lista!!!
Prazna lista!!!
```

#### Test 3

Input:
```
2
3
-3
2
1
-1
2
```
Expected:
```
3->-3
1->-1
```

#### Test 4

Input:
```
3
1
2
3
3
1
7
3
0
```
Expected:
```
1->Outlier 2->3
1->3
```

#### Test 5

Input:
```
3
10
20
30
3
1
20
30
2
```
Expected:
```
Outlier 10->20->30
20->30
```

#### Test 6

Input:
```
5
5
12
7
20
1
3
6
8
9
2
```
Expected:
```
5->Outlier 12->7->Unchecked 20->Unchecked 1
6->9
```

#### Test 7

Input:
```
3
-5
0
8
4
-3
2
5
99
2.5
```
Expected:
```
-5->0->Outlier 8
-3->2->99
```

#### Test 8

Input:
```
4
7
-7
7
-7
4
0
0
0
0
0.5
```
Expected:
```
Outlier 7->Outlier -7->Outlier 7->Outlier -7
Prazna lista!!!
```

#### Test 9

Input:
```
4
2147483647
-2147483648
-2147483648
2147483647
4
-2147483648
2147483647
-2147483648
2147483647
4294967294.5
```
Expected:
```
Outlier 2147483647->Outlier -2147483648->-2147483648->2147483647
-2147483648->2147483647
```

#### Test 10

Input:
```
16
-8
-7
-6
-5
-4
-3
-2
-1
0
1
2
3
4
5
6
7
12
-12
-9
-6
-3
0
-7
-4
-1
2
5
-2
1
2.5
```
Expected:
```
Outlier -8->-7->-6->-5->Outlier -4->Outlier -3->-2->-1->0->Outlier 1->Outlier 2->3->Unchecked 4->Unchecked 5->Unchecked 6->Unchecked 7
-9->-6->-3->-4->-1->2->1
```

### Notes from the test cases

- **Test 9:** the values go up to the `int` limits (`2147483647` and `-2147483648`), so `a - b` overflows if `a` and `b` are `int`. Store and compare them as `long`.
- **Test 9:** `x` is larger than any `int` (`4294967294.5`), so read it as `double` (`Double.parseDouble(in.next())`).
- **Test 2:** both lists can be empty.

---

## Lab 2.2: Doubly linked list, circular insertion

### Task

You are given a nonempty doubly linked list of integers. Then N commands of the form `element fromWhere howManyPositions` are given, where `fromWhere` is either `left` or `right`, and `howManyPositions` is a positive integer.

For each command, select the node at position `howManyPositions` using circular counting from the first node for `left` or from the last node for `right`. Then insert a new node with value `element` after the selected node. Count using the current list, including nodes inserted by earlier commands.

After all insertions, a final command is given in the form `everyWhich addWhat`. Starting at the first node and moving right, skip `everyWhich` nodes and increase the next node's value by `addWhat`. Continue in the same way after the updated node until the end of the list, without wrapping. The value of `everyWhich` is a positive integer.

Print the list after all N insertion commands, then print it again after applying the final command.

**Circular counting explained:** For each command, counting starts at 1: at the first node if `left` is given, or at the last node if `right` is given. When moving from left to right, continue from the first node after the last; when moving from right to left, continue from the last node after the first. "Before" and "after" refer to the left-to-right order in the printed list, regardless of the counting direction.

**Circular counting example:** For the list `1<->2<->3` and command `9 left 4`, the node after which 9 should be inserted is the one with value 1, giving `1<->9<->2<->3`. If `9 right 4` is applied to the same initial list, the node after which 9 should be inserted is the one with value 3, giving `1<->2<->3<->9`. After each insertion, the next command uses the updated list length.

**Final command example:** For the list `1<->2<->3<->4<->5<->6<->7` and command `2 3`, the result is `1<->2<->6<->4<->5<->9<->7`.

**Final command explained:** Starting at the first node, count 2 nodes (the nodes with values 1 and 2) to reach the node with value 3. Increase this value by 3, then repeat the same procedure starting at the next node, whose value is 4.

**Input:** The first line contains M ≥ 1, and the next M lines contain the initial list elements. Then N ≥ 0 is given, followed by N lines containing the insertion commands. The last line contains the final command `everyWhich addWhat`.

**Output:** Print the list after all insertions on the first line and the list after the final command on the second line. Use the supplied `.toString()` method of the DLL class for both outputs.

### Test cases

#### Test 1

Input:
```
1
4
1
9 left 1
1 3
```
Expected:
```
4<->9
4<->12
```

#### Test 2

Input:
```
3
1
2
3
0
9 2
```
Expected:
```
1<->2<->3
1<->2<->3
```

#### Test 3

Input:
```
3
10
20
30
1
9 right 1
1 -2
```
Expected:
```
10<->20<->30<->9
10<->18<->30<->7
```

#### Test 4

Input:
```
3
1
2
3
1
9 left 7
2 3
```
Expected:
```
1<->9<->2<->3
1<->9<->5<->3
```

#### Test 5

Input:
```
3
1
2
3
2
9 right 6
8 left 8
5 -1
```
Expected:
```
1<->9<->2<->3<->8
1<->9<->2<->3<->8
```

#### Test 6

Input:
```
2
1
2
3
5 left 3
6 left 4
7 right 5
2 5
```
Expected:
```
1<->6<->5<->2<->7
1<->6<->10<->2<->7
```

#### Test 7

Input:
```
4
-5
0
-5
5
3
-9 right 3
0 left 2
5 right 1
1 -7
```
Expected:
```
-5<->0<->0<->-9<->-5<->5<->5
-5<->-7<->0<->-16<->-5<->-2<->5
```

#### Test 8

Input:
```
8
1
2
3
4
5
6
7
8
0
2 -1
```
Expected:
```
1<->2<->3<->4<->5<->6<->7<->8
1<->2<->2<->4<->5<->5<->7<->8
```

#### Test 9

Input:
```
3
1
2
3
2
9 left 1000000000000000000
7 right 999999999999999999
1000000000000000000 3
```
Expected:
```
1<->9<->7<->2<->3
1<->9<->7<->2<->3
```

#### Test 10

Input:
```
10
-5
-4
-3
-2
-1
0
1
2
3
4
10
9 left 21
-3 right 12
7 left 25
0 right 1
4 left 1
-8 right 38
6 left 17
2 right 36
5 left 55
-1 right 19
4 3
```
Expected:
```
-5<->-1<->5<->6<->4<->7<->9<->-4<->-3<->-2<->-1<->-8<->0<->1<->2<->3<->4<->-3<->2<->0
-5<->-1<->5<->6<->7<->7<->9<->-4<->-3<->1<->-1<->-8<->0<->1<->5<->3<->4<->-3<->2<->3
```

### Notes from the test cases

- **Test 9:** `howManyPositions` and `everyWhich` go up to `10^18`, which doesn't fit in an `int`. Read them with `in.nextLong()`.
- **Test 9:** walking `k - 1` steps one by one would take forever, so use the remainder: `int steps = (int) ((k - 1) % size);`. The result is smaller than `size`, so it fits in an `int`.
- **Tests 3, 5, 7, 8:** `addWhat` can be negative or make values negative.
- **Test 2:** `N` can be 0.
