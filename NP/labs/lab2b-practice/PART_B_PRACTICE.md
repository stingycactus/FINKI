# Lab 2 Part B practice: Extending the Validation System

Part B extends your own Part A classes, so this practice task is written the same way as the lab: per class, what to add. It's a guess at the kind of requirements Part B adds, based on Auds 2–3 and on what Lab 1's Part B did, not the real Quiz B.

Priority if time is short: **2.1 (`of`), 3 (`field` + new `UserValidation`) and 2.2 (`or`)** are the most likely. Then 1 (`merge`) and 2.3 (`andAll`), then 2.5–2.6.

Setup: `src/Lab2.java` here is a copy of your submitted Part A file. In IntelliJ: File → New → Module from Existing Sources… → pick the `lab2b-practice` folder, then work in this copy. Extra imports: `java.util.function.Predicate`, and `java.util.stream.Collectors` if you use streams.

---

## 1. Class `ValidationResult`: add one method

*(Immutable class + list copy, as in Lab 1 `Ticket` and Aud 3 `getItems()`.)*

- `public ValidationResult merge(ValidationResult other)` – returns a **new** result whose errors are this result's errors followed by the errors of `other`. Neither original result changes. Merging two successful results gives a successful result. If `other` is `null`, throw `IllegalArgumentException`.

Note: the list from `getErrors()` is unmodifiable, so build the new list as a copy and add to the copy.

## 2. Interface `Validator<T>`: add these methods

### 2.1 `static <T> Validator<T> of(Predicate<? super T> condition, String message)`

*(Aud 2: `Predicate`.)*

Returns a validator that is valid when `condition.test(value)` is `true`; otherwise the result contains the error `message`.

- If `condition` is `null`, or `message` is `null` or an empty string, throw `IllegalArgumentException` when the validator is created.
- The validator does not check for `null` values itself; combine it with `notNull()` using `and` when the value may be `null`.

### 2.2 `default Validator<T> or(Validator<? super T> other)`

*(Same structure as your `and`.)*

Returns a new validator that:

1. First executes the current validator. If it succeeds, returns its result without calling `other`.
2. Otherwise executes `other`. If it succeeds, returns its result.
3. If both fail, returns a result containing the errors of both, the current validator's errors first.

If `other` is `null`, throw `IllegalArgumentException` (when `or` is called).

### 2.3 `default Validator<T> andAll(Validator<? super T> other)`

*(Uses `merge` from 1. Compare with `and`, which stops at the first failure.)*

Returns a new validator that **always** executes both validators and returns all their errors, the current validator's errors first. If both succeed, the result is successful. If `other` is `null`, throw `IllegalArgumentException`.

### 2.4 `static <T, R> Validator<T> field(String name, Function<? super T, ? extends R> getter, Validator<? super R> validator)`

*(Aud 2: `Function`; Aud 3: generic method with two type variables.)*

Returns a validator for objects of type `T` that:

1. Reads a field of the object with `getter`.
2. Validates the field's value with `validator`.
3. Returns the errors with the prefix `name: ` (field name, colon, space). If the field is valid, the result is successful.

If any argument is `null`, throw `IllegalArgumentException` when the validator is created. A method reference such as `User::getName` can be passed as `getter`.

### 2.5 `static <T> List<T> filterValid(List<T> items, Validator<? super T> validator)`

*(Aud 2 task 4: `Course.filter`.)*

Returns a new list containing only the items that pass the validator, in their original order.

### 2.6 `static <T> long countInvalid(List<T> items, Validator<? super T> validator)`

*(Aud 2 task 4: `Course.count`.)*

Returns the number of items that fail the validator.

2.5 and 2.6 can be written with loops (like `Course`) or with streams (`filter`, `collect`, `count`).

## 3. Class `UserValidation`: rewrite `validate`

Rewrite `public static ValidationResult validate(User user)` so that it uses:

- `field(...)` once for each field: `name`, `age`, `email`, with the same rules as in Part A,
- `Validator.of(...)` for the `@` check of `email` (error `must contain @`),
- `merge` to combine the three results, in the order name, age, email.

The behaviour must stay exactly the same as in Part A: re-run both `USER` tests from `labs/lab2a/README.md`, and the output must not change.

---

## Exceptions and Edge Cases

| Situation | Exception |
|---|---|
| `merge(other)` — `other` is `null` | `IllegalArgumentException` |
| `Validator.of(condition, message)` — `condition` is `null`, or `message` is `null`/empty (when created) | `IllegalArgumentException` |
| `or(other)` / `andAll(other)` — `other` is `null` (when called) | `IllegalArgumentException` |
| `Validator.field(...)` — any argument is `null` (when created) | `IllegalArgumentException` |

Also keep in mind:
- `andAll` always runs **both** validators, so `minLength(5).andAll(hasAt)` on a `null` value would call `contains` on `null`. Put `notNull()` in front with `and` when values may be `null`.
- Argument checks go **before** `return v -> ...`, and value checks go inside the lambda (the same as in Part A).
- Error order is always the current validator first, then `other`; fields in the order name, age, email.
- Never add to a list returned by `getErrors()`. It's unmodifiable and throws.

---

## Usage Example (test `main`)

Paste as a separate class in `Lab2.java` and run it with the green arrow:

```java
class PartBTest {
    public static void main(String[] args) {
        System.out.println("== 2.1 of");
        Validator<String> hasAt = Validator.of(s -> s.contains("@"), "must contain @");
        System.out.println(hasAt.validate("ab").getErrors());
        System.out.println(hasAt.validate("a@b").isValid());
        Validator<String> maxLen10 = Validator.of(s -> s.length() <= 10, "must have at most 10 characters");
        System.out.println(maxLen10.validate("Ana").isValid() + " " + maxLen10.validate("Aleksandrina").getErrors());
        Validator<String> email = Validator.<String>notNull().and(Validator.minLength(5)).and(hasAt);
        System.out.println(email.validate(null).getErrors() + " " + email.validate("ab").getErrors() + " "
                + email.validate("abcde").getErrors() + " " + email.validate("a@bcd").isValid());
        try { Validator.<String>of(s -> true, ""); System.out.println("no exception"); }
        catch (IllegalArgumentException e) { System.out.println("IllegalArgumentException"); }

        System.out.println("== 2.2 or");
        Validator<String> phone = Validator.of(s -> s.startsWith("+389"), "must start with +389");
        Validator<String> contact = hasAt.or(phone);
        System.out.println(contact.validate("a@b").isValid());
        System.out.println(contact.validate("+38970123").isValid());
        System.out.println(contact.validate("abc").getErrors());
        try { hasAt.or(null); System.out.println("no exception"); }
        catch (IllegalArgumentException e) { System.out.println("IllegalArgumentException"); }

        System.out.println("== 1 merge");
        ValidationResult r1 = ValidationResult.of(Arrays.asList("a", "b"));
        ValidationResult r2 = ValidationResult.error("c");
        System.out.println(r1.merge(r2).getErrors());
        System.out.println(ValidationResult.ok().merge(ValidationResult.ok()).isValid());
        System.out.println(r1.getErrors() + " " + r2.getErrors());

        System.out.println("== 2.3 andAll");
        Validator<String> strictAnd = Validator.minLength(5).andAll(hasAt);
        Validator<String> normalAnd = Validator.minLength(5).and(hasAt);
        System.out.println(strictAnd.validate("ab").getErrors());
        System.out.println(normalAnd.validate("ab").getErrors());
        System.out.println(strictAnd.validate("abcdef").getErrors());
        System.out.println(strictAnd.validate("a@bcd").isValid());

        System.out.println("== 2.4 field");
        Validator<User> nameField = Validator.field("name", User::getName,
                Validator.<String>notNull().and(Validator.minLength(3)));
        System.out.println(nameField.validate(new User("Al", 30, "x")).getErrors());
        System.out.println(nameField.validate(new User(null, 30, "x")).getErrors());
        System.out.println(nameField.validate(new User("Ana", 30, "x")).isValid());

        System.out.println("== 2.5 / 2.6");
        List<String> names = Arrays.asList("Ana", "Al", null, "Marko", "Bo");
        Validator<String> nameRule = Validator.<String>notNull().and(Validator.minLength(3));
        System.out.println(Validator.filterValid(names, nameRule));
        System.out.println(Validator.countInvalid(names, nameRule));
        System.out.println(Validator.filterValid(Arrays.asList(5, 18, 120, 121, 40), Validator.range(18, 120)));
    }
}
```

Expected output:

```text
== 2.1 of
[must contain @]
true
true [must have at most 10 characters]
[must not be null] [must have at least 5 characters] [must contain @] true
IllegalArgumentException
== 2.2 or
true
true
[must contain @, must start with +389]
IllegalArgumentException
== 1 merge
[a, b, c]
true
[a, b] [c]
== 2.3 andAll
[must have at least 5 characters, must contain @]
[must have at least 5 characters]
[must contain @]
true
== 2.4 field
[name: must have at least 3 characters]
[name: must not be null]
true
== 2.5 / 2.6
[Ana, Marko]
3
[18, 120, 40]
```

- The `merge` line `[a, b] [c]` checks that the originals didn't change.
- The two `andAll` lines vs `and` show the difference: all errors vs only the first.
- For 3 (the new `UserValidation`), use the `USER` tests from `labs/lab2a/README.md` with the given `Lab2.main` harness.

---

# Extra (not covered in auds)

Only if there's time. These are common in validation APIs but not in Auds 2–3:

- `Validator<T>`: `default Validator<T> negate(String message)`: valid when the current validator fails, otherwise an error with `message`.
- `Validator<T>`: `static <T> Validator<T> allOf(List<Validator<? super T>> validators)`: combine any number of validators with `andAll` in a loop.
- `Predicate.not(...)` (Java 11): the negation of a predicate, handy inside `of(...)`, e.g. `Validator.of(Predicate.not(String::isBlank), "must not be blank")`.
