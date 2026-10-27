# NP prep: Auds 1 and 2 (OOP, exceptions, lambdas)

Parts 1 and 2 teach the concepts one at a time. All exercises build **one project, a parking `Garage`**, and each exercise extends the code from the previous one. Part 3 is the auds themselves; by then every task there is something you've already built once in the Garage.

Setup: one IntelliJ project, all classes in `Main.java`, only `Main` is `public`. Keep the old `main` code around as comments: later exercises re-run earlier samples to check nothing broke.

Java 11 limits (if NP's checker is Java 11 like the labs): no `switch` with `->`, no `v instanceof Chargeable c` pattern (Java 16), no records, no `.formatted()`.

---

# 1. Aud 1 concepts: abstract classes, interfaces, exceptions

## 1.1 Abstract classes

- `abstract class` can't be created with `new`. It exists only to be extended.
- An `abstract` method has no body, and every non-abstract child **must** override it.
- It can still have fields, a constructor (called with `super(...)`), and normal methods.
- Use it when the parent is a real "is-a" idea with shared state, but has no sensible default for some method.

```java
abstract class Shape {
    private final String name;
    Shape(String name) { this.name = name; }
    abstract double area();                       // no body, ends with ;
    @Override
    public String toString() { return name + " " + area(); }   // calls the child's area()
}
```

**Exercise**
1. Write `abstract class Vehicle` with private `plate` (String) and `hours` (int), getters, and `abstract double fee()`. `toString()` returns `PLATE Hh fee=F` (2 decimals) and uses `fee()`, not a field.
2. `Car` charges 2.0 per hour, `Truck` 5.0 per hour. `new Car("SK1", 3)` prints `SK1 3h fee=6.00`, `new Truck("SK2", 2)` prints `SK2 2h fee=10.00`.
3. Try `new Vehicle("X", 1)` and read the error.

## 1.2 `static final` constants and an automatic counter

- `static final double RATE = 2.0;` is a class-wide constant (name in CAPS). Use it as `Car.RATE` from outside.
- A `private static int nextId = 1;` belongs to the class, not the object, so it keeps counting across all objects. That gives "a sequential number assigned automatically" (Aud 1 Bank wording).

```java
private static int nextTicket = 1;
private final int ticket;
// in the constructor:
this.ticket = nextTicket++;          // 1, 2, 3, ... across ALL vehicles, any subclass
```

**Exercise:** replace the magic numbers in `Car` and `Truck` with `RATE` constants. Give `Vehicle` an automatic `ticket` and prefix `toString()` with `#T `: `#1 SK1 3h fee=6.00`.

## 1.3 Interfaces

- An interface is a list of methods a class promises to have. Methods are automatically `public abstract`, so the implementing method must be `public`.
- A class `extends` one class but `implements` any number of interfaces: `class A extends B implements X, Y`.
- Abstract class vs interface: abstract class = shared code and state ("is a"), interface = a capability that unrelated classes can share ("can do").
- A child inherits the parent's interfaces: if `B implements X` and `C extends B`, then `C` is an `X` too.

```java
interface Chargeable {
    void charge();
}
class ElectricCar extends Car implements Chargeable {
    @Override
    public void charge() { ... }      // must be public
}
```

**Exercise** (this is the exact shape of the Bank task)
1. `interface Chargeable { void charge(); }`
2. `ElectricCar extends Car implements Chargeable`, with an extra `battery` (int %). `static final int CHARGE_STEP = 20`. Add `protected void addBattery(int amount)` that caps at 100, and `charge()` calls `addBattery(CHARGE_STEP)`. `toString()` appends ` battery=B%`.
3. `FastElectricCar extends ElectricCar` (no `implements` needed, it's inherited). Its `charge()` adds **double** the parent's step, written as `CHARGE_STEP * 2`, not `40`.

## 1.4 Interface as a type: `instanceof` plus cast, and a growing array

- A variable can have an interface type: `Chargeable c = new ElectricCar(...)`.
- Through a `Vehicle` variable you can't call `charge()`, even if the object is electric. Check, then cast:

```java
if (v instanceof Chargeable) {
    ((Chargeable) v).charge();       // parentheses around the cast, then the call
}
```

- Growing a full array: `arr = Arrays.copyOf(arr, arr.length * 2);` (`import java.util.Arrays;`). Use `arr.length`, not a fixed field: the Aud 1 Bank solution uses `max * 2` with `max` never changing, so the second growth doesn't grow at all and crashes.
- Loop to `count`, never `arr.length` (the empty slots are `null`).

**Exercise:** `Garage` with `Vehicle[] vehicles`, `int count`, constructor `Garage(int capacity)`, `park(Vehicle)` (grows when full), `printAll()`, `totalFees()`, `chargeAll()`.

Test with `new Garage(2)` (forces one growth):
```java
g.park(new Car("SK1", 3));
g.park(new Truck("SK2", 2));
g.park(new ElectricCar("EV1", 2, 50));
g.park(new FastElectricCar("EV2", 1, 90));
```
```
#1 SK1 3h fee=6.00
#2 SK2 2h fee=10.00
#3 EV1 2h fee=4.00 battery=50%
#4 EV2 1h fee=2.00 battery=90%
Total fees: 22.00
```
After `chargeAll()` and `printAll()`, `EV1` shows `battery=70%`, `EV2` shows `battery=100%` (capped). The electric cars cost 2.0/h because they inherit `Car.fee()`.

## 1.5 Refactoring a "type code" into subclasses

Aud 1 task 2 (Alien) gives you code like this and asks you to fix it:

```java
class Ticket {
    static final int CAR = 0, TRUCK = 1;
    int type;                        // public field, no encapsulation
    double fee() {
        if (type == CAR) return hours * 2;
        else if (type == TRUCK) return hours * 5;
        ...
    }
}
```

- Every new type means editing every `if` chain. With subclasses, each class carries its own behavior and the caller just calls `fee()` (polymorphism).
- Recipe: abstract parent with `private` fields and getters, one subclass per type code, the `if` branch body becomes that subclass's override, and the `type` field disappears.

**Exercise:** your `Vehicle` is already the refactored version. Add `Motorcycle` (1.0 per hour). Notice that `Garage` needs **zero** changes. In the `Ticket` version, count the places you'd have to edit.

## 1.6 Exceptions (lecture NP26-02)

- Hierarchy: `Throwable` → `Error` (JVM problems, don't handle) and `Exception`. `Exception` → `RuntimeException` (unchecked) and everything else (checked).
- **Unchecked** (`RuntimeException` and subclasses: `NullPointerException`, `ArrayIndexOutOfBoundsException`, `IllegalArgumentException`, ...): bugs in your code. The compiler doesn't force you to handle them. Lecture rule: "Don't catch it, FIX IT!"
- **Checked** (everything else that extends `Exception`): expected failures, like bad user input. The compiler forces you to either `catch` it or declare it with `throws` in the method signature.
- `throw new X(...)` throws, `throws X` in the signature declares. Both words are needed.
- Several `catch` blocks: the first matching one runs, so put the specific type before the general one (`Exception` last). `finally` always runs.
- A custom exception is a class that extends `Exception` (checked) or `RuntimeException` (unchecked). Pass the message to `super(...)`, and `getMessage()` is inherited.

```java
class UnknownTypeException extends Exception {
    public UnknownTypeException(char type) {
        super(String.format("%c is unknown", type));
    }
}

static Vehicle create(char type, ...) throws UnknownTypeException {   // declare
    ...
    throw new UnknownTypeException(type);                               // throw
}

try {
    Vehicle v = create('X', "SK3", 1);
} catch (UnknownTypeException e) {
    System.out.println(e.getMessage());
} finally {
    System.out.println("always runs");
}
```

**Exercise**
1. Write `UnknownVehicleTypeException extends Exception` with the message `X is an unknown vehicle type`.
2. In `Garage`, write `static Vehicle create(char type, String plate, int hours)`: `C` → `Car`, `T` → `Truck`, `M` → `Motorcycle`, anything else throws. Call it with `'X'` inside a `try`, print the message.
3. Remove `throws` from the signature and read the error. Then remove the `try/catch` around the call and read that error too.
4. In the `Vehicle` constructor, throw `IllegalArgumentException` if `hours < 0`. Note that nothing forces a `throws` or a `catch` this time (unchecked).

## 1.7 Nested classes and an input loop that survives bad lines

- A class can be declared inside another class. From outside you name it `Outer.Inner`, for example `catch (Garage.UnknownVehicleTypeException e)`.
- **Non-static** nested (inner) class: every object is tied to an outer object, so it can't be created from a `static` method. **`static` nested**: just a class living in the other's namespace.
- Aud 1 Calculator puts its exception inside `Calculator` as a non-static inner class. That works there only because `execute` isn't static.

**Exercise:** move your exception inside `Garage` as `static class UnknownVehicleTypeException`. Then remove `static` and read the error (your `create` is static). Put it back.

Then write a `main` loop (the Calculator's loop with vehicles): read whole lines with `nextLine()`, skip blank lines, stop on `q`/`Q`, otherwise `split("\\s+")`, call `create`, park and print `Parked V`. On an unknown type, print the message and keep reading. At the end print the total.

Input:
```
C SK1 3
T SK2 2
X SK3 1
M SK4 4
q
```
Output:
```
Parked #1 SK1 3h fee=6.00
Parked #2 SK2 2h fee=10.00
X is an unknown vehicle type
Parked #3 SK4 4h fee=4.00
Total fees: 20.00
```
`X` uses no ticket number: the exception is thrown before any `Vehicle` is created. Save this input as `garage1.txt`, because you'll re-run it in Part 2.

---

# 2. Aud 2 concepts: anonymous classes, lambdas, `java.util.function`

## 2.1 Anonymous classes

- Create a one-off implementation of an interface, or a subclass of a class, right where you need it, without naming it.
- Works for abstract classes too (with constructor arguments), and can override several methods.

```java
Chargeable test = new Chargeable() {          // "new Interface() { body }"
    @Override
    public void charge() { System.out.println("test charge"); }
};

Shape unit = new Shape("unit") {              // abstract class, constructor args in ()
    @Override
    double area() { return 1; }
};
```

**Exercise**
1. Make a `Chargeable` anonymous object that prints `charging a test unit`, and call `charge()`.
2. Add a free guest spot: `Vehicle visitor = new Vehicle("GUEST", 5) { ... fee() returns 0 ... };`. Park it in the 1.4 garage. It prints `#5 GUEST 5h fee=0.00`, and the total stays `22.00`.

## 2.2 Lambdas and `@FunctionalInterface`

- A **functional interface** has exactly one abstract method. Only those can be written as a lambda. `@FunctionalInterface` makes the compiler check it.
- A lambda is a short form of the anonymous class: parameters, `->`, body. The parameter types come from the interface.

```java
Chargeable c = () -> System.out.println("charging");      // no params
Op square = x -> x * x;                                    // one param, no parentheses needed
Op2 add = (a, b) -> a + b;                                 // two params, expression = returned
Op2 safeDiv = (a, b) -> {                                  // block body needs return
    if (b == 0) return 0;
    return a / b;
};
```

- A lambda can't replace an abstract **class** (`Vehicle`). That's why the guest in 2.1 needed an anonymous class.
- Local variables used inside a lambda must be effectively final (never reassigned).
- **Method references** are an even shorter lambda that only calls one method:

| Lambda | Method reference |
|---|---|
| `s -> System.out.println(s)` | `System.out::println` |
| `v -> v.getPlate()` | `Vehicle::getPlate` |
| `s -> Integer.parseInt(s)` | `Integer::parseInt` |
| `(p, h) -> new Car(p, h)` | `Car::new` |

**Exercise** (this is exactly what Aud 2 does to the Calculator)
1. Replace your 2.1 anonymous `Chargeable` with a lambda.
2. Write `@FunctionalInterface interface VehicleMaker { Vehicle make(String plate, int hours); }`.
3. In `Garage`, store one lambda per type as constants: `private static final VehicleMaker CAR = (p, h) -> new Car(p, h);` (and `TRUCK`, `MOTO`).
4. Replace `create` with `static VehicleMaker getMaker(char type) throws UnknownVehicleTypeException`, which returns the right constant or throws. The loop becomes `getMaker(type).make(plate, hours)`.
5. Re-run `garage1.txt`. The output must be identical to 1.7.
6. Put the cursor on a lambda, press `Alt+Enter` → "Replace lambda with method reference" (`Car::new`).

## 2.3 Built-in functional interfaces (`java.util.function`)

`import java.util.function.*;`. Type arguments are wrappers: `Integer`, not `int`.

| Interface | Method | Takes → returns | Example |
|---|---|---|---|
| `Function<T, R>` | `apply` | `T` → `R` | `Function<String, Integer> len = s -> s.length();` |
| `BiFunction<T, U, R>` | `apply` | `T, U` → `R` | `BiFunction<Integer, Integer, Integer> sum = (a, b) -> a + b;` |
| `Predicate<T>` | `test` | `T` → `boolean` | `Predicate<Integer> even = n -> n % 2 == 0;` |
| `Consumer<T>` | `accept` | `T` → nothing | `Consumer<String> print = System.out::println;` |
| `Supplier<T>` | `get` | nothing → `T` | `Supplier<Long> now = System::currentTimeMillis;` |

- Combining predicates: `p1.and(p2)`, `p1.or(p2)`, `p1.negate()`.
- A lambda for these **can't throw a checked exception**: `get()`, `apply()` and the others don't declare `throws`. Catch it inside the lambda.

**Exercise**
1. Delete your `VehicleMaker` interface and use `BiFunction<String, Integer, Vehicle>` instead (`getMaker` now returns that, and you call `.apply(plate, hours)`). Re-run `garage1.txt`, same output.
2. Add a `Supplier<Vehicle> reader` in `main` that reads one line, and returns the vehicle via `getMaker`. First let the exception escape and read the compile error, then catch it inside, print the message and `return null`. Make `park` ignore `null`.

## 2.4 Your own methods that take lambdas

The caller decides **what** to do, your method decides **how to loop**. Inside, call the interface's method on each element:

```java
void forEach(Consumer<Vehicle> action) {
    for (int i = 0; i < count; i++) {
        action.accept(vehicles[i]);
    }
}
// call site
garage.forEach(v -> System.out.println(v.getPlate()));
```

**Exercise:** add these to `Garage` (all loop to `count`). This is exactly the Aud 2 `Course` class, with vehicles instead of students.
- `void forEach(Consumer<Vehicle> action)`
- `int count(Predicate<Vehicle> condition)`
- `Vehicle findFirst(Predicate<Vehicle> condition)`, `null` if none
- `Vehicle[] filter(Predicate<Vehicle> condition)`: size the new array with `count(condition)` first, then fill it
- `String[] mapToLabels(Function<Vehicle, String> mapper)`
- `void applyIf(Predicate<Vehicle> condition, Consumer<Vehicle> action)`, then rewrite `chargeAll()` as one `applyIf` call (`instanceof` check plus the cast inside the consumer)

`main`: read `n` (with `Integer.parseInt(sc.nextLine().trim())`, so the reader's `nextLine()` works right after), call `park(reader.get())` `n` times, then:
- `forEach(System.out::println)`
- `Trucks: ` + `count(v -> v instanceof Truck)`
- `Predicate<Vehicle> isLong = v -> v.getHours() >= 3;`, then `filter(isLong.and(v -> v.fee() > 5))`
- `findFirst` the first `Motorcycle`
- `mapToLabels(Vehicle::getPlate)` printed with `Arrays.toString`

Input:
```
5
C SK1 3
T SK2 2
M SK3 1
X SK9 9
T SK4 4
```
Output:
```
X is an unknown vehicle type
#1 SK1 3h fee=6.00
#2 SK2 2h fee=10.00
#3 SK3 1h fee=1.00
#4 SK4 4h fee=20.00
Trucks: 2
Long and expensive:
#1 SK1 3h fee=6.00
#4 SK4 4h fee=20.00
First motorcycle: #3 SK3 1h fee=1.00
Plates: [SK1, SK2, SK3, SK4]
```

---

# 3. The auds

Write each task yourself first, then compare with the posted solution. The posted solutions have bugs (listed per task). Spotting them is good exam practice.

## 3.1 Aud 1, task 1: Bank (= 1.1 to 1.4)

- Draw the hierarchy first (`Ctrl+H` on a class in IntelliJ shows it): `Account` ← `NonInterestCheckingAccount`, `Account` ← `InterestCheckingAccount` ← `PlatinumCheckingAccount`, with `InterestBearingAccount` implemented by `InterestCheckingAccount` (and so inherited by Platinum).
- Mapping: `Account` = `Vehicle`, `InterestBearingAccount` = `Chargeable`, `addAmount` = `addBattery`, Platinum = `FastElectricCar`, `Bank.addInterest` = `chargeAll`.
- Posted solution bugs:
  - `PlatinumCheckingAccount extends Account`, but the text says it **is an** `InterestCheckingAccount`.
  - The account number is passed in, but the text says it's assigned automatically (1.2).
  - `totalAssets()` and `addInterest()` loop over the whole array → `NullPointerException` on the empty slots.
  - Growth uses `max * 2`, and `max` never changes.

Test: `new Bank(2)`, then add Non 1000, Interest 1000, Platinum 1000, Non 500, Interest 200 (five accounts, which crashes the posted version).
```
Total: 3700.00
After interest: 3796.00
```
(1000 + 1030 + 1060 + 500 + 206)

## 3.2 Aud 1, task 2: Alien (= 1.5)

- `abstract class Alien` with `private` `health` and `name`, getters, `abstract int getDamage()`. `SnakeAlien` 10, `OgreAlien` 6, `MarshmallowManAlien` 1. The `type` field and the constants are gone.
- `calculateDamage()` just sums `getDamage()`. `addAlien` takes an index, so slots can stay empty: skip `null`.

Test: a pack of 4 with Snake, Ogre and Marshmallow at indexes 0 to 2 gives `17` (and doesn't crash on slot 3).

## 3.3 Aud 1, task 3: Calculator (= 1.6 and 1.7)

- `UnknownOperatorException` = your `UnknownVehicleTypeException`, and the operator `if` chain = your `create`.
- Posted solution bugs:
  - The sample input has `+5` and `/2` with no space, so `split("\\s+")` gives one part and `parts[1]` crashes. Take the operator as `line.charAt(0)` and the number from `line.substring(1).trim()`.
  - It prints with `%f` (`5.000000`), but the sample shows `5.0`. Plain `+` concatenation of a `double` gives `5.0`.
- Test with the exact sample from the statement (save it as `calc.txt`, use Redirect input).

## 3.4 Aud 2, task 1: three ways to implement an interface (= 2.1 and 2.2)

Write `Operation` and `MessageProvider` each as a named class, an anonymous class, and a lambda. Then `Alt+Enter` on each anonymous class → "Replace with lambda" to see that IntelliJ agrees.
```
Addition: 8
Multiplication: 15
Subtraction: 2
```
plus the three messages.

## 3.5 Aud 2, task 2: Calculator with lambdas (= 2.2 exercise)

- `OperationFactory.getOperation(char)` = your `getMaker`. Keep your 3.3 parsing fixes.
- The exception moves out of `Calculator` to top level here because the factory method is `static` (the 1.7 error).
- Same `calc.txt`, same output as 3.3.

## 3.6 Aud 2, task 3: built-in functional interfaces (= 2.3 table)

```
Length of 'Hello': 5
Sum of 5 and 3: 8
Is 4 even? true
Is 5 even? false
Printing: Hello, World!
```
The time line changes every run.

## 3.7 Aud 2, task 4: Course and Students (= 2.4)

- `Student`: `final` index. `setGrade` clamps to 5..10, and call `setGrade` from the constructor too, so a bad input grade is clamped as well (the posted one only clamps in the setter).
- `Course` = your `Garage` methods with `Student`.
- Posted solution gaps:
  - `toString()` loops over the whole array → `NullPointerException` when the course isn't full (capacity 10), and the header has no newline.
  - `main` never calls `mapToLabels` or the final `toString()`, and doesn't print after `conditionalMutate`, though the text asks for all three.
  - Drop the `Enter student...` prompt in the supplier so the output stays clean.

Input:
```
4
221001 Ana 8 95
221002 Bob 5 60
221003 Cleo 6 80
221004 Dan 10 85
```
Key output lines:
```
Passing and present (grade >= 6 and attendance >= 70):
Ana (221001), grade=8, attendance=95%
Cleo (221003), grade=6, attendance=80%
Dan (221004), grade=10, attendance=85%
First honor student (grade >= 9): Dan (221004), grade=10, attendance=85%
After +1 for everyone: Ana 9, Bob 6, Cleo 7, Dan 10 (capped)
After +1 for attendance >= 90: Ana 10, the rest unchanged
Labels (s -> s.getName() + ": " + s.getGrade()): Ana: 10, Bob: 6, Cleo: 7, Dan: 10
```

---

# 4. IntelliJ tricks for these auds

- `Ctrl+I` (Implement Methods): in a class that `implements` an interface or extends an abstract class, writes all required method stubs.
- `Alt+Enter` on a red call that throws a checked exception: "Add exception to method signature" or "Surround with try/catch". `Ctrl+Alt+T` surrounds any selected code with `try/catch`.
- `Alt+Enter` on `new Interface() {` → "Replace with lambda". On a lambda → "Replace lambda with method reference". Use it to check your hand-written lambdas.
- `Ctrl+P` inside a method's parentheses shows the expected parameter, for example `Predicate<Vehicle>`, so you know the lambda's shape.
- `Ctrl+H` shows the type hierarchy (Bank task).
- Redirect input (Run → Edit Configurations → Modify options → Redirect input) with `garage1.txt`, `calc.txt` and your Course sample.

Source: auditory exercises at https://finki-mk.github.io/NP_2025/en/
