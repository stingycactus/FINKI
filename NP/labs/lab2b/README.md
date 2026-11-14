# Lab 2, Part B: Generics and Functional Interfaces

In this part, you will extend the validation system implemented in Part A.

The goal is to support validation of individual object fields and combining multiple validators, allowing all validation rules to be checked and their errors to be collected.

Use generics, functional interfaces, and lambda expressions to implement the requirements.

**Important:** Continue working on your Part A solution. All existing functionality must preserve its original behavior.

## 1. Extending the `Validator<T>` Interface

Add the following two static methods to the existing `Validator<T>` interface.

### 1.1. Method `field`

```java
static <T, F> Validator<T> field(
    String name,
    Function<? super T, ? extends F> getter,
    Validator<? super F> validator
)
```

This method creates a validator for objects of type `T` that validates a specific field of the object.

- `name` – the name of the field being validated.
- `getter` – a function that extracts the field value from the object.
- `validator` – a validator applied to the extracted value.

When validation is performed:

1. Use `getter` to obtain the field value.
2. Validate the extracted value using `validator`.
3. If validation succeeds, return the result unchanged.
4. If validation fails, prefix every error message with the field name using the format `<name>: <error>`.

If any of the arguments `name`, `getter`, or `validator` is `null`, throw `IllegalArgumentException`.

Example:

```java
Validator<User> byName = Validator.field(
    "name",
    User::getName,
    Validator.minLength(3)
);

System.out.println(
    byName.validate(new User("Al", 30, "a@b.c")).getErrors()
);
```

Expected output:

```text
[name: must have at least 3 characters]
```

### 1.2. Method `allOf`

```java
static <T> Validator<T> allOf(
    List<? extends Validator<? super T>> validators
)
```

This method creates a new validator by combining multiple validators.

The resulting validator must:

- Execute all validators in the order they appear in the list.
- Collect all error messages produced by the validators.
- Preserve the order of the errors.
- Return a successful result if no errors are found.

Unlike the `and` method from Part A, which stops after the first failed validation, `allOf` must execute every validator, regardless of the results of previous validations.

Additional rules:

- If the list is empty, the resulting validator must always return a successful result.
- If the list is `null` or contains a `null` element, throw `IllegalArgumentException`.
- Modifying the original list after creating the validator must not affect its behavior.

Example:

```java
Validator<User> byName = Validator.field(
    "name",
    User::getName,
    Validator.minLength(3)
);

Validator<User> byAge = Validator.field(
    "age",
    User::getAge,
    Validator.range(18, 120)
);

Validator<User> both = Validator.allOf(
    List.of(byName, byAge)
);

System.out.println(
    both.validate(new User("Al", 17, "al")).getErrors()
);
```

Expected output:

```text
[name: must have at least 3 characters, age: must be between 18 and 120]
```

## 2. Extending the `UserValidation` Class

Add the following static method to the existing `UserValidation` class:

```java
public static Validator<User> userValidator()
```

The method must return a validator for `User` objects, built using the new `field` and `allOf` methods.

The validator must apply the same validation rules from Part A:

| Field | Validation Rule |
|---|---|
| `name` | Must not be null and must contain at least 3 characters |
| `age` | Must not be null and must be between 18 and 120 |
| `email` | Must not be null, must contain at least 5 characters, and must contain the `@` character |

Only the first validation error should be reported for each field, while errors from different fields must be collected in the order `name`, `age`, `email`.

The `userValidator()` method must produce exactly the same validation results and error order as the existing `UserValidation.validate(User user)` method.

Example:

```java
User user = new User("Al", 17, "al");

System.out.println(
    UserValidation.userValidator().validate(user).getErrors()
);
```

Expected output:

```text
[name: must have at least 3 characters, age: must be between 18 and 120, email: must have at least 5 characters]
```

## 3. Using Generic Types

You must use the specified generic method signatures, including `? super` and `? extends`.

Your implementation must allow a validator for a more general type to be used when validating values of a more specific type.

For example, the following code must compile and execute correctly:

```java
Validator<Object> notNullObject = Validator.notNull();

Validator<String> text = Validator.minLength(3)
        .and(notNullObject);

System.out.println(text.validate("ab").getErrors());
```

Expected output:

```text
[must have at least 3 characters]
```

---

# Test cases

### Test 1

INPUT
```text
VAL R INT RANGE:2:5
FIELD_LENGTH len R ab
FIELD_LENGTH len R a
FIELD_LENGTH len R abcde
FIELD_LENGTH len R abcdef
VAL N INT NOTNULL
FIELD_LENGTH size N hello
FIELD_OBJ objlen R abc
FIELD_OBJ objlen R abcdefgh
FIELD_OBJVAL anything hello
VAL M STR MINLEN:3
FIELD_DEF F1 name M
CHECK F1 Al
CHECK F1 Ana
CHECK F1 NULL
END
```
EXPECTED
```text
Defined R (INT)
Valid
Invalid: [len: must be between 2 and 5]
Valid
Invalid: [len: must be between 2 and 5]
Defined N (INT)
Valid
Valid
Invalid: [objlen: must be between 2 and 5]
Valid
Defined M (STR)
Defined F1 (STR)
Invalid: [name: must have at least 3 characters]
Valid
Invalid: [name: must not be null]
```

### Test 2

INPUT
```text
FIELD_NULL NAME
VAL R INT RANGE:1:10
FIELD_NULL NAME
FIELD_NULL GETTER
FIELD_NULL VALIDATOR
FIELD_LENGTH ok R abc
END
```
EXPECTED
```text
No validator R
Defined R (INT)
IllegalArgumentException
IllegalArgumentException
IllegalArgumentException
Valid
```

### Test 3

INPUT
```text
VAL N STR NOTNULL>MINLEN:3
VAL L STR MINLEN:5
VAL H STR NOTNULL>HASAT
ALLOF A1 STR N,L,H
CHECK A1 ab
CHECK A1 abcdef
CHECK A1 abc@d
CHECK A1 abcde@
CHECK A1 NULL
ALLOF A2 STR L,N
CHECK A2 ab
ALLOF EMPTY STR -
CHECK EMPTY NULL
CHECK EMPTY abc
ALLOF O STR N,OBJNOTNULL
CHECK O ab
CHECK O NULL
ALLOF NEST STR A1,A2
CHECK NEST ab
END
```
EXPECTED
```text
Defined N (STR)
Defined L (STR)
Defined H (STR)
Defined A1 (STR)
Invalid: [must have at least 3 characters, must have at least 5 characters, must contain @]
Invalid: [must contain @]
Valid
Valid
Invalid: [must not be null, must not be null, must not be null]
Defined A2 (STR)
Invalid: [must have at least 5 characters, must have at least 3 characters]
Defined EMPTY (STR)
Valid
Valid
Defined O (STR)
Invalid: [must have at least 3 characters]
Invalid: [must not be null, must not be null]
Defined NEST (STR)
Invalid: [must have at least 3 characters, must have at least 5 characters, must contain @, must have at least 5 characters, must have at least 3 characters]
```

### Test 4

INPUT
```text
VAL N STR NOTNULL>MINLEN:3
VAL L STR MINLEN:5
ALLOF_NULL
ALLOF_NULL_ELEM N
ALLOF_COPY N,L ab
ALLOF_COPY N,L abcdef
ALLOF_COPY N,L NULL
END
```
EXPECTED
```text
Defined N (STR)
Defined L (STR)
IllegalArgumentException
IllegalArgumentException
Invalid: [must have at least 3 characters, must have at least 5 characters]
Valid
Invalid: [must not be null, must not be null]
```

### Test 5

INPUT
```text
VAL N STR NOTNULL>MINLEN:3
VAL L STR MINLEN:5
ALLOF X STR N,L
FIELD_DEF F1 first N
FIELD_DEF F2 second L
ALLOF Y STR F1,F2
CHECK Y ab
CHECK Y abcdef
CHECK Y NULL
FIELD_DEF OUTER outer X
CHECK OUTER ab
CHECK OUTER abcdef
FIELD_DEF O2 o2 Y
CHECK O2 ab
END
```
EXPECTED
```text
Defined N (STR)
Defined L (STR)
Defined X (STR)
Defined F1 (STR)
Defined F2 (STR)
Defined Y (STR)
Invalid: [first: must have at least 3 characters, second: must have at least 5 characters]
Valid
Invalid: [first: must not be null, second: must not be null]
Defined OUTER (STR)
Invalid: [outer: must have at least 3 characters, outer: must have at least 5 characters]
Valid
Defined O2 (STR)
Invalid: [o2: first: must have at least 3 characters, o2: second: must have at least 5 characters]
```

### Test 6

INPUT
```text
USER2 Ana 30 ana@mail.com
USER2 Al 17 al
USER2 NULL NULL NULL
USER2 Ana NULL a@b.c
USER2 Ana 18 abc
USER2 Ana 120 abcde
USER2 Ana 121 a@b.c
USER_SAME Ana 30 ana@mail.com
USER_SAME Al 17 al
USER_SAME NULL NULL NULL
USER_SAME Ana 18 abc
USER_SAME Ana 120 abcde
USER_SAME A 17 a@b.c
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
Same: true
Same: true
Same: true
Same: true
Same: true
Same: true
```

### Test 7

INPUT
```text
VAL N STR NOTNULL>MINLEN:3
CHECK N Al
VAL F STR MINLEN:3>OBJNOTNULL
CHECK F NULL
AND_NULL N
MODIFY N Al
VAL X STR MINLEN:-1
VAL X INT RANGE:5:3
RESULT_OF_COPY a,b
RESULT_OF_NULL
RESULT_ERROR EMPTY
USER Al 17 al
USER_NULL
USER2 Al 17 al
USER_SAME Ana 25 x@y.mk
END
```
EXPECTED
```text
Defined N (STR)
Invalid: [must have at least 3 characters]
Defined F (STR)
Invalid: [must not be null]
IllegalArgumentException
UnsupportedOperationException
IllegalArgumentException
IllegalArgumentException
after change: Invalid: [a, b]
IllegalArgumentException
IllegalArgumentException
Invalid: [name: must have at least 3 characters, age: must be between 18 and 120, email: must have at least 5 characters]
IllegalArgumentException
Invalid: [name: must have at least 3 characters, age: must be between 18 and 120, email: must have at least 5 characters]
Same: true
```
