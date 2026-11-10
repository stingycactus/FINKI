import java.util.*;
import java.util.stream.Collectors;

class Book {
    private String title;
    private String category;
    private float price;

    public Book(String title, String category, float price) {
        this.title = title;
        this.category = category;
        this.price = price;
    }

    public String getTitle() {
        return title;
    }

    public String getCategory() {
        return category;
    }

    public float getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return String.format("%s (%s) %.2f", title, category, price);
    }
}

class BookCollection {
    private List<Book> books = new ArrayList<>();

    public void addBook(Book book) {
        books.add(book);
    }

    public void printByCategory(String category) {
        books.stream().
                sorted(Comparator.comparing(Book::getTitle).thenComparing(Book::getPrice)).
                filter(b -> b.getCategory().equalsIgnoreCase(category)).forEach(System.out::println);
    }

    public List<Book> getCheapestN(int n) {
        return books.stream().sorted(Comparator.comparing(Book::getPrice).thenComparing(Book::getTitle)).limit(n).collect(Collectors.toList());
    }

}

public class BooksTest {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        BookCollection booksCollection = new BookCollection();
        Set<String> categories = new TreeSet<>();
        while (in.hasNextLine()) {
            String line = in.nextLine();
            String[] parts = line.trim().split(":+");
            String bookName = parts[0];
            String category = parts[1];
            float price = Float.parseFloat(parts[2]);
            Book b = new Book(bookName, category, price);
            booksCollection.addBook(b);
            categories.add(category);
        }
        System.out.println("=== PRINT BY CATEGORY ===");
        for (String category : categories) {
            System.out.println("CATEGORY: " + category);
            booksCollection.printByCategory(category);
        }
        System.out.println("=== TOP N BY PRICE ===");
        for (Book book : booksCollection.getCheapestN(n)) {
            System.out.println(book);
        }
    }
}
