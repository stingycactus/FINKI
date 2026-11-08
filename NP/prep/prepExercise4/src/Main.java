import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class Runner {
    private String name;
    private String club;
    private int age;
    private float weeklyKm;

    public Runner(String name, String club, int age, float weeklyKm) {
        this.name = name;
        this.club = club;
        this.age = age;
        this.weeklyKm = weeklyKm;
    }

    public String getName() {
        return name;
    }

    public String getClub() {
        return club;
    }

    public int getAge() {
        return age;
    }

    public float getWeeklyKm() {
        return weeklyKm;
    }

    @Override
    public String toString() {
        return String.format("%s (%s) %d %.1fkm", name, club, age, weeklyKm);
    }

    public static Runner createRunner(String line) {
        String[] parts = line.trim().split("\\s+");
        String name = parts[0];
        String club = parts[1];
        int age = Integer.parseInt(parts[2]);
        float weeklyKm = Float.parseFloat(parts[3]);
        return new Runner(name, club, age, weeklyKm);
    }
}

class RunClub {
    private List<Runner> runners = new ArrayList<>();
    private List<RaceResult> results = new ArrayList<>();
    private List<DayLog> logs = new ArrayList<>();

    public void addRunner(Runner r) {
        runners.add(r);
    }

    public List<Runner> getList() {
        return runners;
    }

    public void printByClub(String club) {
        List<Runner> clubRunners = new ArrayList<>();
        for (Runner runner : runners) {
            if (runner.getClub().equalsIgnoreCase(club)) {
                clubRunners.add(runner);
            }
        }
        clubRunners.sort(new NameAndAgeComparator());
        for (Runner clubRunner : clubRunners) {
            System.out.printf("%s ", clubRunner);
        }
    }

    public void sortByAge(boolean ascending) {
        Comparator<Runner> byAgeThenKm = Comparator.comparing(Runner::getAge).thenComparing(Runner::getWeeklyKm);
        if (ascending) {
            runners.sort(byAgeThenKm);
        } else {
            runners.sort(byAgeThenKm.reversed());
        }
    }

    public List<Runner> getTopN(int n) {
        n = Math.min(n, runners.size());
        List<Runner> sorted = new ArrayList<>(runners);
        sorted.sort(new KmDescComparator());

        List<Runner> top = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            top.add(sorted.get(i));
        }
        return top;
    }

    public List<Runner> filterByClub(String club) {
        return runners.stream()
                .filter(r -> r.getClub().equalsIgnoreCase(club))
                .sorted(new NameAndAgeComparator())
                .collect(Collectors.toList());
    }

    public Set<String> getClubs() {
        Set<String> clubs = new TreeSet<>();
        for (Runner runner : runners) {
            clubs.add(runner.getClub());
        }
        return clubs;
    }

    public void readRunners(InputStream in) {
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        runners = br.lines().map(Runner::createRunner).collect(Collectors.toList());
    }

    public void readRunnersScanner(InputStream in) {
        Scanner sc = new Scanner(in);              // 1. wrap the input so you can read it
        while (sc.hasNextLine()) {                 // 2. is there another line?
            String line = sc.nextLine();           // 3. read it, e.g. "Ana Vardar 24 31.5"
            addRunner(Runner.createRunner(line));  // 4. turn it into a Runner and add it
        }                                          // 5. back to 2, until the file ends
    }

    public void readRace(InputStream in) {
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        results = br.lines().map(RaceResult::createResult).collect(Collectors.toList());
    }

    public List<RaceResult> getResults() {
        return results;
    }

    public void printRace(OutputStream out) {
        List<RaceResult> sorted = new ArrayList<>(results);
        Collections.sort(sorted);
        PrintWriter pw = new PrintWriter(out);
        int rank = 1;
        for (RaceResult raceResult : sorted) {
            pw.println(String.format("%d. %-10s%8s", rank++, raceResult.getName(), raceResult.getBestSplit()));
        }
        pw.flush();
    }
    public void readLog(InputStream in) {
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        logs = br.lines().map(DayLog::createDayLog).collect(Collectors.toList());
    }
    public void writeLogStats(OutputStream out, char unit) {
        PrintWriter pw = new PrintWriter(out);
        List<DayLog> sorted = new ArrayList<>(logs);
        Collections.sort(sorted);
        for (DayLog dayLog : sorted) {
            pw.println(dayLog.stats(unit));
        }
        pw.flush();
    }
}

class NameAndAgeComparator implements Comparator<Runner> {
    @Override
    public int compare(Runner o1, Runner o2) {
        int byName = o1.getName().compareTo(o2.getName());
        if (byName == 0) {
            return Integer.compare(o1.getAge(), o2.getAge());
        }
        return byName;
    }
}

class AgeAndKmComparator implements Comparator<Runner> {
    @Override
    public int compare(Runner o1, Runner o2) {
        if (o1.getAge() == o2.getAge()) {
            return Float.compare(o1.getWeeklyKm(), o2.getWeeklyKm());
        }
        return Integer.compare(o1.getAge(), o2.getAge());
    }
}

class KmDescComparator implements Comparator<Runner> {
    @Override
    public int compare(Runner o1, Runner o2) {
        if (o1.getWeeklyKm() == o2.getWeeklyKm()) {
            return o1.getName().compareTo(o2.getName());
        }
        return Float.compare(o2.getWeeklyKm(), o1.getWeeklyKm());
    }
}

class RaceResult implements Comparable<RaceResult> {
    private String name;
    private List<String> splits;

    private static int toSeconds(String split) {
        String[] parts = split.split(":");
        int minutes = Integer.parseInt(parts[0]);
        int seconds = Integer.parseInt(parts[1]);
        return minutes * 60 + seconds;
    }

    public RaceResult(String name, List<String> splits) {
        this.name = name;
        this.splits = splits;
    }

    public static RaceResult createResult(String line) {
        String[] parts = line.trim().split("\\s+");
        String name = parts[0];
        List<String> splits = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            splits.add(parts[i]);
        }
        return new RaceResult(name, splits);
    }

    public String getName() {
        return name;
    }

    public String getBestSplit() {
        int index = 0;
        for (int i = 1; i < splits.size(); i++) {
            int splitInSeconds = RaceResult.toSeconds(splits.get(i));
            int indexSplitInSeconds = RaceResult.toSeconds(splits.get(index));
            if (splitInSeconds < indexSplitInSeconds) {
                index = i;
            }
        }
        return splits.get(index);
    }

    @Override
    public int compareTo(RaceResult o) {
        return Integer.compare(RaceResult.toSeconds(this.getBestSplit()), RaceResult.toSeconds(o.getBestSplit()));
    }

    @Override
    public String toString() {
        return String.format("%s %s", name, this.getBestSplit());
    }
}

class DayLog implements Comparable<DayLog> {
    static final double KM_PER_MILE = 1.609344;
    private int day;
    private List<Double> km;

    public DayLog(int day, List<Double> km) {
        this.day = day;
        this.km = km;
    }

    public int getDay() {
        return day;
    }

    public static DayLog createDayLog(String line) {
        String[] parts = line.trim().split("\\s+");
        int day = Integer.parseInt(parts[0]);
        List<Double> distances = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            String distancePart = parts[i];
            String unit = distancePart.substring(distancePart.length()-2);
            double distance = Double.parseDouble(distancePart.substring(0, distancePart.length() - 2));
            if (unit.equals("mi")) {
                distance*=KM_PER_MILE;
            }
            distances.add(distance);
        }
        return new DayLog(day, distances);
    }

    @Override
    public int compareTo(DayLog o) {
        return Integer.compare(day, o.day);
    }

    public String stats(char unit) {
        List<Double> distancesInUnit = new ArrayList<>();
        for (Double v : km) {
            distancesInUnit.add(unit == 'M' ? v / KM_PER_MILE : v);
        }
        int count = distancesInUnit.size();
        double min = Collections.min(distancesInUnit);
        double max = distancesInUnit.stream().max(Double::compareTo).get();
        double sum = 0;
        for (Double v : distancesInUnit) {
            sum+=v;
        }
        double avg = sum / count;
        String u = unit == 'M' ? "mi" : "km";
        return String.format("%3d: Count: %2d Min: %6.2f%s Max: %6.2f%s Avg: %6.2f%s",
                day, count, min, u, max, u, avg, u);    }
}

public class Main {
    static RunClub sampleClub() {
        RunClub club = new RunClub();
        club.addRunner(new Runner("Ana", "Vardar", 24, 31.5f));
        club.addRunner(new Runner("Marko", "Rabotnicki", 31, 42.0f));
        club.addRunner(new Runner("Bojan", "vardar", 24, 18.5f));
        club.addRunner(new Runner("Elena", "Rabotnicki", 19, 42.0f));
        club.addRunner(new Runner("Ana", "Vardar", 22, 27.0f));
        club.addRunner(new Runner("Ivan", "Skopje", 45, 12.0f));
        return club;
    }

    static InputStream input(String text) {
        return new ByteArrayInputStream(text.getBytes());
    }

    static void print(List<?> items) {
        for (Object item : items) {
            System.out.println(item);
        }
    }

    public static void main(String[] args) {
        System.out.println("=== 1.1 list");
        print(sampleClub().getList());

        System.out.println("=== 1.2 printByClub");
        RunClub club = sampleClub();
        club.printByClub("vardar");     System.out.println("--");
        club.printByClub("RABOTNICKI"); System.out.println("--");
        club.printByClub("Pelister");   System.out.println("--");

        System.out.println("=== 1.3 sortByAge");
        club = sampleClub();
        club.sortByAge(true);  System.out.println("ASC");  print(club.getList());
        club.sortByAge(false); System.out.println("DESC"); print(club.getList());

        System.out.println("=== 1.4 topN / filter");
        club = sampleClub();
        System.out.println("TOP 3");  print(club.getTopN(3));
        System.out.println("TOP 10: " + club.getTopN(10).size());
        System.out.println("FILTER"); print(club.filterByClub("rabotnicki"));
        System.out.println("LIST");   print(club.getList());

        System.out.println("=== 1.5 clubs");
        System.out.println(club.getClubs());

        System.out.println("=== 1.6 readRunners");
        RunClub fromInput = new RunClub();
        fromInput.readRunners(input(
                "Ana Vardar 24 31.5\n" +
                        "Marko Rabotnicki 31 42.0\n" +
                        "Bojan vardar 24 18.5\n" +
                        "Elena Rabotnicki 19 42.0\n" +
                        "Ana Vardar 22 27.0\n" +
                        "Ivan Skopje 45 12.0\n"));
        print(fromInput.getList());

        System.out.println("=== 1.7 race results");
        RunClub raceClub = new RunClub();
        raceClub.readRace(input(
                "Ana 4:55 5:02 4:49\n" +
                        "Marko 4:40 4:52 4:47\n" +
                        "Ivan 10:15 9:58 10:02\n" +
                        "Elena 4:41 4:39 4:50\n"));
        Collections.sort(raceClub.getResults());
        print(raceClub.getResults());

        System.out.println("=== 1.8 printRace");
        raceClub.printRace(System.out);

        System.out.println("=== 1.9 log stats");
        RunClub logClub = new RunClub();
        logClub.readLog(input("12 5km 3.1mi 10km\n3 8.5km\n7 2mi 4mi\n"));
        System.out.println("=== km ===");       logClub.writeLogStats(System.out, 'K');
        System.out.println("=== mi ===");       logClub.writeLogStats(System.out, 'M');
        System.out.println("=== mi again ==="); logClub.writeLogStats(System.out, 'M');
    }
}