import java.io.*;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

class Leaderboard<T extends Comparable<T>> {
    List<T> items;

    public Leaderboard() {
        this.items = new ArrayList<>();
    }

    public Leaderboard(List<T> items) {
        this.items = new ArrayList<>(items);
    }

    public void add(T item) {
        items.add(item);
    }

    public List<T> top(int n) {
        return items.stream()
                .sorted(Comparator.reverseOrder())
                .limit(n)
                .collect(Collectors.toList());
    }

    public Leaderboard<T> filter(Predicate<? super T> condition) {
        return new Leaderboard<>(items.stream().filter(condition).collect(Collectors.toList()));
    }

    public void print(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        List<T> sorted = items.stream().sorted(Comparator.reverseOrder()).collect(Collectors.toList());
        int rank = 1;
        for (T t : sorted) {
            pw.printf("%d. %s%n", rank++, t);
        }
        pw.flush();
    }
}

class Player implements Comparable<Player> {
    private String name;
    private int wins;
    private int losses;
    private int points;

    public Player(String name, int wins, int losses) {
        this.name = name;
        this.wins = wins;
        this.losses = losses;
        this.points = 3 * wins - losses;
    }

    @Override
    public int compareTo(Player o) {
        if (points == o.points) {
            return Integer.compare(o.losses, losses);
        }
        return Integer.compare(points, o.points);
    }

    @Override
    public String toString() {
        return String.format("%s (%d)", name, points);
    }

    public String getName() {
        return name;
    }

    public int getWins() {
        return wins;
    }

    public int getLosses() {
        return losses;
    }

    public int getPoints() {
        return points;
    }
    public Character getChar() {
        return name.charAt(0);
    }
}

class PlayerReader {
    public static List<Player> read(InputStream is) {
        List<Player> players = new ArrayList<>();
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        br.lines().forEach(line -> {
            String[] parts = line.trim().split("\\s+");
            if (parts.length != 3) {
                System.out.printf("Invalid line: %s%n", line);
            } else {
                String name = parts[0];
                int wins = 0;
                int losses = 0;
                try {
                    wins = Integer.parseInt(parts[1]);
                    losses = Integer.parseInt(parts[2]);
                    players.add(new Player(name, wins, losses));
                } catch (NumberFormatException e) {
                    System.out.printf("Invalid line: %s%n", line);
                }
            }
        });
        return players;
    }

    static Map<Integer, List<String>> namesByPoints(List<Player> players) {
        Map<Integer, List<String>> map = new TreeMap<>();
        for (Player player : players) {
            map.putIfAbsent(player.getPoints(), new ArrayList<>());
            map.get(player.getPoints()).add(player.getName());
        }
        return map;
    }

    static Map<Integer, List<String>> namesByPoints2(List<Player> players) {
        return players.stream().collect(Collectors.
                groupingBy(
                        Player::getPoints,
                        TreeMap::new,
                        Collectors.mapping(Player::getName, Collectors.toList())
                )
        );
    }

    static Map<Character, Integer> winsByFirstLetter(List<Player> players) {
        return players.stream().
                collect(Collectors.groupingBy(Player::getChar, TreeMap::new, Collectors.summingInt(Player::getWins)));
    }
}

public class LeaderboardTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Leaderboard<Integer> numbers = new Leaderboard<>();
        Arrays.stream(sc.nextLine().trim().split("\\s+")).map(Integer::parseInt).forEach(numbers::add);
        int n = Integer.parseInt(sc.nextLine().trim());

        StringBuilder sb = new StringBuilder();
        while (sc.hasNextLine()) {
            sb.append(sc.nextLine()).append("\n");
        }

        System.out.println("=== NUMBERS ===");
        numbers.print(System.out);
        System.out.println("=== TOP " + n + " NUMBERS ===");
        System.out.println(numbers.top(n));

        System.out.println("=== READING PLAYERS ===");
        Leaderboard<Player> players = new Leaderboard<>();
        PlayerReader.read(new ByteArrayInputStream(sb.toString().getBytes())).forEach(players::add);

        System.out.println("=== PLAYERS ===");
        players.print(System.out);
        System.out.println("=== TOP " + n + " PLAYERS ===");
        System.out.println(players.top(n));

        // ===== TODO: define the following two conditions with lambda expressions =====
        Predicate<Player> positive = p -> p.getWins() > p.getLosses(); // TODO: more wins than losses
        Predicate<Integer> even = x -> x % 2 == 0; // TODO: even number
        // ================================================================================

        System.out.println("=== PLAYERS WITH MORE WINS THAN LOSSES ===");
        players.filter(positive).print(System.out);
        System.out.println("=== EVEN NUMBERS ===");
        numbers.filter(even).print(System.out);

        List<Player> list = PlayerReader.read(new ByteArrayInputStream(sb.toString().getBytes()));
        System.out.println(PlayerReader.namesByPoints(list));
        System.out.println(PlayerReader.namesByPoints2(list));
        System.out.println(PlayerReader.winsByFirstLetter(list));
        PlayerReader.namesByPoints(list).forEach((pts, names) -> System.out.printf("%d: %s%n", pts, names));
    }
}
