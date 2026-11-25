import java.util.*;
import java.util.stream.Collectors;

class Booking {
    private int id;
    private String room;
    private String organizer;
    private int minutes;

    public Booking(int id, String room, String organizer, int minutes) {
        this.id = id;
        this.room = room;
        this.organizer = organizer;
        this.minutes = minutes;
    }

    public int getId() { return id; }
    public String getRoom() { return room; }
    public String getOrganizer() { return organizer; }
    public int getMinutes() { return minutes; }

    @Override
    public String toString() { return "#" + id; }
}

class MapPractice {
    private List<Booking> bookings;

    public MapPractice(List<Booking> bookings) {
        this.bookings = bookings;
    }

    // 1. computeIfAbsent + ArrayList
    // room → its bookings, in the order they appear in the list.
    // Rooms sorted alphabetically (TreeMap).
    public Map<String, List<Booking>> byRoom() {
        Map<String, List<Booking>> roomBookingsMap = new TreeMap<>();
        for (Booking booking : bookings) {
            roomBookingsMap.computeIfAbsent(booking.getRoom(), k -> new ArrayList<>()).add(booking);
        }
        return roomBookingsMap;
    }

    // 2. computeIfAbsent + TreeSet with a comparator
    // room → its bookings, kept sorted by minutes DESCENDING, ties by id ascending.
    // Don't call sort(). Booking has no compareTo, so you MUST pass a comparator.
    public Map<String, Set<Booking>> sortedByRoom() {
        Map<String, Set<Booking>> map = new TreeMap<>();
        for (Booking booking : bookings) {
            map.putIfAbsent(booking.getRoom(), new TreeSet<>(Comparator.comparing(Booking::getMinutes, Comparator.reverseOrder()).thenComparing(Booking::getId)));
            map.get(booking.getRoom()).add(booking);
        }
        return map;
    }

    // 3. merge
    // organizer → total minutes of all their bookings. Use merge(..., Integer::sum).
    public Map<String, Integer> totalMinutesPerOrganizer() {
        Map<String, Integer> map = new HashMap<>();
//        for (Booking booking : bookings) {
//            String org = booking.getOrganizer();
//            map.put(org, map.getOrDefault(org, 0) + booking.getMinutes());
//        }
        for (Booking booking : bookings) {
            map.merge(booking.getOrganizer(), booking.getMinutes(), Integer::sum);
        }
        return map;
    }

    // 4. getOrDefault for counting + sorting entries by value
    // Count bookings per room (use getOrDefault, NOT merge, for practice),
    // then print "room: count" sorted by count DESCENDING, ties by room ascending.
    public void printRoomsByCount() {
        Map<String, Integer> map = new TreeMap<>();
        for (Booking booking : bookings) {
            String room = booking.getRoom();
            map.put(room, map.getOrDefault(room, 0) + 1);
        }
        map.entrySet().stream().sorted((a,b) -> {
            int c = b.getValue().compareTo(a.getValue());
            if (c == 0) {
                c = a.getKey().compareTo(b.getKey());
            }
            return c;
        }).forEach(e -> System.out.println(e.getKey() + ": " + e.getValue()));
    }

    // 5. group by the GIVEN keys only, return the map
    // For each organizer in the set: organizer → their bookings sorted by minutes
    // ascending, ties by id. Organizers with no bookings get an empty list.
    // Organizers NOT in the set must not appear. Result sorted by organizer (TreeMap).
    public Map<String, List<Booking>> byOrganizers(Set<String> organizers) {
        Map<String, List<Booking>> map = new TreeMap<>();
        for (String organizer : organizers) {
            List<Booking> list = bookings.stream().filter(b -> b.getOrganizer().equals(organizer))
                    .sorted(Comparator.comparing(Booking::getMinutes).thenComparing(Booking::getId))
                    .collect(Collectors.toList());
            map.put(organizer, list);
        }
        return map;
    }
}

public class MapPracticeTest {
    public static void main(String[] args) {
        List<Booking> bookings = List.of(
                new Booking(1, "B2.2", "Ana", 90),
                new Booking(2, "138", "Bojan", 60),
                new Booking(3, "B2.2", "Mishev", 120),
                new Booking(4, "B3.2", "Ana", 45),
                new Booking(5, "138", "Ana", 60),
                new Booking(6, "B2.2", "Bojan", 30),
                new Booking(7, "B3.2", "Mishev", 120)
        );
        MapPractice mp = new MapPractice(bookings);

        System.out.println("1: " + mp.byRoom());
        System.out.println("2: " + mp.sortedByRoom());
        System.out.println("3: " + mp.totalMinutesPerOrganizer());
        System.out.println("4:");
        mp.printRoomsByCount();
        System.out.println("5: " + mp.byOrganizers(Set.of("Ana", "Mishev", "Zoran")));
    }
}