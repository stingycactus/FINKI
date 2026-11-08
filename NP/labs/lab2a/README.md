# Lab 2, Part A: Generics and Functional Interfaces

Implement a simple data validation system using generics, functional interfaces, and lambda expressions.

A validator checks whether a value satisfies a particular condition. The validation result indicates whether the value is valid and, if it is not, contains error messages. Validators should be combinable to check multiple conditions.

---

## 1. Class `ValidationResult`

Implement an immutable class representing a validation result and storing its error messages.

**Required methods:**

- `public static ValidationResult ok()` – returns a successful result with no errors.
- `public static ValidationResult error(String message)` – returns a result containing one error. If `message` is `null` or an empty string, throw `IllegalArgumentException`.
- `public static ValidationResult of(List<String> errors)` – returns a result containing the specified errors. An empty list means successful validation. If `errors` is `null`, throw `IllegalArgumentException`.
- `public boolean isValid()` – returns `true` if there are no errors, otherwise `false`.
- `public List<String> getErrors()` – returns the errors in the order they were added; returns an empty list for successful validation.

The `of` method must copy the supplied list so that later changes to the original list do not affect the result. The list returned by `getErrors()` must be unmodifiable: attempting to modify it must throw `UnsupportedOperationException`.

## 2. Interface `Validator<T>`

Define a generic functional interface `Validator<T>`, annotated with `@FunctionalInterface`, with one abstract method:

```java
ValidationResult validate(T value);
```

The interface must also provide the following methods:

### `default Validator<T> and(Validator<? super T> other)`

Returns a new validator that applies two validators to the same value in sequence:

1. First, execute the current validator.
2. If the first validation fails, return its result immediately without calling `other`.
3. If the first validation succeeds, execute `other` and return its result.

If `other` is `null`, throw `IllegalArgumentException`.

### `static <T> Validator<T> notNull()`

Returns a validator that produces the error `must not be null` for a `null` value. Any non-null value is valid.

### `static Validator<String> minLength(int min)`

Returns a validator that checks whether a string has at least `min` characters.

- If the value is `null`: `must not be null`.
- If the string is shorter than `min`: `must have at least <min> characters` (replace `<min>` with the actual minimum).
- Otherwise, validation succeeds.
- If `min < 0`, throw `IllegalArgumentException` when the validator is created.

### `static Validator<Integer> range(int min, int max)`

Returns a validator that checks whether an integer is between `min` and `max`, including both bounds.

- If the value is `null`: `must not be null`.
- If it is outside the interval: `must be between <min> and <max>` (replace the placeholders with the actual bounds).
- Otherwise, validation succeeds.
- If `min > max`, throw `IllegalArgumentException` when the validator is created.

## 3. Class `User`

Implement a `User` class with these fields:

- `String name`
- `Integer age`
- `String email`

Provide the constructor:

```java
public User(String name, Integer age, String email)
```

and the methods `getName()`, `getAge()`, and `getEmail()`.

All fields may contain `null` values. Do not validate values in the constructor: the `UserValidation` class will handle validation.

## 4. Class `UserValidation`

Implement a `UserValidation` class with the following static method:

```java
public static ValidationResult validate(User user)
```

The method must validate the user's three fields according to the following rules, in the specified order:

- `name` – first check that it is not `null`, then that it contains at least 3 characters.
- `age` – first check that it is not `null`, then that it is between 18 and 120 (inclusive).
- `email` – first check that it is not `null`, then that it contains at least 5 characters, and finally that it contains the `@` character. Define the last check using a lambda expression; when it fails, return the error `must contain @`.

**Note:**

- Use the appropriate validators from `Validator<T>` for each field and combine them with `and`. This ensures that only the first error for each field is reported. For example, if `email` has only two characters and does not contain `@`, report the length error, not the `@` error as well.
- Validate all three fields, even if an earlier field is invalid. Collect their errors in the order `name`, `age`, `email`.
- Prefix every error with the field name followed by `:`, for example `name: must not be null` or `email: must contain @`.
- If all fields are valid, return a successful result without errors.
- If `user` is `null`, throw `IllegalArgumentException`.

## Exceptions and Edge Cases

All cases that throw an exception, in one place:

| Situation | Exception |
|---|---|
| `ValidationResult.error(message)` — `message` is `null` or an empty string | `IllegalArgumentException` |
| `ValidationResult.of(errors)` — `errors` is `null` | `IllegalArgumentException` |
| Trying to modify (`add`, `remove`, `set`, `clear`...) the list returned by `getErrors()`, for every result (from `ok()`, `error(...)`, `of(...)`, or returned by a validator) | `UnsupportedOperationException` |
| `and(other)` — `other` is `null` | `IllegalArgumentException` |
| `Validator.minLength(min)` — `min < 0` (when the validator is created) | `IllegalArgumentException` |
| `Validator.range(min, max)` — `min > max` (when the validator is created) | `IllegalArgumentException` |
| `UserValidation.validate(user)` — `user` is `null` | `IllegalArgumentException` |

In all other cases no exception is thrown:

- Validating a `null` value (with `notNull()`, `minLength` or `range`) does not throw; it returns a result with the error `must not be null`.
- `minLength(0)` and `range(min, max)` with `min == max` are allowed. The bounds of `range` may also be negative numbers.
- The `User` constructor does not throw (all values may be `null`). `UserValidation.validate` does not throw for a `null` field; it reports an error.

## Usage Example

```java
Validator<String> name = Validator.<String>notNull()
        .and(Validator.minLength(3));

System.out.println(name.validate("Ana").isValid());
System.out.println(name.validate("Al").getErrors());
System.out.println(name.validate(null).getErrors());

Validator<Integer> age = Validator.range(18, 120);
System.out.println(age.validate(17).getErrors());

ValidationResult result = UserValidation.validate(
        new User("Al", 17, "al")
);

System.out.println(result.isValid());
System.out.println(result.getErrors());
```

Expected output:

```text
true
[must have at least 3 characters]
[must not be null]
[must be between 18 and 120]
false
[name: must have at least 3 characters, age: must be between 18 and 120, email: must have at least 5 characters]
```

---

# Test cases

Inputs for the given `Lab2.main` harness (use IntelliJ's Redirect input). Commands: `VAL <name> <STR|INT> <chain>` defines a validator (atoms joined with `>` = `.and(next)`), `CHECK <name> <value>` validates a value, `NULL` means `null`, `EMPTY` means `""`.

### Test 1: Validators: notNull, minLength, range and chains

INPUT
```text
VAL N STR NOTNULL>MINLEN:3
CHECK N Ana
CHECK N Al
CHECK N NULL
VAL M STR MINLEN:3
CHECK M NULL
CHECK M abc
VAL Z STR MINLEN:0
CHECK Z NULL
CHECK Z x
VAL A INT RANGE:18:120
CHECK A 17
CHECK A 18
CHECK A 120
CHECK A 121
CHECK A NULL
VAL P INT NOTNULL
CHECK P NULL
CHECK P 5
VAL I INT NOTNULL>RANGE:1:10
CHECK I NULL
CHECK I 0
CHECK I 10
VAL S INT RANGE:-5:-1
CHECK S -3
CHECK S 0
END
```
EXPECTED
```text
Defined N (STR)
Valid
Invalid: [must have at least 3 characters]
Invalid: [must not be null]
Defined M (STR)
Invalid: [must not be null]
Valid
Defined Z (STR)
Invalid: [must not be null]
Valid
Defined A (INT)
Invalid: [must be between 18 and 120]
Valid
Valid
Invalid: [must be between 18 and 120]
Invalid: [must not be null]
Defined P (INT)
Invalid: [must not be null]
Valid
Defined I (INT)
Invalid: [must not be null]
Invalid: [must be between 1 and 10]
Valid
Defined S (INT)
Valid
Invalid: [must be between -5 and -1]
```

### Test 2: Exceptions when creating validators, and and(null)

INPUT
```text
VAL N STR NOTNULL
VAL X STR MINLEN:-1
CHECK X abc
VAL X INT RANGE:5:3
CHECK X 5
VAL X INT RANGE:5:5
CHECK X 5
CHECK X 6
CHECK X 4
VAL Y STR MINLEN:0
AND_NULL N
AND_NULL Y
END
```
EXPECTED
```text
Defined N (STR)
IllegalArgumentException
No validator X
IllegalArgumentException
No validator X
Defined X (INT)
Valid
Invalid: [must be between 5 and 5]
Invalid: [must be between 5 and 5]
Defined Y (STR)
IllegalArgumentException
IllegalArgumentException
```

### Test 3: Lambda check (HASAT), Validator<Object> in and, chain order

INPUT
```text
VAL E STR NOTNULL>HASAT
CHECK E NULL
CHECK E abc
CHECK E a@b
VAL F STR MINLEN:3>OBJNOTNULL
CHECK F ab
CHECK F NULL
CHECK F abc
VAL G STR NOTNULL>MINLEN:5>HASAT
CHECK G NULL
CHECK G ab
CHECK G abcde
CHECK G ab@cde
VAL H STR HASAT>MINLEN:5
CHECK H a@
CHECK H abcdef
CHECK H a@bcd
END
```
EXPECTED
```text
Defined E (STR)
Invalid: [must not be null]
Invalid: [must contain @]
Valid
Defined F (STR)
Invalid: [must have at least 3 characters]
Invalid: [must not be null]
Valid
Defined G (STR)
Invalid: [must not be null]
Invalid: [must have at least 5 characters]
Invalid: [must contain @]
Valid
Defined H (STR)
Invalid: [must have at least 5 characters]
Invalid: [must contain @]
Valid
```

### Test 4: ValidationResult: ok, error, of, copies and unmodifiable lists

INPUT
```text
RESULT_OK
RESULT_ERROR boom
RESULT_ERROR NULL
RESULT_ERROR EMPTY
RESULT_OF -
RESULT_OF a
RESULT_OF a,b,c
RESULT_OF_COPY a,b
RESULT_OF_COPY -
RESULT_OF_MODIFY a,b
RESULT_OF_MODIFY -
RESULT_OF_NULL
RESULT_OK_MODIFY
RESULT_ERROR_MODIFY boom
VAL V INT RANGE:1:5
MODIFY V 9
MODIFY V 3
END
```
EXPECTED
```text
ok: Valid
error: Invalid: [boom]
IllegalArgumentException
IllegalArgumentException
of: Valid
of: Invalid: [a]
of: Invalid: [a, b, c]
after change: Invalid: [a, b]
after change: Valid
UnsupportedOperationException
UnsupportedOperationException
IllegalArgumentException
UnsupportedOperationException
UnsupportedOperationException
Defined V (INT)
UnsupportedOperationException
UnsupportedOperationException
```

### Test 5: UserValidation

INPUT
```text
USER Ana 30 ana@mail.com
USER Al 17 al
USER NULL NULL NULL
USER Ana NULL a@b.c
USER Ana 18 abc
USER Ana 120 abcde
USER Ana 121 a@b.c
USER A 17 abcde
USER NULL 25 x@y.mk
USER Ana 25 ab@
USER Ana 25 a@bcd
END
```
EXPECTED
```text
Valid
Invalid: [name: must have at least 3 characters, age: must be between 18 and 120, email: must have at least 5 characters]
Invalid: [name: must not be null, age: must not be null, email: must not be null]
Invalid: [age: must not be null]
Invalid: [email: must have at least 5 characters]
Invalid: [email: must contain @]
Invalid: [age: must be between 18 and 120]
Invalid: [name: must have at least 3 characters, age: must be between 18 and 120, email: must contain @]
Invalid: [name: must not be null]
Invalid: [email: must have at least 5 characters]
Valid
```

### Test 6: UserValidation: boundaries and null user

INPUT
```text
USER Ana 18 a@b.c
USER Ana 120 a@b.c
USER Ana 17 a@b.c
USER Ana 121 a@b.c
USER Ab 18 a@b.c
USER Abc 18 abcd
USER Abc 18 abcde
USER Abc 18 a@bcd
USER Abcdefghij 50 first.last@example.mk
USER_NULL
END
```
EXPECTED
```text
Valid
Valid
Invalid: [age: must be between 18 and 120]
Invalid: [age: must be between 18 and 120]
Invalid: [name: must have at least 3 characters]
Invalid: [email: must have at least 5 characters]
Invalid: [email: must contain @]
Valid
Valid
IllegalArgumentException
```
