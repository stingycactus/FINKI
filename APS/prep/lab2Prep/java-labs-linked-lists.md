# Lab: linked lists (Part A: SLL outliers, Part B: DLL circular insertion)

Work through the exercises in order. Each one adds one idea, and each has the expected output so you can check yourself. The full solution for each part is at the end of that part. Try the exercises before you look at it.

---

# 0. Before you start

## 0.1 The classes the lab gives you

The lab pastes `SLL`/`DLL` code above the answer box. **Read it first and use exactly its names.** This guide assumes the usual FINKI versions:

| | Fields | Methods you'll use |
|---|---|---|
| `SLLNode<E>` | `element`, `succ` | (none, you use the fields directly) |
| `SLL<E>` | `first` (private) | `getFirst()`, `insertLast(o)`, `delete(node)`, `toString()` |
| `DLLNode<E>` | `element`, `pred`, `succ` | (none) |
| `DLL<E>` | `first`, `last` (private) | `getFirst()`, `getLast()`, `insertLast(o)`, `insertAfter(o, node)`, `delete(node)`, `toString()` |

- `succ` = next node and `pred` = previous node. These are the same arrows as `getNext()` in your own `Node`, just under different names.
- The node fields are `protected`, and `Main` sits in the same file (same package), so you can write `p.element` and `p.succ` directly. You don't need getters.
- `toString()` already prints `a->b->c` (SLL) or `a<->b<->c` (DLL), and `Prazna lista!!!` for an empty list. **Never write your own printing.** Just `System.out.println(list)`.

## 0.2 Reading input

Every value is a separate token (spaces or newlines don't matter), so `Scanner` tokens are enough:

```java
int n = in.nextInt();         // a number
String dir = in.next();       // a word like left / right
double x = Double.parseDouble(in.next());   // a real number
```

Use `Double.parseDouble(in.next())` for real numbers: it always reads `2.5` with a dot, whatever the machine's language settings.

---

# Part A: two SLLs, outliers

**Task in one sentence:** walk both lists side by side. When the pair is too far apart (`|a - b| > x`), relabel the node in list 1 as `Outlier a` and delete the node from list 2. Leftover nodes in list 1 become `Unchecked a`.

## A1. Build and print the two lists

Read `N` and the N elements into list 1, then `M` and the M elements into list 2, then `x`. Print both lists.

**Design decision:** list 1 will later hold text like `Outlier 10`, so make it `SLL<String>` and read its elements with `in.next()`. List 2 only ever holds numbers, so it can be `SLL<Integer>`.

Test input:
```
2
10
20
2
1
20
2
```
Expected:
```
10->20
1->20
```

## A2. Walk both lists side by side

Use two pointers, one per list, and move them together. Print each pair.

```java
SLLNode<String> p1 = list1.getFirst();
SLLNode<Integer> p2 = list2.getFirst();
while (p1 != null && p2 != null) {
    // print the pair here
    p1 = p1.succ;
    p2 = p2.succ;
}
```

The loop stops as soon as **either** list runs out. That's exactly "pairs at the same position".

Expected for the same input: pairs `(10, 1)` and `(20, 20)`.

## A3. Detect outliers (no deleting yet)

List 1 holds strings, so convert before comparing: `int a = Integer.parseInt(p1.element);`.

- The condition is `Math.abs(a - b) > x`, with **strict** `>`. A difference of exactly `x` is **not** an outlier.
- Relabel with `p1.element = "Outlier " + a;`. Use `a`, the original number, and not `p1.element` after you've changed it.

Expected after this step (list 2 not changed yet):
```
Outlier 10->20
1->20
```

## A4. Delete from list 2 while walking (the key trick)

The rule "compare by original positions" just means **deleting a node from list 2 must not shift the pairs**. Pointers give you that for free, as long as you save the next node *before* deleting:

```java
SLLNode<Integer> next2 = p2.succ;   // 1. remember where to go next
if (/* outlier */) {
    ...
    list2.delete(p2);                 // 2. unlink p2 from list 2
}
p1 = p1.succ;
p2 = next2;                          // 3. continue from the saved node
```

Why this works: the next node of list 2 is still the next node in the original order, because deleting `p2` only redraws the arrow of the node *before* it.

Do you need `next2`? With the FINKI `delete`, `p2.succ` still points to the right node after deleting, so it would happen to work. But saving it first is the safe habit, and it makes the intent obvious.

Expected now:
```
Outlier 10->20
20
```
That's the example from the lab text.

## A5. Unchecked leftovers

After the side-by-side loop, `p1` is either `null` (done) or the first **unpaired** node of list 1. Continue with `p1` alone:

```java
while (p1 != null) {
    p1.element = "Unchecked " + p1.element;
    p1 = p1.succ;
}
```

If list 2 is longer, do nothing: its remaining nodes stay as they are.

## A6. Test cases (all verified)

| Input (one value per line) | Output |
|---|---|
| `1 10 1 1 2` (lab sample) | `Outlier 10` / `Prazna lista!!!` |
| `2 10 20 2 1 20 2` | `Outlier 10->20` / `20` |
| `3 5 7 9 2 5 100 0.5` | `5->Outlier 7->Unchecked 9` / `5` |
| `1 3 1 5 2` (difference exactly x) | `3` / `5` |
| `0 2 1 2 3` (empty first list) | `Prazna lista!!!` / `1->2` |
| `2 -4 10 2 -1 10 2.5` | `Outlier -4->10` / `10` |
| `3 1 2 3 3 10 20 30 1` (everything deleted) | `Outlier 1->Outlier 2->Outlier 3` / `Prazna lista!!!` |

## A: Traps

- `>` not `>=`. Exactly `x` stays unchanged.
- Keep the **original** `a` in the label.
- Don't delete from list 1, only relabel it.
- `x` is real: read it as `double`.
- `N` or `M` can be 0. The `p1 != null && p2 != null` check handles it.

## A: Full solution (the `main`, below the given classes)

```java
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        SLL<String> list1 = new SLL<>();
        for (int i = 0; i < n; i++) {
            list1.insertLast(in.next());
        }

        int m = in.nextInt();
        SLL<Integer> list2 = new SLL<>();
        for (int i = 0; i < m; i++) {
            list2.insertLast(in.nextInt());
        }

        double x = Double.parseDouble(in.next());

        SLLNode<String> p1 = list1.getFirst();
        SLLNode<Integer> p2 = list2.getFirst();
        while (p1 != null && p2 != null) {
            int a = Integer.parseInt(p1.element);
            int b = p2.element;
            SLLNode<Integer> next2 = p2.succ;     // save BEFORE deleting
            if (Math.abs(a - b) > x) {
                p1.element = "Outlier " + a;
                list2.delete(p2);
            }
            p1 = p1.succ;
            p2 = next2;
        }
        while (p1 != null) {
            p1.element = "Unchecked " + p1.element;
            p1 = p1.succ;
        }

        System.out.println(list1);
        System.out.println(list2);
    }
}
```

`import java.util.Scanner;` goes at the very top of the file.

---

# Part B: DLL, circular insertion, then a final command

**Task in one sentence:** for each command, find a node by counting around the list (wrapping), and insert after it. Then walk the list once and add `addWhat` to every `(everyWhich + 1)`-th node.

The **list itself is not circular**. It's a normal DLL with `first` and `last`. Only the counting wraps around.

## B1. Build and print

Read `M` and the M elements into a `DLL<Integer>` with `insertLast`. Print it.

Also keep a variable `int size = M;`. You'll need the current length for every command, and you'll do `size++` after each insert.

## B2. Circular counting on paper first

Counting starts at **1** on the start node, so the node you land on is `k - 1` moves away. Since the counting wraps, moving `size` times brings you back to where you started, so you only need the remainder:

```java
int steps = (k - 1) % size;
```

- `left`: start at `getFirst()` and move `steps` times with `succ` (to the right).
- `right`: start at `getLast()` and move `steps` times with `pred` (to the left).

**Exercise:** for the list `1<->2<->3` (`size = 3`), which node do you land on? Answers below the table.

| Command | Your answer |
|---|---|
| `left 1` | |
| `left 4` | |
| `right 1` | |
| `right 4` | |
| `left 8` | |
| `right 3` | |

Answers:
- `left 1`: `(1 - 1) % 3 = 0` steps, so **1**.
- `left 4`: `3 % 3 = 0` steps, so **1** (it wrapped once).
- `right 1`: 0 steps from the last node, so **3**.
- `right 4`: 0 steps from the last node, so **3**.
- `left 8`: `7 % 3 = 1` step right from 1, so **2**.
- `right 3`: `2 % 3 = 2` steps left from 3, so **1**.

The `%` matters: `k` can be much larger than the list, and the remainder saves you from walking around it many times.

## B3. Insert after the selected node

```java
list.insertAfter(element, node);
size++;
```

The lab's examples, which you should reproduce:
- `1<->2<->3` with `9 left 4` gives `1<->9<->2<->3`.
- `1<->2<->3` with `9 right 4` gives `1<->2<->3<->9`.

The given `insertAfter` already handles inserting after the last node (it updates `last`), so you don't need a special case.

**Exercise:** start from `1<->2<->3` and apply these three commands one after another. Remember that `size` grows each time.
```
9 right 1
8 left 5
7 right 2
```
Expected: `1<->8<->2<->3<->7<->9`.

## B4. The final command: `everyWhich addWhat`

Starting at the first node: skip `everyWhich` nodes, add `addWhat` to the node you land on, then continue from the node **after** it. Stop when you run off the end (no wrapping).

Trace for `1<->2<->3<->4<->5<->6<->7` with `2 3`:
- At 1: skip 1 and 2, land on 3, add 3 → **6**. Continue at 4.
- At 4: skip 4 and 5, land on 6, add 3 → **9**. Continue at 7.
- At 7: skip 7, run off the end, stop.

Result: `1<->2<->6<->4<->5<->9<->7` (the lab's example).

The loop:

```java
DLLNode<Integer> p = list.getFirst();
while (p != null) {
    for (int i = 0; i < everyWhich && p != null; i++) {
        p = p.succ;                 // skip everyWhich nodes
    }
    if (p == null) break;           // ran off the end
    p.element += addWhat;           // update the node you landed on
    p = p.succ;                     // continue after it
}
```

The `&& p != null` inside the `for` is important: without it, skipping past the end crashes with a `NullPointerException`.

## B5. Test cases (all verified)

| Input | Line 1 | Line 2 |
|---|---|---|
| `1 / 4 / 1 / 9 left 1 / 1 3` (lab sample) | `4<->9` | `4<->12` |
| `3 / 1 2 3 / 1 / 9 left 4 / 5 1` | `1<->9<->2<->3` | `1<->9<->2<->3` |
| `3 / 1 2 3 / 1 / 9 right 4 / 5 1` | `1<->2<->3<->9` | `1<->2<->3<->9` |
| `7 / 1 2 3 4 5 6 7 / 0 / 2 3` | `1<->2<->3<->4<->5<->6<->7` | `1<->2<->6<->4<->5<->9<->7` |
| `3 / 1 2 3 / 3 / 9 right 1 / 8 left 5 / 7 right 2 / 1 10` | `1<->8<->2<->3<->7<->9` | `1<->18<->2<->13<->7<->19` |

(`/` separates lines. Put each element of the initial list on its own line in the real input.)

## B: Traps

- `N` can be 0. Then the first printed line is just the original list.
- Update `size` after every insert, because the next command counts on the **current** list.
- `left` moves with `succ` from `first`, and `right` moves with `pred` from `last`.
- In the final command, continue from the node **after** the updated one, and never wrap.

## B: Full solution (the `main`, below the given classes)

```java
public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int m = in.nextInt();
        DLL<Integer> list = new DLL<>();
        for (int i = 0; i < m; i++) {
            list.insertLast(in.nextInt());
        }
        int size = m;

        int n = in.nextInt();
        for (int c = 0; c < n; c++) {
            int element = in.nextInt();
            String fromWhere = in.next();
            int k = in.nextInt();

            int steps = (k - 1) % size;
            DLLNode<Integer> node;
            if (fromWhere.equals("left")) {
                node = list.getFirst();
                for (int i = 0; i < steps; i++) node = node.succ;
            } else {
                node = list.getLast();
                for (int i = 0; i < steps; i++) node = node.pred;
            }
            list.insertAfter(element, node);
            size++;
        }
        System.out.println(list);

        int everyWhich = in.nextInt();
        int addWhat = in.nextInt();
        DLLNode<Integer> p = list.getFirst();
        while (p != null) {
            for (int i = 0; i < everyWhich && p != null; i++) {
                p = p.succ;
            }
            if (p == null) break;
            p.element += addWhat;
            p = p.succ;
        }
        System.out.println(list);
    }
}
```

## B: Variant you might get (delete instead of add)

The Macedonian version of this task has a different final command: just `everyWhich`. Starting at the **last** node and moving **left**, skip `everyWhich` nodes and **delete** the next one. Continue from the node to the left of the deleted one, with no wrapping. Example: `1..7` with `2` gives `1<->3<->4<->6<->7`.

It's the same loop mirrored: start at `getLast()`, move with `pred`, and save the left neighbour before deleting:

```java
int everyWhich = in.nextInt();
DLLNode<Integer> p = list.getLast();
while (p != null) {
    for (int i = 0; i < everyWhich && p != null; i++) {
        p = p.pred;
    }
    if (p == null) break;
    DLLNode<Integer> left = p.pred;   // save BEFORE deleting
    list.delete(p);
    p = left;
}
```

Verified: `1..7` with `2` gives `1<->3<->4<->6<->7`, and `1<->9<->2<->3` with `1` gives `9<->3`.
