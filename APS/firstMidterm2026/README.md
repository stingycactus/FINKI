# First midterm 2026: coding tasks (not 100% 1:1)

## 1. Entry tasks

### 1.1 ThirdOccurrenceToFront (termin 1, group A, entry, SLL)

You get a singly linked list of numbers and one number `x`.

- Count how many times `x` is in the list.
- If it's there **at least 3 times**: find the **3rd** `x`. Everything that comes **after** it gets moved to the **front** of the list, one element at a time with `insertFirst`. The 3rd `x` itself stays where it is.
- If it's there fewer than 3 times: print a message that there aren't 3 nodes with value `x`.

**Input:**
```
8
5 3 1 3 2 3 7 8
3
```
**Output:**
```
8->7->5->3->1->3->2->3
```

**What happens:**
```
5 3 1 3 2 3 7 8      the 3rd 3 is the one before 7, so 7 and 8 have to move
7 5 3 1 3 2 3 8      insertFirst(7)
8 7 5 3 1 3 2 3      insertFirst(8)
```

Because each element goes to the very front, the moved part comes out reversed (8 before 7).

---

### 1.2 SecondOccurrenceToEnd (termin 1, group B, entry, SLL)

You get a singly linked list of numbers and one number `x`.

- Count how many times `x` is in the list.
- If it's there **fewer than 2 times**: don't change the list.
- Otherwise: take the elements from the **start** of the list one by one and move each to the **end**, until the **2nd** `x` is at the front. The 2nd `x` itself doesn't move.

Print the list.

**Input:**
```
6
1 5 2 5 3 4
5
```
**Output:**
```
5->3->4->1->5->2
```

**What happens:**
```
1 5 2 5 3 4      move 1 to the end
5 2 5 3 4 1      move 5 to the end (1st x)
2 5 3 4 1 5      move 2 to the end
5 3 4 1 5 2      the 2nd x is at the front, stop
```

---

### 1.3 BeforeSecondLastToEnd (termin 2, group A, entry, DLL)

You get a doubly linked list of N numbers, then one number X.

- Count how many times X is in the list.
- If it's there **fewer than 2 times**, print only: `Node so vrednost X ne se pojavuva barem 2 pati.`
- Otherwise:
  1. print the list as it is
  2. find the **second-to-last** X (the last X but one)
  3. move **everything in front of that X** to the **end** of the list (that X itself doesn't move), and print the new list on a second line

**Input:**
```
7
1 2 3 2 4 2 5
2
```
**Output:**
```
1<->2<->3<->2<->4<->2<->5
2<->4<->2<->5<->1<->2<->3
```

**What happens:**
```
1 2 3 2 4 2 5        2s at positions 1, 3, 5 → the second-to-last is at position 3
                     in front of it: 1 2 3 → they go to the end
2 4 2 5 1 2 3
```

---

### 1.4 ThirdFromEndToFront (termin 2, group B, entry, DLL)

You get a doubly linked list of N numbers, then one number X. You work **from the end of the list to the start**.

- Count how many times X is in the list.
- If it's there **fewer than 3 times**: print only a message saying X doesn't appear at least 3 times.
- Otherwise: going from the end, find the **3rd** X. Every element after it gets moved to the **front** of the list, in the order you meet them walking from the end. The 3rd X itself stays where it is. Print the original list, then the new list on a second line.

**Input:**
```
6
1 2 2 4 2 5
2
```
**Output:**
```
1<->2<->2<->4<->2<->5
5<->2<->4<->2<->1<->2
```

**What happens:**
```
1 2 2 4 2 5      from the end, 2s at positions 4, 2, 1 → the 3rd is at position 1
                 after it: 2 4 2 5 → walking from the end you meet them as 5 2 4 2
5 2 4 2 1 2      they go to the front in that order; 1 2 stays behind them
```

## Advanced tasks

### 2. MeetingSelection (advanced, greedy)

You get N intervals. Each has a **start** and an **end** time, and they're numbered **1, 2, 3, …** in the order they're given.

Pick **as many intervals as possible** so that no two of them overlap. Print how many you picked, then their numbers.

Touching is allowed: an interval can start at the exact moment the previous one ends, so `1 4` and `4 7` can both be picked (start ≥ previous end).

**Input:**
```
6
1 4
2 5
4 7
3 8
7 9
8 10
```
**Output:**
```
3
1 3 5
```

**What happens:** the intervals are numbered 1 to 6 in input order. Intervals 1 (1–4), 3 (4–7) and 5 (7–9) are picked. They touch at 4 and at 7, which is allowed, and there's no way to fit 4 intervals.

---

### 3. CursorEditor (advanced)

You get one string of keystrokes, typed into an empty editor with a cursor. Rebuild the text that's on the screen at the end.

- **letter, digit or space:** it's typed at the cursor, and the cursor moves past it
- `<`: the cursor moves **one place left**. If it's already at the start, nothing happens.
- `>`: the cursor moves **one place right**. If it's already at the end, nothing happens.
- `#`: deletes the character **just left of the cursor**. If there's nothing there, nothing happens.

At the end, print the text. If the text is empty, print an empty line.

**Input:**
```
helo<l
```
**Output:**
```
hello
```

**What happens:**
```
helo|        type h e l o
hel|o        <  cursor goes back one place
hell|o       type l at the cursor
```

**Input:**
```
cat#r
```
**Output:**
```
car
```

**What happens:**
```
cat|         type c a t
ca|          #  deletes the t
car|         type r
```

**Input:**
```
ac<b>d
```
**Output:**
```
abcd
```

**What happens:**
```
ac|          type a c
a|c          <  cursor goes back one place
ab|c         type b at the cursor
abc|         >  cursor goes forward one place
abcd|        type d
```
