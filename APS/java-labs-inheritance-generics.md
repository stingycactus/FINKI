# Lab prep: inheritance (Lab 1) and generics (Lab 2)

Each subsection is one thing to learn, in the order you need it. Do the exercises yourself, then compare with the expected output.

Setup for both labs: put all classes in one `Main.java`, only `Main` is `public`, unless the lab says otherwise. Use the exact class and method names from the lab text.

---

# 1. Lab 1: FINKI Soft (inheritance, polymorphism, arrays)

## 1.1 Inheritance basics: `extends` and `super(...)`

- A child gets all non-private members of its parent. Single inheritance only.
- The child constructor must call a parent constructor as its **first line**. It's the Java version of the C++ initializer list.
- Forgetting it makes Java insert `super()`, which fails with "no default constructor" if the parent doesn't have one.
- If the parent's fields are `private`, the child can't read them directly: use `super.calculateSalary()`, or make the fields `protected` if children should access them.
- Every class extends `Object`, which is why `toString()` needs `@Override`.
- The chain works: `TeamLead extends Developer extends Employee`, and each constructor calls the one above it.

```java
class Developer extends Employee {
    private int overtimeHours;

    public Developer(String id, String name, double baseSalary, int overtimeHours) {
        super(id, name, baseSalary);     // first line
        this.overtimeHours = overtimeHours;
    }
}
```

**Exercises**
1. Write `Animal(name)`, `Dog(name, breed)` extending it, and `Puppy(name, breed, ageMonths)` extending `Dog`, with getters. `new Puppy("Rex", "Lab", 3)` should print `Rex Lab 3`.
2. Delete the `super(...)` line in `Dog`, read the compile error, put it back.

## 1.2 Overriding and `super.method()`

- Same name and parameters as the parent's method, with `@Override`. All methods are virtual by default.
- `super.method()` runs the parent's version. The lab requires it in every subclass calculation.

```java
return super.calculateSalary() + 300 * overtimeHours;   // inside Developer.calculateSalary()
return super.toString() + " overtime=" + overtimeHours; // inside Developer.toString()
```

- **The key trick:** `Employee.toString()` must use `calculateSalary()`, not the `baseSalary` field. Then each subclass prints its own salary automatically (the method is virtual).
- `TeamLead` extends `Developer`, so its `toString()` gets `Developer`'s text (already ending in `overtime=H`) from `super.toString()` and appends ` team=T`.

Check your classes against this table (the bonus applies to the **total**, and only for `teamSize >= 5`):

| Object | Calculation | Expected |
|---|---|---|
| `Employee(1000)` | base | `1000.00` |
| `Developer(1500, overtime 10)` | 1500 + 300 * 10 | `4500.00` |
| `TeamLead(2000, overtime 5, team 4)` | (2000 + 1500) + 1000 * 4 | `7500.00` |
| `TeamLead(2000, overtime 5, team 5)` | ((2000 + 1500) + 1000 * 5) * 1.05 | `8925.00` |
| `Intern(800, 5 months)` | 60% of base | `480.00` |
| `Intern(800, 6 months)` | 80% of base | `640.00` |

Expected `toString()` lines:
```
e1 Ana salary=1000.00
d1 Bob salary=4500.00 overtime=10
l1 Cleo salary=8925.00 overtime=5 team=5
i1 Dan salary=640.00 months=8
```

**Exercise:** give `Animal` a `describe()` returning `"I am " + name`. Override it in `Dog` and `Puppy` with `super.describe() + " and ..."`. Print a `Puppy`'s description, it should contain all three parts.

## 1.3 Polymorphism

- A parent-typed variable can hold a child object: `Employee e = new Developer(...)`.
- The variable's type decides what you may call (compile time). The object's real type decides which override runs.
- `e.getOvertimeHours()` doesn't compile through an `Employee` variable.
- An `Employee[]` can hold all four types, and a loop calling `toString()` prints each with its own rules.

```java
Employee e = new TeamLead("l1", "Cleo", 2000, 5, 5);
e.calculateSalary();    // TeamLead's version runs (8925.0), not Employee's
```

**Exercise:** fill an `Employee[]` with one of each of the four types and print it.

## 1.4 The statistics trap: `instanceof`

- `x instanceof Developer` is also **true for a `TeamLead`**. The lab says team leads are not developers.
- Fix: check the most specific class first (`TeamLead`, then `Developer`, then `Intern`, else others), using `if / else if`.
- Alternative: exact class test `x.getClass() == Developer.class`, but then every class (including `Employee.class`) needs its own branch.

```java
if (x instanceof TeamLead) teamLeads++;
else if (x instanceof Developer) developers++;
else if (x instanceof Intern) interns++;
else others++;
```

**Exercise:** with `Puppy extends Dog extends Animal`, count animals, dogs and puppies in `[Animal, Dog, Puppy, Puppy]`, where puppies are not dogs.
- Right order: puppies 2, dogs 1, others 1.
- Wrong order (dog check first): dogs 3, puppies 0, others 1.

## 1.5 `Company`: array of objects plus a count

- `new Employee[capacity]` makes `capacity` `null` slots. Keep an `int count` of hired employees.
- Every loop runs to `count`, never to `array.length`.
- `highestPaid()` and `countAbove()` use strict `>`, so a tie keeps the first.
- `averageSalary()` divides by `count`, guard `count == 0`.
- No generics in this lab, arrays only.
- The lab doesn't say what `hire()` does when the company is full, or what `highestPaid()` returns when it's empty. Guard both (ignore the extra hire, return `null`).

## 1.6 The locale trap

- Use `double`. Add `in.useLocale(Locale.US);` after creating the `Scanner`, and use `Locale.US` in `String.format` / `printf`, otherwise a decimal-comma machine reads `100.5` wrong and prints `4500,00`.

## 1.7 Parsing the input

- Read `n`, then for each line `type = in.next()`, then `id`, `name` (single tokens), `base` (`nextDouble`), and the extra ints depending on the type (`D`: 1, `L`: 2, `I`: 1).
- Use `switch (type)` with `case "E":`, and put each case in `{ }` with a `break;`, otherwise same-named variables clash.
- The last line is the threshold.


## 1.8 Build order and full sample

Order: `Employee` → `Developer` → `TeamLead` → `Intern` → `Company.hire/printAll` → statistics → totals → `highestPaid` / `countAbove` → `main`.

Sample input:
```
5
E e1 Ana 1000
D d1 Bob 1500 10
L l1 Cleo 2000 5 5
I i1 Dan 800 8
I i2 Eli 800 3
1000
```

Expected output (computed by hand):
```
=== FINKI Soft ===
e1 Ana salary=1000.00
d1 Bob salary=4500.00 overtime=10
l1 Cleo salary=8925.00 overtime=5 team=5
i1 Dan salary=640.00 months=8
i2 Eli salary=480.00 months=3
Developers: 1, Team leads: 1, Interns: 2, Others: 1
Total payroll: 15545.00
Average salary: 3109.00
Highest paid: l1 Cleo (8925.00)
Employees with salary above 1000.00: 2
```
The lab text doesn't say how many decimals the total, average and threshold use. I assumed 2, so check your lab's sample output. `Ana` earns exactly 1000, so she isn't counted (strictly greater).

Edge cases: a tie for highest paid (`E e1 A 100`, `E e2 B 100`, threshold `100` gives `Highest paid: e1 A (100.00)` and count `0`), team of 4 vs 5, internship of 5 vs 6 months, a team lead appearing only under "Team leads".

---

# 2. Lab 2: Warehouse (generics)

## 2.1 Generic classes: `Pair<K, V>`

- Type placeholders go in angle brackets after the class name. Use them as types inside the class.
- Type arguments must be objects: `Pair<String, Double>`, not `Pair<String, double>`.
- `<>` on the right side infers the types.
- Naming convention: `T` = type, `E` = element, `K` / `V` = key / value.

```java
class Pair<K, V> { ... }                                // fields K key, V value, getKey(), getValue()
Pair<String, Double> p = new Pair<>("Fridge", 11.0);
double v = p.getValue();                                // Double unboxes automatically
```

**Exercise:** write `Pair<K, V>`. `new Pair<>("age", 20)` printed as `key=value` gives `age=20`.

## 2.2 Bounded types: `T extends Product`

- Inside `Container<T>` you can only call `Object`'s methods. The bound lets you call `finalPrice()`:

```java
class Container<T extends Product> { ... }
```

- `extends` is used for the bound, even for interfaces.
- Toy example with the same shape: in `class Box<T extends Number>`, a `T value` can call `value.doubleValue()`. `new Box<>("hi")` doesn't compile.

## 2.3 `ArrayList<T>` inside a generic class

(Allowed in this lab, unlike Lab 1.)

- Field: `private ArrayList<T> items = new ArrayList<>();` plus your own `capacity`. `add` returns `false` when `items.size() >= capacity`, otherwise adds and returns `true`.
- `mostExpensive()`: `null` if empty, otherwise keep the best so far with strict `>` (a tie keeps the first).

**Exercise (covers 2.2 and 2.3):** write `Bag<T extends Number>` with a capacity, `boolean add(T)` and `double total()` (use `x.doubleValue()`). With capacity 2, adding `5`, `7`, `9` prints `true`, `true`, `false`, and `total()` is `12.0`. Then remove the bound and read the error.

## 2.4 Generics and subtyping (your first slide, applied)

- `Container<Food>` is **not** a `Container<Product>`.
- But a `Container<Product>` accepts a `Food` in `add`: with `T = Product`, the parameter is a `Product`, and a `Food` is one. That's why `Overflow` works.
- `Container<Food>.mostExpensive()` returns a `Food`, so `getDaysToExpiry()` works directly, no cast.

```java
Container<Product> overflow = new Container<>("Overflow", 2);
overflow.add(new Food("Milk", 2.0, 2));                  // OK
// Container<Product> c = new Container<Food>("x", 1);   // ERROR, try it and read it
```

## 2.5 The `Product` hierarchy

Same pattern as 1.2. `Product.toString()` uses `price` and `finalPrice()` (virtual), both with 2 decimals.

| Object | Rule | Expected `finalPrice()` |
|---|---|---|
| `Product(10.00)` | price | `10.00` |
| `Food(2.00, days 3)` | 3 or fewer days: 50% | `1.00` |
| `Food(2.00, days 4)` | unchanged | `2.00` |
| `Electronics(500.00, warranty 24)` | not longer than 24: unchanged | `500.00` |
| `Electronics(500.00, warranty 25)` | longer than 24: plus 15% | `575.00` |

```
Milk price=2.00 final=1.00 days=2
Phone price=500.00 final=575.00 warranty=36
```
Add getters for `daysToExpiry` and `warrantyMonths` (Alt+Insert), `main` needs them.

## 2.6 `Container` methods

- `totalValue()` sums `finalPrice()`. `summary()` returns `Pair<String, Double>` of (name, total).
- `print()` format:
```
=== Fridge (2/2) ===
Milk price=2.00 final=1.00 days=2
Cheese price=10.00 final=10.00 days=10
Total: 11.00
Most expensive: Cheese (10.00)
```
Empty container: `=== Tech (0/3) ===`, `Total: 0.00`, `Most expensive: none`.
- Null-check `mostExpensive()` before printing. The lab doesn't say if `(PRICE)` is the price or the final price, I assumed final, so check your lab's sample.

## 2.7 Main flow

- Create `Container<Food> fridge`, `Container<Electronics> tech`, `Container<Product> overflow` from the first line (three capacities).
- For each line: `F name price days` or `E name price warranty`. A food goes to `fridge`, if `add` returns `false` try `overflow`, if that also fails print `Rejected: NAME`. Electronics are the same with `tech`.
- Print `Rejected` lines while reading, they come first.
- No casting means each item must be created in a variable of its **own** type. A `Product p = new Food(...)` would not fit into `fridge`, which is a `Container<Food>`:

```java
Food f = new Food(name, price, days);
if (!fridge.add(f) && !overflow.add(f)) {
    System.out.println("Rejected: " + name);
}
```
- Then `print()` for fridge, tech, overflow. Most valuable container from the three `summary()` values (strict `>`, tie keeps the first).
- Last two lines only if the container isn't empty, taken from `mostExpensive()` with no cast.

## 2.8 Full samples

Sample 1:
```
2 1 1
6
F Milk 2.00 2
F Cheese 10.00 10
F Yogurt 3.00 5
E Phone 500.00 36
E Laptop 1000.00 12
E Mouse 20.00 6
```
```
Rejected: Laptop
Rejected: Mouse
=== Fridge (2/2) ===
Milk price=2.00 final=1.00 days=2
Cheese price=10.00 final=10.00 days=10
Total: 11.00
Most expensive: Cheese (10.00)
=== Tech (1/1) ===
Phone price=500.00 final=575.00 warranty=36
Total: 575.00
Most expensive: Phone (575.00)
=== Overflow (1/1) ===
Yogurt price=3.00 final=3.00 days=5
Total: 3.00
Most expensive: Yogurt (3.00)
Most valuable container: Tech (575.00)
Top food expires in 10 days
Top electronics warranty: 36 months
```
`Yogurt` in `Overflow` still prints `days=5`: the object is a `Food` and `toString()` is virtual.

Sample 2 (empty containers, a rejection):
```
1 1 0
2
F Milk 2.00 3
F Bread 1.50 1
```
```
Rejected: Bread
=== Fridge (1/1) ===
Milk price=2.00 final=1.00 days=3
Total: 1.00
Most expensive: Milk (1.00)
=== Tech (0/1) ===
Total: 0.00
Most expensive: none
=== Overflow (0/0) ===
Total: 0.00
Most expensive: none
Most valuable container: Fridge (1.00)
Top food expires in 3 days
```
No "Top electronics" line, because `Tech` is empty.

---

# 3. IntelliJ tricks for these labs

**Alt+Insert (Generate) inside a class**
- `Constructor`: in a subclass it asks which **parent constructor** to call (when there's more than one), then which fields to add, and writes `super(id, name, baseSalary);` for you.
- `Getter`, `Setter`, `Getter and Setter`: select the fields.
- `Override Methods...` (also `Ctrl+O`): lists everything you can override (`toString`, `calculateSalary`, ...), and writes the `@Override` stub with a `super.method()` call inside.
- `Implement Methods...` (`Ctrl+I`): the same for abstract methods or interfaces.
- `toString()`: handy for quick debugging, but you'll write the lab's custom format by hand.

**Overriding by typing:** inside the child class, start typing the method name (`calcu`), press `Ctrl+Space`, pick the inherited method, and IntelliJ writes the whole override with `@Override` and a `return super....;` body.

**Also useful:** `Alt+Enter` on a red, undefined class or method offers **Create class / Create method** with the right signature.

**Testing input quickly (very useful for these labs)**
- Run → Edit Configurations... → Modify options → **Redirect input** → choose a text file containing your sample input. The program then reads from the file instead of making you retype everything each run.
- Make one file per sample (`sample1.txt`, `sample2.txt`) and switch between them.
