# Aud 1: Object-oriented programming

Topics: abstract classes, interfaces, inheritance and polymorphism, refactoring type codes into subclasses, custom exceptions, reading from standard input.

Each task starts with the original text from the aud, with the wording unchanged and only the formatting cleaned up (solutions left out). Tasks 1 and 2 have no input format in the aud, so each comes with a small sample `main` (add `import java.util.Scanner;` at the top of the file) and test cases for it.

---

## Task 1: Bank (inheritance, polymorphism and interfaces)

### Original text

Given are the following five classes:

- `Bank`
- `Account`
- `NonInterestCheckingAccount`
- `InterestCheckingAccount`
- `PlatinumCheckingAccount`

as well as an interface called `InterestBearingAccount` which behave as follows:

- In **`Bank`** a list of all types of accounts is stored, including savings and checking accounts, some of which are subject to interest and some are not. In `Bank` there is a method `totalAssets` which returns the sum of the balance of all accounts. It also contains a method `addInterest` which calls the `addInterest` method on all accounts that are subject to interest.
- **`Account`** is an abstract class. Each account stores the name of the account holder, the account number (a sequential number assigned automatically), and the current balance. The class implements a constructor for initializing the data members, methods for accessing the current balance, as well as for adding and subtracting from the current balance.
- The **`InterestBearingAccount`** interface declares a single method `addInterest` (without parameters and returns nothing - `void`) which increases the balance with the appropriate interest rate for this type of account.
- **`InterestCheckingAccount`** is an `Account` which is also an `InterestBearingAccount`. Calling `addInterest` increases the balance by 3%.
- **`PlatinumCheckingAccount`** is an `InterestCheckingAccount`. Calling `addInterest` increases the balance by double the interest rate for `InterestCheckingAccount` (whatever that may be).
- **`NonInterestCheckingAccount`** is an `Account` but not an `InterestBearingAccount`. It has no additional functionalities beyond the basic ones from the class `Account`.

### Sample main

Input: the bank's starting capacity, the number of accounts `N`, then `N` lines of `TYPE NAME BALANCE`, where `TYPE` is `N` (non-interest), `I` (interest) or `P` (platinum). It assumes account constructors take `(name, balance)` and assign the number automatically.

```java
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Bank bank = new Bank(sc.nextInt());
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            String type = sc.next();
            String name = sc.next();
            double balance = sc.nextDouble();
            if (type.equals("N")) bank.addAccount(new NonInterestCheckingAccount(name, balance));
            else if (type.equals("I")) bank.addAccount(new InterestCheckingAccount(name, balance));
            else bank.addAccount(new PlatinumCheckingAccount(name, balance));
        }
        System.out.printf("Total assets: %.2f%n", bank.totalAssets());
        bank.addInterest();
        System.out.printf("After interest: %.2f%n", bank.totalAssets());
        bank.addInterest();
        System.out.printf("After interest: %.2f%n", bank.totalAssets());
    }
}
```

### Test cases

**Test 1: one of each**

INPUT
```text
10
3
N Ana 1000
I Bob 1000
P Cleo 1000
```
OUTPUT
```text
Total assets: 3000.00
After interest: 3090.00
After interest: 3184.50
```

**Test 2: the bank has to grow** (capacity 2, five accounts, so it grows twice)

INPUT
```text
2
5
N Ana 1000
I Bob 1000
P Cleo 1000
N Dan 500
I Eli 200
```
OUTPUT
```text
Total assets: 3700.00
After interest: 3796.00
After interest: 3896.68
```

### Easy to miss

- `PlatinumCheckingAccount` extends `InterestCheckingAccount`, not `Account`.
- Platinum's rate is "double the `InterestCheckingAccount` rate". Use that class's constant times 2, not a hardcoded 6%.
- Loops in `Bank` must stop at the number of accounts added, not the array length. Unused slots are `null`.

---

## Task 2: Inheritance (refactoring)

### Original text

The following code was designed by J. Hacker for a video game. There is a class `Alien` that represents an alien and a class `AlienPack` that represents a group of aliens and how much damage they can inflict:

```java
class Alien {
    public static final int SNAKE_ALIEN = 0;
    public static final int OGRE_ALIEN = 1;
    public static final int MARSHMALLOW_MAN_ALIEN = 2;
    public int type; // Stores one of the three above types
    public int health; // 0=dead, 100=full strength
    public String name;

    public Alien(int type, int health, String name) {
        this.type = type;
        this.health = health;
        this.name = name;
    }
}

class AlienPack {
    private Alien[] aliens;

    public AlienPack(int numAliens) {
        aliens = new Alien[numAliens];
    }

    public void addAlien(Alien newAlien, int index) {
        aliens[index] = newAlien;
    }

    public Alien[] getAliens() {
        return aliens;
    }

    public int calculateDamage() {
        int damage = 0;
        for (int i = 0; i < aliens.length; i++) {
            if (aliens[i].type == Alien.SNAKE_ALIEN) {
                damage += 10;// Snake does 10 damage
            } else if (aliens[i].type == Alien.OGRE_ALIEN) {
                damage += 6;// Ogre does 6 damage
            } else if (aliens[i].type == Alien.MARSHMALLOW_MAN_ALIEN) {
                damage += 1;
                // Marshmallow Man does 1 damage
            }
        }
        return damage;
    }
}
```

The code is not very object-oriented and does not support encapsulation in the `Alien` class. It should be rewritten so that inheritance is used to represent different types of aliens instead of using the `type` parameter. Also, rewrite the `Alien` class so that it hides the instance variables and add a method `getDamage` which, for each of the derived classes, will return the amount of damage it causes. Finally, rewrite the `calculateDamage` method to use `getDamage` and write a `main` method to test the class.

(The code above is the starting code you refactor, not a solution.)

### Sample main

Input: the pack size, the number of aliens `N`, then `N` lines of `TYPE NAME HEALTH INDEX`, where `TYPE` is `S` (snake), `O` (ogre) or `M` (marshmallow man). It assumes the subclass constructors take `(health, name)`.

```java
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        AlienPack pack = new AlienPack(sc.nextInt());
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            String type = sc.next();
            String name = sc.next();
            int health = sc.nextInt();
            int index = sc.nextInt();
            if (type.equals("S")) pack.addAlien(new SnakeAlien(health, name), index);
            else if (type.equals("O")) pack.addAlien(new OgreAlien(health, name), index);
            else pack.addAlien(new MarshmallowManAlien(health, name), index);
        }
        System.out.println("Total damage: " + pack.calculateDamage());
    }
}
```

### Test cases

**Test 1: one of each**

INPUT
```text
3
3
S Sid 100 0
O Olga 80 1
M Max 50 2
```
OUTPUT
```text
Total damage: 17
```

**Test 2: an empty slot** (pack of 4, index 2 left empty)

INPUT
```text
4
3
S Sid 100 0
S Sam 100 1
O Olga 80 3
```
OUTPUT
```text
Total damage: 26
```

### Easy to miss

- The `type` field and the three constants disappear completely.
- `addAlien` puts aliens at an index, so the array can have empty (`null`) slots. `calculateDamage()` must skip them.
- Adding a fourth alien type should only need a new subclass. `AlienPack` shouldn't change.

---

## Task 3: Reading from standard input (SI): 3.1 Calculator

### Original text

Write a program — a simple calculator.
The calculator stores a single number of type `double` named `result`, whose initial value is `0.0`.
In a loop, the user is allowed to:

- add (`+`)
- subtract (`-`)
- multiply (`*`)
- divide (`/`)

with a second number.
The result of these operations becomes the new value of `result`.
Calculations end when the user enters `R` (uppercase or lowercase) for result.
Then the user can start a new calculation from the beginning or end the program (Y/N).

If the user enters an operator other than `+`, `-`, `*`, or `/`, then an exception `UnknownOperatorException` is thrown, and a new input is requested.

**Requirements that the text forgot to mention** (taken from the sample run below):

- Print `Calculator is on.` once when the program starts, not for every new calculation.
- When a calculation starts, print `result = 0.0`.
- After each valid line, print `result OP VALUE = RESULT`, then `new result = RESULT` for the first operation of a calculation and `updated result = RESULT` for later ones.
- For an unknown operator, print `OP is an unknown operation.` (with the actual operator), then `Reenter, your last line:`. The result doesn't change and isn't printed.
- On `r`/`R`, print `Final result = RESULT`, then `Again? (y/n)`.
- If the answer starts with `n`/`N`, print `End of Program`. If it starts with `y`/`Y`, start a new calculation from `result = 0.0`.
- Print numbers the way Java prints a `double` normally (`5.0`, `11.0`, `1.1`), not with `%f` or `%.2f`.
- The space between the operator and the number is optional: both `+5` and `* 2.2` are valid.
- `r`/`R` and `y`/`n` are case-insensitive, and only the first letter of the answer counts (`yes` = `y`).

Example of input data format:

```text
Calculator is on.
result = 0.0
+5
result + 5.0 = 5.0
new result = 5.0
* 2.2
result * 2.2 = 11.0
updated result = 11.0
% 10
% is an unknown operation.
Reenter, your last line:
* 0.1
result * 0.1 = 1.1
updated result = 1.1
r
Final result = 1.1
Again? (y/n)
yes
result = 0.0
+10
result + 10.0 = 10.0
new result = 10.0
/2
result / 2.0 = 5.0
updated result = 5.0
r
Final result = 5.0
Again? (y/n)
N
End of Program
```

### Test cases

**Test 1: the sample above, split into input and output**

INPUT
```text
+5
* 2.2
% 10
* 0.1
r
yes
+10
/2
r
N
```
OUTPUT
```text
Calculator is on.
result = 0.0
result + 5.0 = 5.0
new result = 5.0
result * 2.2 = 11.0
updated result = 11.0
% is an unknown operation.
Reenter, your last line:
result * 0.1 = 1.1
updated result = 1.1
Final result = 1.1
Again? (y/n)
result = 0.0
result + 10.0 = 10.0
new result = 10.0
result / 2.0 = 5.0
updated result = 5.0
Final result = 5.0
Again? (y/n)
End of Program
```

**Test 2: subtraction, a bad operator in the middle, uppercase R**

INPUT
```text
-3
x 4
* 2
/ 4
R
n
```
OUTPUT
```text
Calculator is on.
result = 0.0
result - 3.0 = -3.0
new result = -3.0
x is an unknown operation.
Reenter, your last line:
result * 2.0 = -6.0
updated result = -6.0
result / 4.0 = -1.5
updated result = -1.5
Final result = -1.5
Again? (y/n)
End of Program
```

### Easy to miss

- Parse the operator as the first character and the number as the rest of the line. Splitting on spaces fails for `+5`.
- Only the first letter of the Y/N answer matters (`yes` counts as `y`).
- After an unknown operator, the result stays unchanged and the loop continues.
- `UnknownOperatorException` is a checked exception (extends `Exception`), so the method that throws it must declare `throws`.
