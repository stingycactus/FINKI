import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;

// ===================== Part A: your classes =====================
//
// Write ValidationResult, Validator, User and UserValidation here.

/*
TODO: your Part A code here
*/

final class ValidationResult {

    private List<String> errors;

    public ValidationResult(String message) {
        this.errors = new ArrayList<String>();
        this.errors.add(message);
    }

    public ValidationResult(List<String> errors) {
        this.errors = new ArrayList<String>(errors);
    }

    public ValidationResult() {
        this.errors = new ArrayList<String>();
    }

    public static ValidationResult ok() {
        return new ValidationResult();
    }
    public static ValidationResult error(String message) {
        if (message == null || message.isBlank()) {
            throw new IllegalArgumentException();
        }
        return new ValidationResult(message);
    }
    public static ValidationResult of(List<String> errors) {
        if (errors == null) {
            throw new IllegalArgumentException();
        }
        return new ValidationResult(errors);
    }

    public boolean isValid() {
        if (errors.isEmpty()) {
            return true;
        }
        return false;
    }

    public List<String> getErrors() {
        return Collections.unmodifiableList(errors);
    }

    public ValidationResult merge(ValidationResult other) {
        if (other == null) {
            throw new IllegalArgumentException();
        }
        List<String> combined = new ArrayList<>(errors);
        combined.addAll(other.getErrors());
        return ValidationResult.of(combined);
    }

}

@FunctionalInterface
interface Validator<T> {
    ValidationResult validate(T value);
    default Validator<T> and(Validator<? super T> other) {
        if (other == null) {
            throw new IllegalArgumentException();
        }
        return v -> {
            if (this.validate(v).isValid()) {
                return other.validate(v);
            }
            return this.validate(v);
        };
    }

    default Validator<T> or(Validator<? super T> other) {
        if (other == null) {
            throw new IllegalArgumentException();
        }
        return v -> {
            if (this.validate(v).isValid()) {
                return this.validate(v);
            } else if (other.validate(v).isValid()) {
                return other.validate(v);
            }
            return this.validate(v).merge(other.validate(v));
        };
    }

    default Validator<T> andAll(Validator<? super T> other) {
        if (other == null) {
            throw new IllegalArgumentException();
        }
        return v -> this.validate(v).merge(other.validate(v));
    }



    static <T, R> Validator<T> field(String name, Function<? super T, ? extends R> getter, Validator<? super R> validator) {
        if (name == null || getter == null || validator == null) {
            throw new IllegalArgumentException();
        }
        return v -> {
            R value = getter.apply(v);
            ValidationResult result = validator.validate(value);
            if (result.isValid()) {
                return ValidationResult.ok();
            }
            List<String> errors = new ArrayList<>();
            for (String error : result.getErrors()) {
                errors.add(String.format("%s: %s", name, error));
            }
            return ValidationResult.of(errors);
        };
    }

    static <T> List<T> filterValid(List<T> items, Validator<? super T> validator) {
        return items.stream().filter(v -> validator.validate(v).isValid()).collect(Collectors.toList());
    }

    static <T> long countInvalid(List<T> items, Validator<? super T> validator) {
        return items.stream().filter(v -> !(validator.validate(v).isValid())).count();
    }

    static <T> Validator<T> notNull() {
        return v -> {
            if (v == null) {
                return ValidationResult.error("must not be null");
            }
            return ValidationResult.ok();
        };
    }
    static Validator<String> minLength(int min) {
        if (min < 0) {
            throw new IllegalArgumentException();
        }
        return v -> {
            if (v == null) {
                return ValidationResult.error("must not be null");
            }
            return v.length() < min ? ValidationResult.error(String.format("must have at least %d characters", min)) : ValidationResult.ok();
        };
    }

    static Validator<Integer> range(int min, int max) {
        if (min > max) {
            throw new IllegalArgumentException();
        }
        return v -> {
            if (v == null) {
                return ValidationResult.error("must not be null");
            }
            if (min > v || max < v) {
                return ValidationResult.error(String.format("must be between %d and %d", min, max));
            }
            return ValidationResult.ok();
        };
    }

    static <T> Validator<T> of(Predicate<? super T> condition, String message) {v
        if (condition == null || message == null || message.isEmpty()) {
            throw new IllegalArgumentException();
        }
        return v -> condition.test(v) ? ValidationResult.ok() : ValidationResult.error(message);
    }
}

class User {
    private String name;
    private Integer age;
    private String email;

    public User(String name, Integer age, String email) {
        this.name = name;
        this.age = age;
        this.email = email;
    }

    public String getName() {
        return name;
    }

    public Integer getAge() {
        return age;
    }

    public String getEmail() {
        return email;
    }
}

class UserValidation {
    public static ValidationResult validate(User user) {
        if (user == null) {
            throw new IllegalArgumentException();
        }

        Validator<String> nameRule = Validator.<String>notNull().and(Validator.minLength(3));

        Validator<Integer> ageRule = Validator.<Integer>notNull().and(Validator.range(18, 120));

        Validator<String> emailRule = Validator.<String>notNull().and(Validator.minLength(5)).and(Validator.of(s -> s.contains("@"), "must contain @"));

        ValidationResult nameResult = Validator.field("name", User::getName, nameRule).validate(user);
        ValidationResult ageResult   = Validator.field("age", User::getAge, ageRule).validate(user);
        ValidationResult emailResult = Validator.field("email", User::getEmail, emailRule).validate(user);

        // merge = combine the errors, in order name, age, email
        return nameResult.merge(ageResult).merge(emailResult);
    }
}


// ===================== Test harness (do not modify) =====================
//
// Reads commands from standard input (one per line) and calls your classes.
// Validators have a name (e.g. V) and a type: STR (Validator<String>) or INT (Validator<Integer>).
// NULL means null. Values must not contain spaces.

public class Lab2 {
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
}
