import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

// TODO: your classes and interfaces here

interface Transformer<T, R> {
    R transform(T input);
}

class EmptyDataSetException extends Exception {
    public EmptyDataSetException(String message) {
        super(message);
    }
}

class DataSet<T extends Comparable<T>> {
    private List<T> elements;

    public DataSet() {
        this.elements = new ArrayList<>();
    }

    public DataSet(List<T> elements) {
        this.elements = new ArrayList<>(elements);
    }

    public void add(T element) {
        elements.add(element);
    }
    DataSet<T> filter(Predicate<T> condition) {
        return new DataSet<>(elements.stream().filter(condition).collect(Collectors.toList()));
    }
    <R extends Comparable<R>> DataSet<R> map(Transformer<? super T, ? extends R> transformer) {
        DataSet<R> result = new DataSet<>();
        for (T element : elements) {
            result.add(transformer.transform(element));
        }
        return result;
    }
    public T max() throws EmptyDataSetException {
        if (elements.isEmpty()) {
            throw new EmptyDataSetException("DataSet is empty");
        }
        return Collections.max(elements);
    }

    @Override
    public String toString() {
        List<T> sorted = new ArrayList<>(elements);
        Collections.sort(sorted);
        return sorted.toString();
    }

    boolean isEmpty() {
        return elements.isEmpty();
    }
}

class Stats {
    public static <T extends Comparable<T>> T maxOfAll(List<DataSet<T>> datasets) throws EmptyDataSetException {
        T largest = null;
        for (DataSet<T> dataset : datasets) {
            if (dataset.isEmpty()) {
                continue;
            }
            T currMax = dataset.max();
            if (largest == null || currMax.compareTo(largest) > 0) {
                largest = currMax;
            }
        }
        if (largest == null) {
            throw new EmptyDataSetException("DataSet is empty");
        }
        return largest;
    }
}

public class DataSetTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        DataSet<Integer> numbers = new DataSet<>();
        for (String s : sc.nextLine().trim().split("\\s+")) {
            numbers.add(Integer.parseInt(s));
        }

        DataSet<String> words = new DataSet<>();
        for (String s : sc.nextLine().trim().split("\\s+")) {
            words.add(s);
        }

        int minLength = Integer.parseInt(sc.nextLine().trim());

        // ===== TODO: define the following four objects with lambda expressions =====
        Predicate<Integer> even = x -> x%2==0;                    // keeps only the even numbers
        Transformer<Integer, Integer> square = x -> x*x;       // a number -> its square
        Transformer<String, Integer> length = String::length;        // a word -> its length
        Predicate<String> longWord = str -> str.length() > minLength;                 // keeps words longer than minLength
        // ==========================================================================

        System.out.println("=== NUMBERS ===");
        System.out.println(numbers);
        DataSet<Integer> evens = numbers.filter(even);
        DataSet<Integer> squares = numbers.map(square);
        System.out.println("even: " + evens);
        System.out.println("squares: " + squares);

        System.out.println("=== WORDS ===");
        System.out.println(words);
        System.out.println("lengths: " + words.map(length));
        System.out.println("longer than " + minLength + ": " + words.filter(longWord));

        System.out.println("=== MAX ===");
        try {
            System.out.println("max number: " + numbers.max());
            System.out.println("max word: " + words.max());
            System.out.println("max of even and squares: " + Stats.maxOfAll(Arrays.asList(evens, squares)));
            System.out.println("max even: " + evens.max());
        } catch (EmptyDataSetException e) {
            System.out.println(e.getMessage());
        }
    }
}
