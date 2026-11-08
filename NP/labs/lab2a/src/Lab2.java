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

        Validator<String> nameNotNull = Validator.notNull();
        Validator<String> nameMinLen  = Validator.minLength(3);
        Validator<String> nameRule    = nameNotNull.and(nameMinLen);
        ValidationResult nameResult  = nameRule.validate(user.getName());

        Validator<Integer> ageNotNull = Validator.notNull();
        Validator<Integer> ageRange = Validator.range(18, 120);
        Validator<Integer> ageRule = ageNotNull.and(ageRange);
        ValidationResult ageResult = ageRule.validate(user.getAge());

        Validator<String> emailNotNull = Validator.notNull();
        Validator<String> emailMinLen = Validator.minLength(5);
        Validator<String> emailHasAt = v -> v.contains("@") ? ValidationResult.ok() : ValidationResult.error("must contain @");
        Validator<String> emailRule = emailNotNull.and(emailMinLen).and(emailHasAt);
        ValidationResult emailResult = emailRule.validate(user.getEmail());

        if (nameResult.isValid() && ageResult.isValid() && emailResult.isValid()) {
            return ValidationResult.ok();
        } else {
            List<String> errors = new ArrayList<>();

            if (!nameResult.isValid()) {
                for (String error : nameResult.getErrors()) {
                    errors.add(String.format("name: %s", error));
                }
            }

            if (!ageResult.isValid()) {
                for (String error : ageResult.getErrors()) {
                    errors.add(String.format("age: %s", error));
                }
            }

            if (!emailResult.isValid()) {
                for (String error : emailResult.getErrors()) {
                    errors.add(String.format("email: %s", error));
                }
            }

            return ValidationResult.of(errors);
        }

    }
}


// ===================== Test harness (do not modify) =====================
//
// Reads commands from standard input (one per line) and calls your classes.
// Validators have a name (e.g. V) and a type: STR (Validator<String>) or INT (Validator<Integer>).
// NULL means null. Values must not contain spaces.

public class Lab2 {
    private static final Map<String, Validator<?>> vals = new HashMap<>();
    private static final Map<String, String> types = new HashMap<>();

    private static String show(ValidationResult r) {
        return r.isValid() ? "Valid" : "Invalid: " + r.getErrors();
    }

    private static boolean missing(String name) {
        if (!vals.containsKey(name)) {
            System.out.println("No validator " + name);
            return true;
        }
        return false;
    }

    private static Validator<String> strAtom(String tok) {
        if (tok.equals("NOTNULL")) return Validator.<String>notNull();
        if (tok.startsWith("MINLEN:")) return Validator.minLength(Integer.parseInt(tok.substring(7)));
        if (tok.equals("HASAT")) {
            return s -> s.contains("@") ? ValidationResult.ok() : ValidationResult.error("must contain @");
        }
        throw new IllegalStateException("unknown atom " + tok);
    }

    private static Validator<Integer> intAtom(String tok) {
        if (tok.equals("NOTNULL")) return Validator.<Integer>notNull();
        if (tok.startsWith("RANGE:")) {
            String[] r = tok.split(":");
            return Validator.range(Integer.parseInt(r[1]), Integer.parseInt(r[2]));
        }
        throw new IllegalStateException("unknown atom " + tok);
    }

    private static String strValue(String t) {
        return t.equals("NULL") ? null : t;
    }

    private static Integer intValue(String t) {
        return t.equals("NULL") ? null : Integer.valueOf(t);
    }

    private static List<String> errorList(String t) {
        List<String> list = new ArrayList<>();
        if (!t.equals("-")) list.addAll(Arrays.asList(t.split(",")));
        return list;
    }

    @SuppressWarnings("unchecked")
    private static void run(String[] p) {
        switch (p[0]) {
            //   VAL <name> <STR|INT> <expr>   a chain of atoms joined with '>' (= .and(next))
            //        STR atoms: NOTNULL, MINLEN:<n>, HASAT (a lambda: "must contain @"), OBJNOTNULL (Validator<Object>.notNull())
            //        INT atoms: NOTNULL, RANGE:<min>:<max>
            case "VAL": {
                String[] toks = p[3].split(">");
                if (p[2].equals("STR")) {
                    Validator<String> v = null;
                    for (String tok : toks) {
                        if (tok.equals("OBJNOTNULL")) {
                            v = v.and(Validator.<Object>notNull());          // Validator<Object> where Validator<? super String> is expected
                        } else {
                            Validator<String> next = strAtom(tok);
                            v = (v == null) ? next : v.and(next);
                        }
                    }
                    vals.put(p[1], v);
                } else {
                    Validator<Integer> v = null;
                    for (String tok : toks) {
                        Validator<Integer> next = intAtom(tok);
                        v = (v == null) ? next : v.and(next);
                    }
                    vals.put(p[1], v);
                }
                types.put(p[1], p[2]);
                System.out.println("Defined " + p[1] + " (" + p[2] + ")");
                break;
            }
            case "CHECK": {
                if (missing(p[1])) break;
                ValidationResult r = types.get(p[1]).equals("STR")
                        ? ((Validator<String>) vals.get(p[1])).validate(strValue(p[2]))
                        : ((Validator<Integer>) vals.get(p[1])).validate(intValue(p[2]));
                System.out.println(show(r));
                break;
            }
            case "AND_NULL":
                if (missing(p[1])) break;
                ((Validator<String>) vals.get(p[1])).and(null);
                System.out.println("No exception");
                break;
            case "MODIFY": {
                if (missing(p[1])) break;
                ValidationResult r = types.get(p[1]).equals("STR")
                        ? ((Validator<String>) vals.get(p[1])).validate(strValue(p[2]))
                        : ((Validator<Integer>) vals.get(p[1])).validate(intValue(p[2]));
                r.getErrors().add("x");
                System.out.println("Modified");
                break;
            }
            case "RESULT_OK":
                System.out.println("ok: " + show(ValidationResult.ok()));
                break;
            case "RESULT_OK_MODIFY":
                ValidationResult.ok().getErrors().add("x");
                System.out.println("Modified");
                break;
            case "RESULT_ERROR":
                System.out.println("error: " + show(ValidationResult.error(p[1].equals("NULL") ? null : p[1].equals("EMPTY") ? "" : p[1])));
                break;
            case "RESULT_ERROR_MODIFY":
                ValidationResult.error(p[1]).getErrors().add("x");
                System.out.println("Modified");
                break;
            case "RESULT_OF":
                System.out.println("of: " + show(ValidationResult.of(errorList(p[1]))));
                break;
            case "RESULT_OF_COPY": {
                List<String> src = errorList(p[1]);
                ValidationResult r = ValidationResult.of(src);
                src.add("late");
                if (src.size() > 1) src.set(0, "changed");
                System.out.println("after change: " + show(r));
                break;
            }
            case "RESULT_OF_MODIFY":
                ValidationResult.of(errorList(p[1])).getErrors().add("x");
                System.out.println("Modified");
                break;
            case "RESULT_OF_NULL":
                ValidationResult.of(null);
                System.out.println("No exception");
                break;
            case "USER":
                System.out.println(show(UserValidation.validate(new User(strValue(p[1]), intValue(p[2]), strValue(p[3])))));
                break;
            case "USER_NULL":
                UserValidation.validate(null);
                System.out.println("No exception");
                break;
            default:
                System.out.println("Unknown command");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = in.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            String[] p = line.split("\\s+");
            if (p[0].equals("END")) break;
            try {
                run(p);
            } catch (IllegalArgumentException e) {
                System.out.println("IllegalArgumentException");
            } catch (UnsupportedOperationException e) {
                System.out.println("UnsupportedOperationException");
            }
        }
    }
}
