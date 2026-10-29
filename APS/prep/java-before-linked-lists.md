# Java roadmap before Singly / Doubly Linked Lists

Goal: learn by doing. Write each exercise myself, run it, test edge cases.

Format of each step: what to learn, then practice problems (easy first).
Read input with `Scanner` for now. For problems without input, hardcode test data in `main`.

---

# Quick syntax: C++ -> Java

## Program structure
```cpp
// C++
#include <iostream>
using namespace std;
int main() { cout << "hi" << endl; return 0; }
```
```java
// Java: everything lives in a class, file must be named Main.java
import java.util.Scanner;                      // only for things outside java.lang

public class Main {
    public static void main(String[] args) {
        System.out.println("hi");
    }
}
```
No header files, no `#include`, no forward declarations, no `using namespace`. Order of methods in a class does not matter.

## Types and variables
```java
int a = 5;            long b = 5L;          // L suffix for long literals
double d = 2.5;       float f = 2.5f;       // f suffix for float
boolean ok = true;    char c = 'x';         // char is 16-bit, single quotes
String s = "text";                           // String is a class, double quotes
final int MAX = 100;                         // "const" -> final
int x = (int) 3.9;                           // casts work the same
```
- Primitives: `byte short int long float double boolean char`. There is no `unsigned`.
- Primitives have default values only as fields/array elements (0, 0.0, false, `\0`). Local variables must be assigned before use.
- Wrapper classes for generics and collections: `Integer`, `Long`, `Double`, `Boolean`, `Character`. Use `Integer.parseInt(s)`, `String.valueOf(5)`.
- `var x = 5;` works (type inferred, like `auto`).
- `Math.max`, `Math.min`, `Math.abs`, `Math.sqrt`, `Math.pow` (all in `java.lang`, no import).

## Input / Output
```java
Scanner in = new Scanner(System.in);         // import java.util.Scanner;
int n = in.nextInt();                         // cin >> n
double d = in.nextDouble();
String w = in.next();                         // cin >> word
in.nextLine();                                // like cin.ignore() after a number
String line = in.nextLine();                  // getline(cin, line)

System.out.println(n);                        // cout << n << endl
System.out.print(n);                          // cout << n
System.out.printf("%d %.2f %s%n", n, d, w);  // printf, %n = newline
```

## Arrays
```cpp
// C++
int a[5];  int b[3] = {1,2,3};  int* p = new int[n];  delete[] p;
```
```java
int[] a = new int[5];                 // all zeros, always on the heap
int[] b = {1, 2, 3};
int[] c = new int[]{1, 2, 3};
int n = a.length;                     // field, NO parentheses (String uses length())
a[0] = 10;                            // out of range -> ArrayIndexOutOfBoundsException (no UB)

for (int i = 0; i < a.length; i++) { ... }
for (int x : a) { ... }               // for-each (copy of each element)

int[][] m = new int[3][4];            // 3 rows, 4 columns
int rows = m.length, cols = m[0].length;
int[][] jag = new int[3][];           // rows can have different lengths
jag[0] = new int[2];

String[] names = new String[3];       // array of references, all start as null
```
Useful `java.util.Arrays` methods (`import java.util.Arrays;`):
```java
Arrays.toString(a)          // "[1, 2, 3]"        (printing `a` directly prints junk like [I@1b6d3586)
Arrays.deepToString(m)      // for 2D arrays
Arrays.sort(a)              // sorts in place
Arrays.fill(a, 7)
Arrays.copyOf(a, newLen)    // copy (pads with 0 / truncates)
Arrays.equals(a, b)         // compares contents; `a == b` compares references!
int[] copy = a.clone();     // shallow copy
```
Arrays are objects: `int[] y = a;` does NOT copy, both names refer to the same array.

## Strings
```java
String s = "hello";
s.length()   s.charAt(0)   s.substring(1, 3)   s.indexOf('l')   s.toUpperCase()
s.equals(t)  s.equalsIgnoreCase(t)  s.compareTo(t)    // never compare strings with ==
s.split(" ")   s.trim()   s.contains("ell")   s.isEmpty()
String t = s + " world" + 5;          // + concatenates (the only operator overloading in Java)
char[] chars = s.toCharArray();
StringBuilder sb = new StringBuilder();   // use for building strings in loops
sb.append("a").append(5); String r = sb.toString(); sb.reverse();
```
Strings are immutable: every "change" creates a new String.

## Control flow
`if / else`, `while`, `do-while`, `for`, `break`, `continue`, `&&`, `||`, `!`, `?:`, `%`, `++` all work like C++.
Conditions must be `boolean` (no `if (x)` with an int).
```java
switch (day) {                          // works on int, char, String, enum
    case 1: System.out.println("Mon"); break;
    default: System.out.println("other");
}
```

## Methods
```java
static int add(int a, int b) { return a + b; }       // free functions -> static methods in a class
static double add(double a, double b) { ... }        // overloading works like C++
static void f(int... nums) { ... }                   // varargs
```
- No default arguments (use overloading), no `&` references, no pointers.
- Primitives are passed by value. Objects and arrays: the *reference* is passed by value, so a method can change the object's contents, but `p = new ...` inside the method does not affect the caller.
- A method that returns multiple values: return an array, an object, or a `Pair`-like class.

## Classes and objects
```cpp
// C++
class Point { int x, y; public: Point(int x, int y):x(x),y(y){} int getX() const {return x;} };
Point p(1, 2);   Point* q = new Point(3, 4);   q->getX();   delete q;
```
```java
public class Point {
    private int x, y;                       // access modifier on EVERY member

    public Point(int x, int y) {            // constructor, same name as class
        this.x = x;                         // `this` is a reference, use `.` not `->`
        this.y = y;
    }
    public Point() { this(0, 0); }          // constructor calling another constructor

    public int getX() { return x; }         // no `const` methods
    public void setX(int x) { this.x = x; }

    @Override
    public String toString() { return "(" + x + ", " + y + ")"; }   // like operator<<
}

Point p = new Point(1, 2);                  // always `new`, always on the heap
Point q = p;                                // NOT a copy: q and p are the same object
Point z = null;                             // nullptr -> null
System.out.println(p.getX());               // always `.`, never `->`
```
- No destructors, no `delete`, no copy constructor by default. The garbage collector frees unreachable objects.
- To copy an object, write a copy constructor: `public Point(Point o) { this(o.x, o.y); }`.
- No operator overloading (`+`, `==`, `<<` can't be overloaded). Write methods: `equals`, `compareTo`, `toString`.
- `==` on objects compares references, `a.equals(b)` compares contents (once you override `equals`).
- `static` fields and methods are shared by the class: `Point.count`, `Math.max(...)`.
- Fields can be initialized inline: `private int count = 0;`.
- One public class per file, the file name equals the class name. Helper classes can be in the same file without `public`, or nested: `static class Node { ... }`.

## Inheritance and interfaces
```java
class Animal {
    protected String name;
    Animal(String name) { this.name = name; }
    void speak() { System.out.println("..."); }
}
class Dog extends Animal {                  // single inheritance only
    Dog(String name) { super(name); }       // call parent constructor first
    @Override void speak() { System.out.println("Woof"); }   // all methods are virtual by default
}

Animal a = new Dog("Rex");                  // upcast, no slicing, no pointers needed
a.speak();                                  // prints "Woof"
if (a instanceof Dog) { Dog d = (Dog) a; }  // checked downcast (ClassCastException if wrong)

abstract class Shape { abstract double area(); }    // abstract class (C++: pure virtual)
interface Drawable { void draw(); }                  // interface
class Circle extends Shape implements Drawable { ... }   // one parent, many interfaces
```
- `final` on a class/method stops inheritance/overriding. `final` on a variable makes it assigned-once.
- Every class extends `Object`, which provides `toString()`, `equals()`, `hashCode()`.

## Dynamic memory and null
| C++ | Java |
|---|---|
| `Node* p = new Node();` | `Node p = new Node();` |
| `p->next` | `p.next` |
| `nullptr` | `null` |
| `delete p;` | nothing (garbage collector) |
| `Node** pp`, `Node*&`, pointer arithmetic | don't exist |
| segfault on null deref | `NullPointerException` |

A linked list node in Java:
```java
static class Node {
    int value;
    Node next;                              // a reference, null at the end of the list
    Node(int value) { this.value = value; }
}
Node head = new Node(1);
head.next = new Node(2);
for (Node cur = head; cur != null; cur = cur.next) System.out.println(cur.value);
```

## Collections (replacement for STL)
```java
import java.util.*;
ArrayList<Integer> list = new ArrayList<>();     // vector<int>   (no primitives: Integer, not int)
list.add(5);  list.get(0);  list.set(0, 9);  list.remove(0);  list.size();  list.contains(9);
HashMap<String, Integer> map = new HashMap<>(); // unordered_map
map.put("a", 1);  map.get("a");  map.containsKey("a");  map.getOrDefault("b", 0);
HashSet<Integer> set = new HashSet<>();          // unordered_set
ArrayDeque<Integer> stack = new ArrayDeque<>(); // stack / queue / deque: push, pop, peek, offer, poll
PriorityQueue<Integer> pq = new PriorityQueue<>();   // min-heap by default (C++ priority_queue is max-heap)
for (int x : list) { ... }
```
Generics use `<>` like templates, but only work with objects (`List<Integer>`, never `List<int>`).

## Exceptions
```java
try {
    int x = Integer.parseInt("abc");
} catch (NumberFormatException e) {
    System.out.println("bad number: " + e.getMessage());
} finally {
    // always runs
}
throw new IllegalArgumentException("b must not be 0");
```
Same idea as C++, but all exceptions are objects that extend `Exception`. `RuntimeException`s (null pointer, bad index, bad cast) don't need to be declared.

## Quick C++ -> Java differences to remember
- `main` is `public static void main(String[] args)` inside a class.
- Objects are always references on the heap. No stack objects, no `&`, no `*`, no `->`.
- No slicing, no `delete`, no destructors, no undefined behavior for array access.
- No operator overloading, no `unsigned`, no default arguments, no header files, no multiple inheritance of classes.
- Methods are virtual by default. Use `@Override` every time.
- Compare objects with `.equals()`, never `==` (including `String` and `Integer`).
- Array length is `arr.length`, string length is `s.length()`, collection size is `list.size()`.
- Java passes everything by value (for objects, the value is the reference).

---

## 1. Control flow, methods, and arrays
`if`, loops, `switch`, static methods, 1D and 2D arrays, `Arrays.toString`, `Arrays.sort`, `Arrays.copyOf`.

**Problems**
1. Read `n`, then `n` integers. Print the minimum, maximum, and average (average as a double with 2 decimals, use `System.out.printf("%.2f%n", avg)`).
   - Input: `5` / `4 9 1 7 3` -> Output: `1 9 4.80`
2. Reverse an array in place (no second array). Print it with `Arrays.toString`.
3. Rotate an array right by `k` positions. `[1,2,3,4,5]`, k=2 -> `[4,5,1,2,3]`. Handle `k > n`.
4. Read `n` numbers in the range 0-9 and print how many times each digit appears (frequency array of size 10).
5. Read an `n x m` matrix and print the sum of each row and each column.
6. Write a static method `boolean isPrime(int n)` and use it to print all primes up to 100.

## 2. Strings
Immutability, `equals` vs `==`, `charAt`, `substring`, `split`, `StringBuilder`, `toCharArray`.

**Problems**
1. Read a word and check whether it is a palindrome (ignore case).
   - `Anna` -> `true`, `Java` -> `false`
2. Read a sentence and count the vowels in it.
3. Read a sentence and print the words in reverse order. `I love Java` -> `Java love I`
4. Read a sentence and print the longest word.
5. Compress a string: `aaabccdddd` -> `a3b1c2d4`. Use `StringBuilder`, not `+=` in a loop.
6. Check whether two strings are anagrams (`listen`, `silent` -> `true`).
7. Demonstrate `==` vs `equals`: create `String a = new String("hi")` and `String b = "hi"`, print `a == b` and `a.equals(b)`, and write one sentence on why they differ.

## 3. Classes and objects
Fields, constructors, `this`, access modifiers, getters/setters, `static` vs instance, `toString()`.

**Problems**
1. Write a `Point` class (`x`, `y`) with a constructor, getters, `toString()`, and a method `double distanceTo(Point other)`. Create 3 points and print the distances between them.
2. Write a `Student` class (`name`, `index`, `grades` as an `int[]`) with a method `double average()`. Create an array of 3 students and print the one with the best average.
3. Write a `BankAccount` class with `deposit`, `withdraw` (refuse if the balance is too low), and `getBalance`. Keep the balance `private`.
4. Add a `static int count` field to `Student` that counts how many students have been created. Print it at the end and explain why it is `static`.

## 4. References and `null`
No pointers: a variable holds a reference, `null` means "points to nothing", dereferencing null throws `NullPointerException`.

**Problems**
1. Create a `Point p1 = new Point(1, 2); Point p2 = p1;`. Change `p2.x` and print `p1.x`. Explain what happened.
2. Write a method `void change(Point p)` that does `p.x = 100` and another `void replace(Point p)` that does `p = new Point(0, 0)`. Call both on the same point and print it after each call. Explain the difference (Java passes references *by value*).
3. Write the same two methods for an `int[]` array (change an element vs assign a new array).
4. Create an array of 3 `Student` objects without filling it, then try to call a method on `arr[0]`. Observe the `NullPointerException`, then fix it with a null check.

## 5. Nested classes
A `static class Node` inside another class is how nodes get written.

**Problems**
1. Inside a class `Main`, create `static class Node { int value; Node next; }`. In `main`, create three nodes manually, link them (`1 -> 2 -> 3`), and print them with a `while (cur != null)` loop.
2. Using the same manual nodes, write static methods: `int length(Node head)`, `int sum(Node head)`, `boolean contains(Node head, int x)`.
3. Write `Node addToFront(Node head, int x)` that returns the new head. Call it 3 times starting from `null`.
4. Print the list in reverse order using recursion (no extra list).

## 6. Exceptions
`try/catch/finally`, `throw new ...`, `IllegalArgumentException`, `IllegalStateException`, `NoSuchElementException`.

**Problems**
1. Read a number as a string and convert it with `Integer.parseInt`. If it fails, catch `NumberFormatException` and ask again until the input is valid.
2. Write `int divide(int a, int b)` that throws `IllegalArgumentException` when `b == 0`. Call it with bad input and catch the exception in `main`.
3. Give `BankAccount.withdraw` an `IllegalStateException` for insufficient funds instead of printing an error.
4. Write a method `int get(int[] arr, int index)` that catches `ArrayIndexOutOfBoundsException` and returns `-1`. Then rewrite it so it checks the index first instead. Which is better and why?

## 7. Basic generics
Only the simple part: `class Box<T>`, `class Node<T>`. (This is the Generics and Sub-typing slide: `Box<Integer>` is not a `Box<Number>`.)

**Problems**
1. Write `class Box<T>` with `T value`, `get()`, `set(T v)`. Create a `Box<Integer>` and a `Box<String>`.
2. Write `class Pair<A, B>` with `getFirst()` and `getSecond()`. Create a `Pair<String, Integer>` (name and age).
3. Write a generic static method `static <T> void printArray(T[] arr)` and call it with an `Integer[]` and a `String[]`.
4. Try `Box<Number> b = new Box<Integer>();` and read the compiler error. Then look up `Box<? extends Number>` and explain in one sentence when you would use it.
5. Change the `Node` class from step 5 into `Node<T>` and rebuild the manual list of Strings.

## 8. Interfaces and inheritance (light)
`interface`, `implements`, `extends`, `@Override`, `equals`, `toString`, `Comparable<T>`.

**Problems**
1. Create an `abstract class Shape` with `abstract double area()`. Add `Circle` and `Rectangle` subclasses. Put 4 shapes in a `Shape[]` array and print each area (observe polymorphism).
2. Create `interface Describable { String describe(); }` and implement it in two unrelated classes.
3. Override `equals` in `Point` so that two points with the same `x` and `y` are equal. Test with `==`, then `equals`.
4. Make `Student implements Comparable<Student>` (compare by average grade) and sort an array of students with `Arrays.sort`.

## 9. Build a dynamic array yourself
Bridge between arrays and linked lists: uses arrays, classes, generics, and resizing.

**Problems**
1. Write `MyArrayList` for `int` first: `add(int x)`, `get(int i)`, `size()`, and when the internal array is full, create one twice as big and copy.
2. Add `remove(int index)` (shift elements left) and `add(int index, int x)` (shift right). Throw `IndexOutOfBoundsException` for bad indexes.
3. Add `toString()` that prints `[1, 2, 3]`, and `indexOf(int x)`.
4. Make it generic: `MyArrayList<T>`. (Hint: you cannot write `new T[n]`, so use `(T[]) new Object[n]`, and read about the unchecked warning.)
5. Test: add 1000 elements, remove every second one, and check the result with a plain loop.

## 10. Singly linked list
Build it in this order. Test each operation on an empty list, a one-element list, and a longer list before moving on.

**Problems**
1. Start with `SLL<T>` containing `Node<T> head` and `int size`. Implement `addFirst`, `addLast`, `size`, and `toString`.
2. Add `search(T x)` (return the position or -1) and `get(int index)`.
3. Add `removeFirst`, `removeLast`, and `remove(T x)` (remove the first occurrence). Throw `NoSuchElementException` when the list is empty.
4. Add `insertAt(int index, T x)`.
5. Add `reverse()` in place (no new nodes, only change `next` pointers). Draw it on paper first.
6. Extra: write `static SLL<Integer> merge(SLL<Integer> a, SLL<Integer> b)` that merges two sorted lists into one sorted list.
7. Extra: find the middle element in one pass using the slow/fast pointer technique.
8. Extra: remove all duplicates from an unsorted list.

---

(Next: 11. Doubly linked list: same operations with a `prev` pointer, then a `tail` reference for O(1) `addLast`.)

## Tips
- Draw boxes and arrows on paper for every operation before coding it. Most linked list bugs are pointer updates in the wrong order.
- Use the IntelliJ debugger (click the gutter for a breakpoint, `Shift+F9`).
- Test edge cases every time: empty list, one element, first, last.
- Java has no `delete`. Unlinking a node is enough, the garbage collector frees it.
- If steps 1-7 are comfortable without looking things up, start step 10 and fill in 8 and 9 as you go.
- Stuck? Ask for a hint or a code review, not the full solution.
