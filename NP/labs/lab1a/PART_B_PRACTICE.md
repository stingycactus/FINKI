# Lab 1 Part B practice: interfaces, lambdas, functional interfaces

Part B extends your Part A classes, so these exercises do the same. Each one builds on your current `Ticket` / `ParkingLot` code and on the previous exercise. They're guesses at the kind of requirements Part B adds, based on Auds 1 and 2, not the real Quiz B.

Order by priority: **B3 is the most likely**, then B2, B1 and B4. Topics that aren't in the auds are at the end, under "Extra study material".

Work in a copy of your Part A file so the original stays untouched.

---

## B1. Electric vehicles (interface + `instanceof`)

From Aud 1, Bank (`InterestBearingAccount` and `Bank.addInterest()`).

**Exercise:** The garage installs charging stations. Electric vehicles pay for parking by the hour, like a normal hourly ticket, plus a fee for charging.

1. Create an interface `Chargeable` with one method:
   - `double chargingFee()` — returns the fee for charging the vehicle.
2. Create a class `ElectricHourlyTicket` that extends `HourlyTicket` and implements `Chargeable`:
   - `public ElectricHourlyTicket(String plate, int minutes)` — initializes the attributes through the parent constructor.
   - `public double chargingFee()` — the charging fee is a fixed `30`. Store it as a constant, not a magic number.
   - `public double price()` — the hourly price plus the charging fee. Reuse the parent's calculation instead of repeating it.
3. In `ParkingLot`, add:
   - `public double totalChargingFees()` — the sum of the charging fees of all tickets in the lot that are `Chargeable`. Tickets that aren't `Chargeable` are skipped. If there are none, return `0.0`.

**Expected:**

| Ticket | `price()` | `chargingFee()` |
|---|---|---|
| `ElectricHourlyTicket("E5", 90)` | `130.0` (2 started hours = 100, + 30) | `30.0` |
| `ElectricHourlyTicket("E6", 60)` | `80.0` (1 started hour = 50, + 30) | `30.0` |
| `HourlyTicket("A1", 90)` | `100.0` | not `Chargeable` |

A lot containing `E5`, `E6` and `A1`: `totalRevenue()` = `310.0`, `totalChargingFees()` = `60.0`.

Also check that `new ElectricHourlyTicket(null, 10)` still throws `IllegalArgumentException`, because the validation in `Ticket` runs through `super(...)`.

## B2. Your own functional interface: a ticket factory

From Aud 2, task 2 (Calculator's `Operation` + `OperationFactory`). Same idea as `VehicleMaker`.

1. `@FunctionalInterface interface TicketFactory { Ticket create(String plate, int minutes); }`
2. Three constants, one per type: `HOURLY`, `DAILY`, `ELECTRIC`. Write one as a lambda and the others as method references (`HourlyTicket::new`).
3. `static TicketFactory getFactory(String type)`: `"H"`, `"D"`, `"E"`, otherwise throw `IllegalArgumentException("Unknown type X")`.
4. Create tickets with `getFactory(type).create(plate, minutes)`.

## B3. `ParkingLot` methods that take built-in functional interfaces

From Aud 2, task 4 (Course). All loop to `ticketCount`.

| Method | Uses |
|---|---|
| `void forEach(Consumer<Ticket> action)` | `action.accept(t)` |
| `int count(Predicate<Ticket> condition)` | `condition.test(t)` |
| `Ticket[] filter(Predicate<Ticket> condition)` | size the result with `count(condition)` first |
| `Ticket findFirst(Predicate<Ticket> condition)` | `null` if none match |
| `double revenue(Predicate<Ticket> condition)` | sum of `price()` for matching tickets |
| `String[] mapToLabels(Function<Ticket, String> mapper)` | `mapper.apply(t)` |

Bonus: rewrite `totalRevenue()` as `return revenue(t -> true);`.

Course also has `mutate` and `conditionalMutate`. They don't apply here, because tickets are immutable (no setters allowed).

## B4. Adding tickets from a `Supplier`

From Aud 2, task 4 (Course's `enroll(Supplier<Student>)`).

`int addAll(int n, Supplier<Ticket> supplier)`: calls `supplier.get()` up to `n` times and adds each ticket with your existing `addTicket`. When the lot is full, stop and return how many were added.

- `addTicket` throws `LotFullException`, which is checked. Catch it **inside `addAll`** around the `addTicket` call. A `Supplier` lambda itself can't throw it.
- Don't name it `addTicket(Supplier<Ticket>)`. Then `addTicket(null)` (the `ADD_NULL` command) becomes ambiguous between the two overloads and won't compile.

---

## Test for B1–B4

**`addAll`:** `new ParkingLot(3)`, then `addAll(5, () -> new HourlyTicket("SUP", 30))` returns `3`. Count is `3`, revenue is `150.0`.

**Everything else:** a lot with capacity 10, filled with B2's factory:

```text
H A1 61
D B2 1441
H C3 30
D D4 100
E E5 90
```

| Call | Expected |
|---|---|
| `forEach` printing `plate + " " + price()` | `A1 100.0`, `B2 600.0`, `C3 50.0`, `D4 300.0`, `E5 130.0` |
| `totalRevenue()` | `1180.0` |
| `count(t -> t instanceof DailyTicket)` | `2` |
| `count(t -> t.price() > 100)` | `3` |
| `filter(longStay.and(hourly))`, with `longStay = t -> t.getMinutes() > 60`, `hourly = t -> t instanceof HourlyTicket` | `A1`, `E5` |
| `findFirst(t -> t.price() >= 300)` | `B2` |
| `revenue(t -> t instanceof HourlyTicket)` | `280.0` (`E5` counts: it **is** an `HourlyTicket`) |
| `totalChargingFees()` | `30.0` |
| `mapToLabels(t -> t.getPlate() + ":" + t.price())` | `[A1:100.0, B2:600.0, C3:50.0, D4:300.0, E5:130.0]` |
| `getFactory("X")` | `IllegalArgumentException`, message `Unknown type X` |

---

## Easy to miss

- **Tickets are immutable.** Part B can't add setters, so a `Consumer<Ticket>` can only read (print, collect). Anything "changed" (labels, totals) is computed, not stored.
- **`instanceof` includes subclasses.** `ElectricHourlyTicket` counts as an `HourlyTicket`. If Part B wants "hourly but not electric", check the electric type first or add `.and(t -> !(t instanceof Chargeable))`.
- **A lambda for a built-in interface can't throw a checked exception** like `LotFullException`. Catch it in your method, around the call.
- **Keep the Part A rules.** A failed add still must not change the count or revenue.
- **`Predicate` combining:** `.and()` is used in Aud 2. `.or()` and `.negate()` work the same way.
- **Fix from Part A first:** `LotFullException` needs the no-argument constructor `LotFullException()`.

---

# Extra study material (not covered in auds)

Only if there's time after B1–B4. These are common functional-interface topics, but neither aud has them.

## E1. Transforming values: `UnaryOperator`

`UnaryOperator<T>` is a `Function<T, T>` (same type in and out), so the method is again `apply`.

```java
UnaryOperator<Double> discount = p -> p * 0.9;
discount.apply(100.0);   // 90.0
```

Add an overload `double totalRevenue(UnaryOperator<Double> adjust)` that sums `adjust.apply(t.price())`. Tickets are immutable, so a discount only changes the **computed** total.

Test (same 5 tickets): `totalRevenue(p -> p * 0.9)` → `1062.0`

## E2. Comparing: `Comparator`

`Comparator<T>` is a functional interface too. `compare(a, b)` returns a positive number if `a` is "bigger".

```java
Comparator<Ticket> byPrice = Comparator.comparingDouble(Ticket::price);
byPrice.compare(t1, t2) > 0     // t1 costs more
byPrice.reversed()              // the opposite order
```

Add `Ticket max(Comparator<Ticket> cmp)`, which returns `null` if the lot is empty and keeps the first ticket on a tie (strict `>`).

Test: `max(Comparator.comparingDouble(Ticket::price))` → `B2`

## E3. Removing: `removeIf(Predicate<Ticket>)`

`int removeIf(Predicate<Ticket> condition)` removes matching tickets, **keeps the array packed** (no `null` gaps before `ticketCount`), updates `ticketCount`, and returns how many were removed.

Hint: copy every ticket you keep to position `j++`, then set the leftover slots to `null`.

Test: `removeIf(t -> t.getMinutes() < 60)` → removes `1` (C3), then count `4`, total `1130.0`
