import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class MovieRatings {
    private int minRatings;
    List<Movie> movies;

    MovieRatings(int minRatings) {
        this.minRatings = minRatings;
    }

    public void evaluate(InputStream is, OutputStream os) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        movies = br.lines().map(Movie::createMovie).collect(Collectors.toList());

        PrintWriter pw = new PrintWriter(os);
        movies.stream()
                .filter(m -> m.ratingsCount() >= minRatings)
                .sorted(Comparator.comparing(Movie::getAvgRating, Comparator.reverseOrder())
                        .thenComparing(Movie::ratingsCount, Comparator.reverseOrder())
                        .thenComparing(Movie::getTitle)).forEach(m -> {
                        pw.printf("%-10s %5.2f (%d)%n", m.getTitle(), m.getAvgRating(), m.ratingsCount());
                });
        pw.flush();
    }
}

class Movie {
    private String title;
    private List<Integer> ratings;

    public Movie(String title, List<Integer> ratings) {
        this.title = title;
        this.ratings = ratings;
    }

    public static Movie createMovie(String line) {
        String[] parts = line.trim().split("\\s+");
        String name = parts[0];
        List<Integer> ratings = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            ratings.add(Integer.valueOf(parts[i]));
        }
        return new Movie(name, ratings);
    }

    public double getAvgRating() {
        int sum = ratings.stream().filter(r -> r > 0 && r <= 10).mapToInt(Integer::intValue).sum();
        return (double) sum / ratingsCount();
    }

    public long ratingsCount() {
        return ratings.stream().filter(r -> r > 0 && r <= 10).count();
    }

    public String getTitle() {
        return title;
    }
}

public class MovieRatingsTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int minRatings = Integer.parseInt(sc.nextLine().trim());

        StringBuilder sb = new StringBuilder();
        while (sc.hasNextLine()) {
            sb.append(sc.nextLine()).append("\n");
        }

        MovieRatings ratings = new MovieRatings(minRatings);
        ratings.evaluate(new ByteArrayInputStream(sb.toString().getBytes()), System.out);
    }
}
