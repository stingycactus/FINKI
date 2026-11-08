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
}

class RunClub {
    private List<Runner> runners = new ArrayList<>();

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

    static void print(List<Runner> runners) {
        for (Runner r : runners) {
            System.out.println(r);
        }
    }

    public static void main(String[] args) {
        // 1.1
        RunClub club = sampleClub();
        print(club.getList());
        club.printByClub("vardar");
        System.out.println();
        System.out.println(club.getTopN(3));
        print(club.getList());
        System.out.println(club.filterByClub("rabotnicki"));
        System.out.println(club.getClubs());
    }
}
