import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class Driver implements Comparable<Driver> {
    private String name;
    private List<String> laps;

    public Driver(String name, List<String> laps) {
        this.name = name;
        this.laps = laps;
    }

    public static Driver createDriver(String line) {
        String[] parts = line.trim().split("\\s+");
        String name = parts[0];
        List<String> laps = new ArrayList<>();
        laps.addAll(Arrays.asList(parts).subList(1, parts.length));
        return new Driver(name, laps);
    }

    private static int toMillis(String lap) {
        String[] parts = lap.split(":");
        return Integer.parseInt(parts[0]) * 60 * 1000
                + Integer.parseInt(parts[1]) * 1000
                + Integer.parseInt(parts[2]);
    }

    public String getBestLap() {
        return laps.stream().min(Comparator.comparing(Driver::toMillis)).get();
    }

    @Override
    public int compareTo(Driver o) {
        return Integer.compare(toMillis(getBestLap()), toMillis(o.getBestLap()));
    }

    @Override
    public String toString() {
        return String.format("%-10s%10s", name, getBestLap());
    }
}

class F1Race {
    private List<Driver> drivers = new ArrayList<>();

    public void readResults(InputStream inputStream) {
        BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
        drivers = br.lines().map(Driver::createDriver).collect(Collectors.toList());
    }

    public void printSorted(OutputStream outputStream) {
        PrintWriter pw = new PrintWriter(outputStream);
        Collections.sort(drivers);
        int rank = 1;
        for (Driver driver : drivers) {
            pw.printf("%d. %s%n", rank++, driver);
        }

        pw.flush();
    }
}

public class F1Test {
    public static void main(String[] args) {
        F1Race f1Race = new F1Race();
        f1Race.readResults(System.in);
        f1Race.printSorted(System.out);
    }
}