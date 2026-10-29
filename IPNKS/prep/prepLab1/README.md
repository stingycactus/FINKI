# IPNKS - Lab 1 prep

Three exercises on JavaScript basics: `prompt`, `parseInt`/`parseFloat`, `isNaN`, if/else, and loops or `%` and `Math.floor` for digit extraction.

Input/output format is assumed (the original statements didn't specify one). Each example shows what the user types into `prompt` and what the program prints with `document.write`.

---

## Exercise 1: Temperature conversion

Convert a temperature from Celsius to Fahrenheit and back. The formulas are given in the exercise:

```
F = C * 9/5 + 32
C = (F - 32) * 5/9
```

The user enters a number and the unit (`C` or `F`). The program prints the converted value. If the input is not a number, print an error message.

Use `parseFloat`, not `parseInt`, because temperatures can have decimals.

### Example 1

Input:
```
0
C
```
Output:
```
32 F
```

### Example 2

Input:
```
100
C
```
Output:
```
212 F
```

### Example 3

Input:
```
37
C
```
Output:
```
98.6 F
```

### Example 4

Input:
```
-40
C
```
Output:
```
-40 F
```

### Example 5

Input:
```
212
F
```
Output:
```
100 C
```

### Example 6

Input:
```
32
F
```
Output:
```
0 C
```

### Example 7 (invalid input)

Input:
```
abc
C
```
Output:
```
You have not entered a number!
```

---

## Exercise 2: Largest digit sum

Read three three-digit numbers and print the one with the largest sum of digits. If any of the entered numbers is not three digits (100 to 999), print an error message.

If two numbers have the same digit sum, print the first one.

### Example 1

Input:
```
123
456
789
```
Output:
```
789
```
Digit sums: 6, 15, 24.

### Example 2

Input:
```
100
999
555
```
Output:
```
999
```
Digit sums: 1, 27, 15.

### Example 3 (tie)

Input:
```
900
270
504
```
Output:
```
900
```
Digit sums: 9, 9, 9. The first one is printed.

### Example 4 (not three digits)

Input:
```
123
45
678
```
Output:
```
Error: 45 is not a three-digit number!
```

### Example 5 (four digits)

Input:
```
1000
200
300
```
Output:
```
Error: 1000 is not a three-digit number!
```

---

## Exercise 3: Four-digit palindrome and divisibility

Read a four-digit number and check two things:

1. Is it a palindrome (reads the same forwards and backwards)?
2. Is it divisible by the sum of its own digits?

Print the result for each check. If the number is not four digits (1000 to 9999), print an error message.

### Example 1: palindrome and divisible

Input:
```
2112
```
Output:
```
2112 is a palindrome.
2112 is divisible by the sum of its digits (6).
```

### Example 2: palindrome only

Input:
```
1221
```
Output:
```
1221 is a palindrome.
1221 is not divisible by the sum of its digits (6).
```

### Example 3: palindrome and divisible

Input:
```
4554
```
Output:
```
4554 is a palindrome.
4554 is divisible by the sum of its digits (18).
```

### Example 4: palindrome only

Input:
```
1001
```
Output:
```
1001 is a palindrome.
1001 is not divisible by the sum of its digits (2).
```

### Example 5: neither

Input:
```
1234
```
Output:
```
1234 is not a palindrome.
1234 is not divisible by the sum of its digits (10).
```

### Example 6: divisible only

Input:
```
1230
```
Output:
```
1230 is not a palindrome.
1230 is divisible by the sum of its digits (6).
```

### Example 7 (not four digits)

Input:
```
123
```
Output:
```
Error: 123 is not a four-digit number!
```

### Example 8 (not four digits)

Input:
```
12345
```
Output:
```
Error: 12345 is not a four-digit number!
```

---

## Hints

- Digit extraction: `n % 10` is the last digit, `Math.floor(n / 10)` removes it.
- Palindrome check for four digits: first digit equals last, second equals third.
- `prompt` returns a string (or `null` on Cancel), so convert with `parseInt`/`parseFloat` and validate with `isNaN`.
