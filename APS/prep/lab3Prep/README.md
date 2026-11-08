# APS prep: Lab 3 (queues and stacks: process scheduling)

**The labs:** three variants, all the same kind of task: a processor serves processes in turns of at most **T** time units, and you print the order in which they finish (`1. Name`, `2. Name`, ...).
- **Lab A:** one queue; an unfinished process goes to the back of the queue.
- **Lab B:** a queue of main processes, each with its own **stack** of subprocesses.
- **Lab C (other group):** a queue plus **one shared stack** of suspended processes, emptied into the queue every M rounds or when the queue runs empty.

The full lab texts are in Part 2, copied exactly as given.

**Based on:** Aud 05 "One dimensional data structures": stack (slides 3-14), queue (slides 19-28), Problem 3 student service (slides 29-31). Not needed: postfix homework (18), priority queue (32-33). Things the labs need that the aud doesn't show as code are marked **not in auds**.

**Allowed in the lab:** the aud's classes and `java.util` (e.g. `ArrayDeque`). Wherever java.util has a ready-made version, a **Modern:** line gives it. The checker runs Java 11.

Part 1 builds one practice program, a **print shop**: print jobs wait for one printer. Each exercise extends the previous one; comment out old code instead of deleting it. Section 1.8 is the method for turning any of these lab texts into code. Part 2 is the three labs.

**Workflow (IntelliJ):** a module `prep\lab3prep\practice` with one `Main.java` (all classes in it, only `Main` is `public`). Put input in `input.txt`: Run → Edit Configurations → Modify options → Redirect input. Not sure what type something returns? Cursor on it + **Ctrl+Shift+P** shows the type; **Ctrl+Alt+V** turns `q.peek()` into `Job j = q.peek();` with the right type.

---

# 1. Concepts

## 1.1 Stack: last in, first out (Aud 05 slides 3-13)

- `push(x)` puts x on top, `pop()` removes and returns the top, `peek()` reads the top without removing it.
- Two aud versions: `ArrayStack` (array, fixed max depth, slides 8-10) and `LinkedStack` (singly linked nodes, no limit, slides 11-13). `LinkedStack.push` is `addToFront`: `top = new SLLNode<>(x, top)`.
- `ArrayStack` when you know the maximum size (`push` on a full one throws `ArrayIndexOutOfBoundsException`); `LinkedStack` otherwise.
- `pop()` / `peek()` on an empty stack throw `NoSuchElementException`: check `isEmpty()` first.
- Trap: the posted `LinkedStack.java` ends with a stray `import NoSuchElementException;` line: `error: class, interface, or enum expected`. Delete it.
- **Modern:** `ArrayDeque<E>` has the same `push / pop / peek` and grows by itself. `java.util.Stack` (slide 14) works but is legacy (built on `Vector`).

```java
public void push(E x) {
    top = new SLLNode<>(x, top);
    size++;
}
public E pop() {
    if (top == null) throw new NoSuchElementException();
    E topElem = top.element;
    top = top.succ;
    size--;
    return topElem;
}
```

**Exercise:**
1. In `Main.java` write `SLLNode<E>`, the `Stack<E>` interface and `LinkedStack<E>` (aud version, with `size()` and its `toString()`). Add `import java.util.NoSuchElementException;`.
2. Push `"cover"`, `"page1"`, `"page2"` onto `LinkedStack<String> pile`. Print size and top, pop three times, print size:
   ```
   size 3, top page2
   page2
   page1
   cover
   size 0
   ```
3. Break it: pop a fourth time: `Exception in thread "main" java.util.NoSuchElementException` from `LinkedStack.pop`. Guard it with `if (!pile.isEmpty())`.

## 1.2 Queue: first in, first out (slides 19-28)

- `enqueue(x)` adds at the **rear** (end), `dequeue()` removes and returns the **front** (start), `peek()` reads the front. Stack vs queue is only this: a stack takes back the newest, a queue the oldest.
- `LinkedQueue` (slides 25-26) stores both `front` and `rear` (it updates `rear` on every enqueue), so both ends are instant. `dequeue` is just `front = front.succ`; when that empties the queue it also sets `rear = null`. One `succ` arrow per node is enough because nothing is ever removed at the rear.
- `ArrayQueue` (slides 23-24) is a circular array with a fixed capacity; `enqueue` on a full one throws `NoSuchElementException`.
- There are no indexes: no `q[i]`, no `q.get(i)`. And for-each doesn't work on the aud's classes: `for (String s : q)` gives `error: for-each not applicable to expression type` (it doesn't implement `Iterable`).
- To look at everything: walk the nodes (`SLLNode<String> p = q.front; while (p != null) { ...; p = p.succ; }`) or give `LinkedQueue` a `toString()` like `LinkedStack`'s, starting from `front`.
- Trap: own `Queue` + `import java.util.Queue;` gives `error: Queue is already defined in this compilation unit`. Import only what you use.
- **Modern** (`ArrayDeque<E>` does both jobs, and for-each and `println` work on it):

| Aud method | `ArrayDeque` |
|---|---|
| `enqueue(x)` | `offer(x)` |
| `dequeue()`, throws when empty | `poll()`, returns `null` when empty |
| `peek()`, throws when empty | `peek()`, returns `null` when empty |
| stack `push / pop / peek` | `push / pop / peek` |
| `isEmpty()`, `size()` | `isEmpty()`, `size()` |

Front to back in one line: `q.enqueue(q.dequeue());` (this is the round-robin move).

**Exercise:**
1. Add `Queue<E>` and `LinkedQueue<E>`. Enqueue `"report"`, `"invoice"`, `"poster"`; print `size 3, front report`.
2. Do `q.enqueue(q.dequeue());` once. Then print every element without losing any: `int n = q.size();`, and `n` times dequeue, print, enqueue. Expected: `invoice poster report`.
3. Break it: `for (int i = 0; i < q.size(); i++) System.out.print(q.dequeue() + " ");` prints only `invoice poster` and leaves one in the queue: `size()` shrinks while `i` grows. Save the size first, or use `while (!q.isEmpty())`.

## 1.3 Objects in a queue and reading input (slides 29-31, `Student`)

- Problem 3 stores `Student` objects (`index`, `minutes`) in a queue. The labs need the same: a class with a name and a remaining time.
- A queue holds references: dequeue an object, change `j.pages`, enqueue it back, and the change stays (same object).
- Printing an object calls its `toString()`. Without one you get `Job@7852e922`. (`SLLNode.toString()` just calls `element.toString()`, so a `String` element prints fine but a `Job` doesn't.)
- Input is space-separated tokens: `nextInt()` for numbers, `next()` for names.
- Trap (bug in the posted Problem 3, verified): it reads the index with `nextLine()` right after `nextInt()`, gets the empty rest of the line, and the next `nextInt()` eats the index as the minutes. It prints `Prviot student sto nema da e opsluzen e: ` with an empty index. Use `next()`.

```java
class Job {
    String name;
    int pages;
    Job(String name, int pages) { this.name = name; this.pages = pages; }
    @Override
    public String toString() { return name + " " + pages; }
}
```

**Exercise:**
1. Add `Job`. `input.txt`:
   ```
   3 4
   report 5
   invoice 2
   poster 9
   ```
   The `4` is **T**, the most pages per turn; it's used from 1.5 on. Read `n` and `t`, enqueue `new Job(in.next(), in.nextInt())` n times, then dequeue until empty and print each job:
   ```
   report 5
   invoice 2
   poster 9
   ```
2. Break it: remove `toString()` and see `Job@...`. Put it back.
3. Break it: read the name with `in.nextLine()`: `java.util.InputMismatchException` (name is `""`, then `nextInt()` lands on `report`).

## 1.4 Serve while it fits (Problem 3, slides 29-31)

- Problem 3: the student service has 180 minutes. Serve from the front while the next student still fits; the first one that doesn't fit ends the day.
- Shape: `while (!q.isEmpty() && q.peek().minutes <= left) { left -= ...; q.dequeue(); }`. Lab B's inner loop is this same shape on a stack.
- Trap (bug in the posted solution, verified): it loops `while (tempStudent != null)` using `peek()`, but the aud's `peek()` throws on an empty queue; it never returns `null`. If everyone fits it crashes with `java.util.NoSuchElementException` at `ArrayQueue.peek`. Put `!q.isEmpty()` first: `&&` stops before `peek()` runs.
- **Modern:** `ArrayDeque.peek()` returns `null` when empty, so a `!= null` check works there.

**Exercise:**
1. Same input, `int ink = 10;` (one budget for the whole day). Print jobs while they fit, then report:
   ```
   Printed: report
   Printed: invoice
   First not printed: poster
   Waiting: 1
   ```
2. `ink = 20`: three `Printed:` lines, then `All printed` (no crash).

## 1.5 Round robin: back of the queue (slide 20: OS processes waiting for the processor; the loop is **not in auds**)

- Different rule from 1.4: T is not a shared budget, it's a **per-turn limit**. Every job eventually finishes; the loop runs until the queue is empty, no `break`.
- One turn: `dequeue()` the front job. If its pages `<= T`, it finishes now: `done++`, print `done + ". " + name`. Otherwise subtract T and `enqueue` it at the back.
- `dequeue()` once at the top of the turn: the job is out of line while it's being served, and goes back only if unfinished.
- `<=`, not `<`: exactly T left finishes this turn. The counter grows only when something finishes.

```java
int done = 0;
while (!q.isEmpty()) {
    Job j = q.dequeue();
    if (/* finishes this turn? */) { /* count + print */ }
    else { /* subtract t, back of the queue */ }
}
```

**Exercise:**
1. Replace the 1.4 loop with round robin (T = 4 from the first line). Trace:

   | turn | job | pages | result | queue after |
   |---|---|---|---|---|
   | 1 | report | 5 > 4 | 1 left, back | invoice, poster, report(1) |
   | 2 | invoice | 2 ≤ 4 | **1. invoice** | poster, report(1) |
   | 3 | poster | 9 > 4 | 5 left, back | report(1), poster(5) |
   | 4 | report | 1 ≤ 4 | **2. report** | poster(5) |
   | 5 | poster | 5 > 4 | 1 left, back | poster(1) |
   | 6 | poster | 1 ≤ 4 | **3. poster** | |

   ```
   1. invoice
   2. report
   3. poster
   ```
2. Add `memo 4` as the second job (first line `4 4`): `1. memo`, `2. invoice`, `3. report`, `4. poster`.
3. Break it: `<` instead of `<=`: `1. invoice`, `2. report`, `3. memo`, `4. poster` (memo needs an extra turn).

## 1.6 A stack inside every queue element (**not in auds** as a combination)

- Each job now owns a pile of documents: an instance field `LinkedStack<Doc> pile = new LinkedStack<>();` in `Job` (not in `main`), with `Doc(name, pages)`. Doc's `pages` must be changeable (no `private`, or add a setter).
- Why a stack: the rule is "last listed goes first", which is LIFO. Jobs still wait in a queue (fair turns, back of the line).
- Input line: `jobName K doc pages doc pages ...`. Push in reading order: the last doc read lands on top.
- One turn: `left = t`. While `left > 0` and the pile isn't empty: top fits → `left -= top.pages`, **pop** it; doesn't fit → `top.pages -= left`, `left = 0` (it stays on top, half printed).
- After the turn: pile empty → finished (done++, print); otherwise enqueue the job again.

```java
Job j = new Job(in.next());
int k = in.nextInt();
for (int d = 0; d < k; d++) j.pile.push(new Doc(in.next(), in.nextInt()));
jobs.enqueue(j);
```

**Exercise:**
1. Rewrite `Job` with a pile (keep the 1.5 version as `Task(name, pages)` for 1.7). Input:
   ```
   3 5
   Alice 2 cv 3 letter 4
   Bob 1 thesis 6
   Carol 2 memo 1 note 2
   ```

   | visit | job | what happens (allowance 5) | pile after | line after |
   |---|---|---|---|---|
   | 1 | Alice | letter 4 fits (left 1), cv 3 > 1: 1 page (cv 2) | cv(2) | Bob, Carol, Alice |
   | 2 | Bob | thesis 6 > 5: 5 pages (thesis 1) | thesis(1) | Carol, Alice, Bob |
   | 3 | Carol | note 2 fits (left 3), memo 1 fits | empty: **1. Carol** | Alice, Bob |
   | 4 | Alice | cv 2 fits | empty: **2. Alice** | Bob |
   | 5 | Bob | thesis 1 fits | empty: **3. Bob** | |

   ```
   1. Carol
   2. Alice
   3. Bob
   ```
2. Break it: inner `while` → `if` (one doc per visit): `1. Alice`, `2. Bob`, `3. Carol`.
3. Break it: forget `pile.pop()` when a doc fits: the pile never empties and the program never ends.

## 1.7 A queue plus one shared stack, with a round counter (**not in auds**)

- Unfinished tasks go onto one shared `LinkedStack<Task> tray`, not back into the queue.
- `turn++` right after `dequeue()`: every turn counts, finished or not.
- Empty the tray into the queue with `while (!tray.isEmpty()) tasks.enqueue(tray.pop());` (not a `for` up to `tray.size()`: same shrinking-size trap as 1.2). Popping reverses the order: the last one suspended comes back first.
- Do that (a) after a turn when `turn % m == 0` (use `m` from the input, not a hardcoded number), and (b) before taking a task when the queue is empty but the tray isn't.
- The main loop runs while **either** has tasks: `while (!tasks.isEmpty() || !tray.isEmpty())`.

**Exercise:**
1. First line `N T M`. Input:
   ```
   4 3 2
   report 5
   invoice 2
   poster 9
   flyer 4
   ```

   | turn | task | result | tray (top right) | queue after |
   |---|---|---|---|---|
   | 1 | report 5 | 2 left, to tray | report | invoice, poster, flyer |
   | 2 | invoice 2 | **1. invoice**; turn 2: flush | | poster, flyer, report |
   | 3 | poster 9 | 6 left, to tray | poster | flyer, report |
   | 4 | flyer 4 | 1 left, to tray; turn 4: flush (flyer first) | | report, flyer, poster |
   | 5 | report 2 | **2. report** | | flyer, poster |
   | 6 | flyer 1 | **3. flyer** | | poster |
   | 7 | poster 6 | 3 left, to tray | poster | empty → flush |
   | 8 | poster 3 | **4. poster** | | |

   ```
   1. invoice
   2. report
   3. flyer
   4. poster
   ```
2. Break it: remove the "queue empty" flush: prints three lines, then `java.util.NoSuchElementException` from `dequeue()`.

Your practice file now has every mechanic of all three labs.

## 1.8 From lab text to code (the method)

All three labs are **simulations**. Before writing code, answer on paper:
1. **What are the things?** → a class with what changes (remaining time) and what's printed (name), plus `toString()`.
2. **Where do they wait, and who leaves first?** "In the order entered", "back of the queue" → queue. "Last added first", "innermost", "top" → stack. Each such sentence is one structure.
3. **What happens in one round?** Numbered steps in plain words (the labs often number them for you). Each step ≈ one line of code.
4. **When does it stop?** Nothing waiting anywhere → the `while` condition.

Then hand-trace the first example in a table like the ones above. If your table matches the expected output, coding is translation.

---

# 2. The labs

Each lab: its own module. Output only the required lines (remove debug prints). Pick aud classes or `ArrayDeque` and stay consistent.

## 2.1 Lab A

### Text (as given)

> You are given **N** processes, where each process is represented by a name and the time required for its execution. The processes are handled using the queue (FIFO) principle, in the order in which they are entered.
>
> During each round, the processor executes one process for at most **T** time units. If the process is not completed, its remaining execution time is reduced by **T**, and the process is added to the end of the queue. If the process is completed, its name is printed.
>
> Your task is to determine the order in which the processes finish executing.
>
> Input: The first line contains the number of processes **N** and the number of time units **T** allocated to each iteration.
>
> ```
> 3 2
> Process-A 3
> Process-B 1
> Process-C 4
> ```
>
> Output: The completion order (ordinal number) followed by the name of each completed process.
>
> ```
> 1. Process-B
> 2. Process-A
> 3. Process-C
> ```
>
> For example:
>
> | Input | Result |
> |---|---|
> | `3 2`<br>`Process-A 3`<br>`Process-B 1`<br>`Process-C 4` | `1. Process-B`<br>`2. Process-A`<br>`3. Process-C` |
> | `4 5`<br>`Process-A 1`<br>`Process-B 3`<br>`Process-C 5`<br>`Process-D 2` | `1. Process-A`<br>`2. Process-B`<br>`3. Process-C`<br>`4. Process-D` |

### Build order
1. Queue (1.2) or `ArrayDeque`; `Process(name, time)` with `toString()` (1.3).
2. Read `N T`, then N times `next()` / `nextInt()` (1.3).
3. Round robin with `<=` and a counter (1.5).

### Extra tests (verified)
- Exactly T: `3 3 / P1 3 / P2 7 / P3 3` → `1. P1`, `2. P3`, `3. P2`
- One process, many turns: `1 4 / Only 10` → `1. Only`
- T = 1: `3 1 / A 3 / B 1 / C 2` → `1. B`, `2. C`, `3. A`

(`/` separates input lines.)

## 2.2 Lab B

### Text (as given)

> In an operating system, N main processes arrive and are handled using a queue (Queue), in the order they were entered. Each main process contains a list of subprocesses organized as a stack (Stack), meaning that the last subprocess added (the innermost one) must be executed first (LIFO).
>
> In each round, the processor handles one main process for at most T time units:
>
> 1. The main process at the front of the queue is taken.
> 2. The processor executes the subprocess currently at the top of that process's stack.
> 3. If the subprocess finishes within the available quantum T, it is removed from the stack (pop). If there is still time left in the same quantum, the processor immediately moves on to the next subprocess in the same stack.
> 4. If the quantum T expires while the main process still has unfinished subprocesses in its stack, that main process is moved to the back of the queue.
> 5. When all subprocesses of a main process are completed (its stack becomes empty), the main process is considered fully completed and its name is printed.
>
> Your task is to determine the order in which the main processes are fully completed.
>
> Input
>
> The first line contains two integers: N (the number of main processes) and T (the duration of the time quantum).
>
> Each of the next N lines contains the name of a main process, the number of its subprocesses K, followed by K pairs (SubprocessName Duration), entered in order from outermost to innermost. The last subprocess entered is at the top of the stack.
>
> Example:
> ```
> 2 3
> ProcA 2 SubA1 3 SubA2 2
> ProcB 1 SubB1 4
> ```
> Output
>
> Print the order in which the main processes are fully completed. Each process should be printed on a separate line, together with its completion order and name.
>
> Example:
> ```
> 1. ProcA
> 2. ProcB
> ```

Test cases (as given):

| Input | Expected |
|---|---|
| `2 3`<br>`ProcA 2 SubA1 3 SubA2 2`<br>`ProcB 1 SubB1 4` | `1. ProcA`<br>`2. ProcB` |
| `1 5`<br>`P 3 A 2 B 2 C 2` | `1. P` |
| `3 2`<br>`X 1 x1 5`<br>`Y 2 y1 1 y2 1`<br>`Z 1 z1 2` | `1. Y`<br>`2. Z`<br>`3. X` |
| `2 1`<br>`A 2 a1 1 a2 1`<br>`B 1 b1 3` | `1. A`<br>`2. B` |
| `2 10`<br>`P1 2 s1 4 s2 3`<br>`P2 1 t1 12` | `1. P1`<br>`2. P2` |

### Build order
1. Stack + queue (1.1, 1.2) or `ArrayDeque` for both.
2. `Sub(name, time)` and `MainProc(name)` with its own stack field; push the K pairs in reading order (1.6).
3. Per turn: `left = T`, inner `while`, partial subprocess keeps its reduced time (1.6).
4. Stack empty → print with the counter; otherwise back of the queue (1.5).

### Extra tests (verified)
- `3 3 / Q 1 q 3 / R 2 r1 2 r2 2 / S 1 s 1` → `1. Q`, `2. S`, `3. R`
- `2 4 / M1 3 a 1 b 1 c 2 / M2 2 d 5 e 1` → `1. M1`, `2. M2`

## 2.3 Lab C (other group)

### Text (as given; the photo was cut off after `1. B`, so lines 2-4 of the example output are filled in from my run)

> Системот користи редица (Queue) за активни процеси и еден заеднички стек (Stack) за временски суспендирани процеси. Во системот пристигнуваат N процеси, секој со време потребно за извршување. Процесорот во еден круг обработува еден процес најмногу T временски единици (квантум).
>
> Правила:
>
> 1. Се зема процесот од почетокот на редицата и се извршува најмногу T временски единици. Тоа се брои како еден круг.
> 2. Ако процесот заврши, неговото име се печати со реден број.
> 3. Ако квантумот истече, а процесот не е завршен, тој се поставува на врвот на стекот на суспендирани процеси (не се враќа во редицата).
> 4. По секои M кругови (по круг чиј реден број е делив со M), целиот стек се празни во редицата: процесите се земаат од врвот на стекот и еден по еден се додаваат на крајот од редицата (pop → enqueue). Со тоа се менува редоследот на суспендираните процеси.
> 5. Ако редицата е празна, а стекот не е, стекот веднаш се празни во редицата (без да се чека M-тиот круг).
>
> Ваша задача е да го определите редоследот по кој процесите завршуваат.
>
> Влез
>
> Првиот ред содржи три броја: N (број на процеси), T (времетраење на квантумот) и M (на колку круга се празни стекот).
>
> Во следните N редови се внесува името на процесот и времето потребно за негово извршување.
>
> Пример:
> ```
> 4 2 3
> A 4
> B 1
> C 6
> D 3
> ```
> Излез
>
> Се печати редоследот по кој процесите завршуваат, секој во посебен ред, со неговиот реден број и име.
>
> Пример:
> ```
> 1. B
> 2. A
> 3. C
> 4. D
> ```

### How I read the rules
- Every round counts, including rounds where the process finishes.
- The `% M` check is after the round; the "queue empty" check is before taking the next process.
- Finishing in exactly T counts as finished (`<=`).

### Build order
1. Queue + stack (1.1, 1.2), `Process(name, time)` (1.3).
2. Round counter; unfinished → push onto the stack (1.7).
3. `round % M == 0` flush after the round, "queue empty" flush before taking (1.7).

### Tests (only `1. B` is from the lab; the rest is from my reading of the rules, verified with my own run and yours)
- `4 2 3 / A 4 / B 1 / C 6 / D 3` → `1. B`, `2. A`, `3. C`, `4. D`
- M = 1: `3 2 1 / A 5 / B 3 / C 2` → `1. C`, `2. B`, `3. A`
- Queue empties early, order reversed: `3 5 10 / A 12 / B 1 / C 7` → `1. B`, `2. C`, `3. A`
- `4 3 2 / A 7 / B 7 / C 7 / D 1` → `1. D`, `2. A`, `3. B`, `4. C`
- `2 4 5 / A 4 / B 8` → `1. A`, `2. B`

## 2.4 Common mistakes

| Symptom | Cause | Fix |
|---|---|---|
| `java.util.NoSuchElementException` from `dequeue`/`pop`/`peek` | taking from an empty structure | check `isEmpty()` first; in Lab C flush the stack when the queue is empty |
| Only half the elements processed, rest left over | `for (i < q.size())` while dequeuing/popping | `while (!q.isEmpty())` or save the size first |
| `Job@7852e922` printed | no `toString()` in your class | add one, or print the fields |
| `for-each not applicable to expression type` | for-each over the aud's `LinkedQueue` | walk `front`/`succ`, or use `ArrayDeque` |
| `java.util.InputMismatchException` | `nextLine()` after `nextInt()` | read names with `next()` |
| Process exactly T long finishes a turn late | `<` instead of `<=` | finished when `time <= T` (or `<= left`) |
| Program never ends (Lab B) | finished subprocess not popped | `left -= top.time; stack.pop();` |
| Lab B: wrong order when several subprocesses fit in one turn | `if` instead of `while` in the inner loop | loop until `left == 0` or the stack is empty |
| Lab C: wrong flush timing | hardcoded `% 2` instead of `% M` | use M from the input |
| Output lines run together | `printf` without `%n` | `"%d. %s%n"` or `println` |
| `Queue is already defined in this compilation unit` | own `Queue` + `import java.util.Queue` | import only what you use |
| Extra lines in the output | debug prints left in | remove them |

Sources: Aud 05 "One dimensional data structures" (`05_Ednodimenzionalni_podatocni_strukturi_EN.pdf`) and its code (`Stack`, `Queue`, `ArrayStack`, `LinkedStack`, `ArrayQueue`, `LinkedQueue`, `StudentServiceQueue`) in the APS project.
