import java.awt.print.Book;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.time.*;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;

class InvalidBookingException extends Exception {
    public InvalidBookingException(String line) {
        super(String.format("Invalid booking: %s", line));
    }
}

class BookingConflictException extends Exception {
    public BookingConflictException(Booking booking, Booking existing) {
        super(String.format("Conflict: booking %d overlaps with booking %d in room %s", booking.getId(), existing.getId(), existing.getRoom()));
    }
}

class RoomNotFoundException extends Exception {
    public RoomNotFoundException(String room) {
        super(String.format("Room %s not found", room));
    }
}

abstract class Booking implements Comparable<Booking> {
    // ДАДЕНО - не менувај / GIVEN - do not change
    public static final DateTimeFormatter DATE_TIME =
            DateTimeFormatter.ofPattern("dd.MM.uuuu HH:mm").withResolverStyle(ResolverStyle.STRICT);
    public static final DateTimeFormatter DATE =
            DateTimeFormatter.ofPattern("dd.MM.uuuu").withResolverStyle(ResolverStyle.STRICT);
    public static final DateTimeFormatter TIME = DateTimeFormatter.ofPattern("HH:mm");
    public static final LocalTime WORK_START = LocalTime.of(8, 0);
    public static final LocalTime WORK_END = LocalTime.of(20, 0);

    private int id;
    private String room;
    private String organizer;
    private LocalDateTime start;
    private Duration duration;

    public Booking(int id, String room, String organizer, LocalDateTime start, Duration duration) {
        this.id = id;
        this.room = room;
        this.organizer = organizer;
        this.start = start;
        this.duration = duration;
    }

    public int getId() {
        return id;
    }

    public String getRoom() {
        return room;
    }

    public String getOrganizer() {
        return organizer;
    }

    public LocalDateTime getStart() {
        return start;
    }

    public Duration getDuration() {
        return duration;
    }


    public LocalDateTime getEnd() {
        return start.plus(duration);
    }

    public LocalDate getDate() {
        return start.toLocalDate();
    }

    public abstract Duration getBuffer();

    public abstract char getTypeCode();

    public LocalDateTime getBlockedFrom() {
        return start.minus(getBuffer());
    }

    public LocalDateTime getBlockedTo() {
        return getEnd().plus(getBuffer());
    }

    public boolean overlaps(Booking other) {
        return room.equals(other.room) && this.getBlockedFrom().isBefore(other.getBlockedTo()) && other.getBlockedFrom().isBefore(this.getBlockedTo());
    }

    public static String formatDuration(Duration d) {
        long hours = d.toHours();
        int minutes = d.toMinutesPart();
        return String.format("%dh %02dm", hours, minutes);
    }

    public static Booking createBooking(String line) throws InvalidBookingException {
        Booking b;
        String[] parts = line.trim().split(";", -1);
        if (parts.length != 7) {
            throw new InvalidBookingException(line);
        }
        String type = parts[0].trim();
        int id;
        LocalDateTime start;
        Duration duration;
        String extra;
        int number = 0;
        try {
            id = Integer.parseInt(parts[1].trim());
            start = LocalDateTime.parse(parts[4].trim(), DATE_TIME);
            duration = Duration.parse(parts[5].trim());
            extra = parts[6].trim();
            if (type.equals("E") || type.equals("M")) {
                number = Integer.parseInt(parts[6].trim());
            }
        } catch (NumberFormatException | DateTimeParseException e) {
            throw new InvalidBookingException(line);
        }
        String room = parts[2].trim();
        String organizer = parts[3].trim();
        if (room.isEmpty() || organizer.isEmpty() || extra.isEmpty()) {
            throw new InvalidBookingException(line);
        }
        if (duration.isNegative() || duration.isZero() || duration.toSecondsPart() != 0) {
            throw new InvalidBookingException(line);
        }
        LocalDateTime end = start.plus(duration);
        if (start.toLocalTime().isBefore(WORK_START) || end.toLocalTime().isAfter(WORK_END) || !end.toLocalDate().equals(start.toLocalDate())) {
            throw new InvalidBookingException(line);
        }
        if (type.equals("E") || type.equals("M")) {
            if (number <= 0) {
                throw new InvalidBookingException(line);
            }
        }
        if (type.equals("L")) {
            b = new Lecture(id, room, organizer, start, duration, extra);
        } else if (type.equals("E")) {
            b = new Exam(id, room, organizer, start, duration, number);
        } else if (type.equals("M")) {
            b = new Meeting(id, room, organizer, start, duration, number);
        } else {
            throw new InvalidBookingException(line);
        }
        return b;
    }

    @Override
    public int compareTo(Booking other) {
        int c = start.compareTo(other.start);
        if (c == 0) {
            c = room.compareTo(other.room);
        }
        if (c == 0) {
            c = Integer.compare(id, other.id);
        }
        return c;
    }

    @Override
    public String toString() {
        return String.format("%c %-3d %-6s %s %s-%s %-10s %s |", getTypeCode(), id, room, getDate().format(DATE), start.format(TIME), getEnd().format(TIME), organizer, formatDuration(duration));
    }
}

class Lecture extends Booking {
    private String courseCode;

    public Lecture(int id, String room, String organizer, LocalDateTime start, Duration duration,
                   String courseCode) {
        super(id, room, organizer, start, duration);
        this.courseCode = courseCode;
    }

    @Override
    public Duration getBuffer() {
        return Duration.ZERO;
    }

    @Override
    public char getTypeCode() {
        return 'L';
    }

    @Override
    public String toString() {
        return String.format("%s course: %s", super.toString(), courseCode);
    }
}

class Exam extends Booking {
    private int students;

    public Exam(int id, String room, String organizer, LocalDateTime start, Duration duration, int students) {
        super(id, room, organizer, start, duration);
        this.students = students;
    }

    @Override
    public Duration getBuffer() {
        return students <= 60 ? Duration.ofMinutes(15) : Duration.ofMinutes(30);
    }

    @Override
    public char getTypeCode() {
        return 'E';
    }

    @Override
    public String toString() {
        return String.format("%s students: %d, buffer: %sm", super.toString(), students, getBuffer().toMinutes());
    }
}

class Meeting extends Booking {
    private int participants;

    public Meeting(int id, String room, String organizer, LocalDateTime start, Duration duration,
                   int participants) {
        super(id, room, organizer, start, duration);
        this.participants = participants;
    }

    @Override
    public Duration getBuffer() {
        return Duration.ofMinutes(10);
    }

    @Override
    public char getTypeCode() {
        return 'M';
    }

    @Override
    public String toString() {
        return String.format("%s participants: %d, buffer: %sm", super.toString(), participants, getBuffer().toMinutes());
    }
}

class BookingSystem {
    private List<Booking> bookings = new ArrayList<>();
    private int invalidLines = 0;
    private int conflicts = 0;

    public void addBooking(Booking booking) throws BookingConflictException {
        for (Booking b : bookings) {
            if (b.overlaps(booking)) {
                conflicts++;
                throw new BookingConflictException(booking, b);
            }
        }
        bookings.add(booking);
    }

    public int readBookings(InputStream is, OutputStream log) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        PrintWriter pw = new PrintWriter(log);
        br.lines().filter(line -> !line.isBlank()).forEach(line -> {
            try {
                addBooking(Booking.createBooking(line));
            } catch (InvalidBookingException e) {
                pw.println(e.getMessage());
                invalidLines++;
            } catch (BookingConflictException e) {
                pw.println(e.getMessage());
            }
        });
        pw.flush();
        return bookings.size();
    }

    public int getInvalidLines() {
        return invalidLines;
    }

    public int getConflicts() {
        return conflicts;
    }

    public void printSchedule(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        bookings.stream().sorted(Booking::compareTo).forEach(pw::println);
        pw.flush();
    }

    public void printDay(OutputStream os, LocalDate date) {
        PrintWriter pw = new PrintWriter(os);
        List<Booking> filtered = bookings.stream().filter(booking -> booking.getDate().equals(date)).collect(Collectors.toList());
        if (filtered.isEmpty()) {
            pw.println("No bookings");
        } else {
            filtered.stream().sorted(Comparator.comparing(Booking::getRoom)
                            .thenComparing(Booking::getStart))
                    .forEach(pw::println);
        }
        pw.flush();
    }

    public void printRoom(OutputStream os, String room) throws RoomNotFoundException {
        PrintWriter pw = new PrintWriter(os);
        List<Booking> filtered = bookings.stream().filter(booking -> booking.getRoom().equals(room)).collect(Collectors.toList());
        if (filtered.isEmpty()) {
            throw new RoomNotFoundException(room);
        } else {
            filtered.stream().sorted(Comparator.comparing(Booking::getDate, Comparator.reverseOrder())
                            .thenComparing(Booking::getStart)
                            .thenComparing(Booking::getId))
                    .forEach(pw::println);
        }
        pw.flush();
    }

    public void printStatistics(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);

        if (bookings.isEmpty()) {
            pw.println("No bookings");
        } else {
            Map<Character, Long> counts = bookings.stream().collect(Collectors.groupingBy(Booking::getTypeCode, Collectors.counting()));
            pw.printf("Total: %d (lectures: %d, exams: %d, meetings: %d)%n", bookings.size(),
                    counts.getOrDefault('L', 0L),
                    counts.getOrDefault('E', 0L),
                    counts.getOrDefault('M', 0L));

            Duration total = Duration.ZERO;
            for (Booking b : bookings) {
                total = total.plus(b.getDuration());
            }

            pw.printf("Total booked: %s%n", Booking.formatDuration(total));

            Booking shortest = Collections.min(bookings, Comparator.comparing(Booking::getDuration)
                    .thenComparing(Comparator.naturalOrder()));
            Booking longest = Collections.max(bookings, Comparator.comparing(Booking::getDuration)
                    .thenComparing(Comparator.naturalOrder()));
            double average = total.toMinutes() / (double) bookings.size();

            pw.printf("Shortest: %s%n", shortest);
            pw.printf("Longest: %s%n", longest);
            pw.printf("Average duration: %.2f min%n", average);
            Map<LocalDate, Duration> perDay = new TreeMap<>();
            for (Booking booking : bookings) {
                LocalDate date = booking.getDate();
                perDay.put(date, perDay.getOrDefault(date, Duration.ZERO).plus(booking.getDuration()));
            }

            LocalDate busiest = null;
            for (Map.Entry<LocalDate, Duration> localDateDurationEntry : perDay.entrySet()) {
                if (busiest == null) {
                    busiest = localDateDurationEntry.getKey();
                } else {
                    if (localDateDurationEntry.getValue().compareTo(perDay.get(busiest)) > 0) {
                        busiest = localDateDurationEntry.getKey();
                    }
                }
            }
            pw.printf("Busiest day: %s (%s) %s%n", busiest.format(Booking.DATE), busiest.getDayOfWeek(), Booking.formatDuration(perDay.get(busiest)));
        }

        pw.flush();
    }
    public List<TimeSlot> getFreeSlots(String room, LocalDate date) throws RoomNotFoundException {
        List<Booking> bookingsInRoom = bookings.stream().filter(b -> b.getRoom().equals(room))
                .sorted(Comparator.comparing(Booking::getBlockedFrom)).collect(Collectors.toList());
        List<Booking> bookingsInRoomOnDate = bookingsInRoom.stream().filter(b -> b.getDate().equals(date)).collect(Collectors.toList());
        List<TimeSlot> freeIntervals = new ArrayList<>();
        if (bookingsInRoom.isEmpty()) {
            throw new RoomNotFoundException(room);
        }
        if (bookingsInRoomOnDate.isEmpty()) {
            freeIntervals.add(new TimeSlot(LocalTime.of(8, 0), LocalTime.of(20, 0)));
            return freeIntervals;
        }
        LocalTime cursor = LocalTime.of(8, 0);
        for (Booking booking : bookingsInRoomOnDate) {
            if (cursor.isAfter(booking.getBlockedFrom().toLocalTime())) {
                cursor = booking.getBlockedTo().toLocalTime();
            } else if (cursor.isBefore(booking.getBlockedTo().toLocalTime())) {
                freeIntervals.add(new TimeSlot(cursor, booking.getBlockedFrom().toLocalTime()));
                cursor = booking.getBlockedTo().toLocalTime();
            }
        }
        if (cursor.isBefore(LocalTime.of(20, 0))) {
            freeIntervals.add(new TimeSlot(cursor, LocalTime.of(20, 0)));
        }
        return freeIntervals;
    }

    public void printFreeSlots(OutputStream os, String room, LocalDate date) throws RoomNotFoundException {
        PrintWriter pw = new PrintWriter(os);
        List<TimeSlot> freeSlots = getFreeSlots(room, date);
        if (freeSlots.isEmpty()) {
            pw.println("No free slots");
        } else {
            freeSlots.forEach(pw::println);
            Duration total = Duration.ZERO;
            for (TimeSlot freeSlot : freeSlots) {
                total = total.plus(freeSlot.getDuration());
            }

            pw.printf("Total free: %s%n", Booking.formatDuration(total));
        }
        pw.flush();
    }

    public Optional<LocalDateTime> findFirstFit(String room, LocalDateTime from, Duration length) throws RoomNotFoundException {
        if (length == null || length.isNegative() || length.isZero()) {
            throw new IllegalArgumentException();
        }
        for (int i = 0; i < 6; i++) {
            List<TimeSlot> freeSlots = getFreeSlots(room, from.toLocalDate());
            for (TimeSlot freeSlot : freeSlots) {
                if (i == 0 && freeSlot.getFrom().isBefore(from.toLocalTime())) {
                    freeSlot.setFrom(from.toLocalTime());
                }
                if (freeSlot.getDuration().compareTo(length) > 0) {
//                    return freeSlot;
                }
            }
            from.plusDays(1);
        }
        return Optional.empty();
    }

    public void printRoomReport(OutputStream os) {
        PrintWriter pw = new PrintWriter(os);
        Map<String, List<Booking>> map = bookings.stream().collect(Collectors.groupingBy(Booking::getRoom, TreeMap::new, Collectors.toList()));
        for (Map.Entry<String, List<Booking>> e : map.entrySet()) {
            String room = e.getKey();
            List<Booking> bookingsInRoom = e.getValue();
            Duration total = Duration.ZERO;
            for (Booking booking : bookingsInRoom) {
                total = total.plus(booking.getDuration());
            }
            double average = total.toMinutes() / (double) bookings.size();
            List<LocalDate> existingDates = new ArrayList<>();
            int distinctDates = 0;
            for (Booking booking : bookingsInRoom) {
                if (!existingDates.contains(booking.getDate())) {
                    existingDates.add(booking.getDate());
                    distinctDates++;
                }
            }
            double utilization = 100.0 * total.toMinutes() / (existingDates.size()) * 720;
            Booking first = Collections.min(bookingsInRoom, Comparator.comparing(Booking::getStart));
            Booking last = Collections.max(bookingsInRoom, Comparator.comparing(Booking::getEnd));
            LocalDateTime start = first.getStart();
            LocalDateTime end = first.getEnd();
            pw.printf("%s bookings: %d, total:%s, avg: %.2f min, days: %d, utilization: %.2f, first: %s, last: %s%n",
                    e.getKey(), bookingsInRoom.size(), Booking.formatDuration(total), average,
                    existingDates.size(), utilization, start.format(Booking.DATE_TIME), end.format(Booking.DATE_TIME));
        }

        pw.flush();
    }

    public List<Booking> filter(Predicate<? super Booking> condition) {
        if (condition == null) {
            throw new IllegalArgumentException();
        }
        return bookings.stream().filter(condition).collect(Collectors.toList());
    }
}

class TimeSlot {
    private LocalTime from;
    private LocalTime to;

    public TimeSlot(LocalTime from, LocalTime to) {
        this.from = from;
        this.to = to;
    }

    public LocalTime getFrom() {
        return from;
    }

    public LocalTime getTo() {
        return to;
    }
    public Duration getDuration() {
        return Duration.between(from, to);
    }

    public void setFrom(LocalTime from) {
        this.from = from;
    }

    public void setTo(LocalTime to) {
        this.to = to;
    }

    @Override
    public String toString() {
        return String.format("%s-%s (%s)", from.format(Booking.TIME), to.format(Booking.TIME), Booking.formatDuration(getDuration()));
    }
}

public class BookingSystemTest {
    private static void printList(List<Booking> list) {
        if (list.isEmpty()) {
            System.out.println("No bookings");
        }
        list.forEach(System.out::println);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder bookingLines = new StringBuilder();
        String line;
        while ((line = br.readLine()) != null && !line.trim().equals("COMMANDS")) {
            bookingLines.append(line).append("\n");
        }

        BookingSystem system = new BookingSystem();
        int accepted = system.readBookings(
                new ByteArrayInputStream(bookingLines.toString().getBytes(StandardCharsets.UTF_8)), System.out);
        System.out.println("Accepted: " + accepted);
        System.out.println("Invalid: " + system.getInvalidLines());
        System.out.println("Conflicts: " + system.getConflicts());

        while ((line = br.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            String[] parts = line.split("\\s+");
            System.out.println("=== " + line + " ===");
            switch (parts[0]) {
                case "SCHEDULE":
                    system.printSchedule(System.out);
                    break;
                case "DAY":
                    system.printDay(System.out, LocalDate.parse(parts[1], Booking.DATE));
                    break;
                case "ROOM":
                    try {
                        system.printRoom(System.out, parts[1]);
                    } catch (RoomNotFoundException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "STATS":
                    system.printStatistics(System.out);
                    break;
                case "FREE":
                    try {
                        system.printFreeSlots(System.out, parts[1], LocalDate.parse(parts[2], Booking.DATE));
                    } catch (RoomNotFoundException e) {
                        System.out.println(e.getMessage());
                    }
                    break;
                case "FIRST_FIT":
                    try {
                        LocalDateTime from = LocalDateTime.parse(parts[2] + " " + parts[3], Booking.DATE_TIME);
                        Duration length = Duration.parse(parts[4]);
                        Optional<LocalDateTime> fit = system.findFirstFit(parts[1], from, length);
                        System.out.println(fit.map(t -> "First fit: " + t.format(Booking.DATE_TIME)
                                        + " (" + t.getDayOfWeek() + ")")
                                .orElse("No free slot in the next 7 days"));
                    } catch (RoomNotFoundException e) {
                        System.out.println(e.getMessage());
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                    }
                    break;
                case "REPORT":
                    system.printRoomReport(System.out);
                    break;
                case "FILTER_BETWEEN": {
                    LocalDate fromDate = LocalDate.parse(parts[1], Booking.DATE);
                    LocalDate toDate = LocalDate.parse(parts[2], Booking.DATE);
                    printList(system.filter(b -> !b.getDate().isBefore(fromDate) && !b.getDate().isAfter(toDate)));
                    break;
                }
                case "FILTER_LONGER": {
                    Duration limit = Duration.parse(parts[1]);
                    printList(system.filter(b -> b.getDuration().compareTo(limit) > 0));
                    break;
                }
                case "FILTER_WEEKDAY": {
                    DayOfWeek dayOfWeek = DayOfWeek.valueOf(parts[1]);
                    Predicate<Booking> onDay = b -> b.getStart().getDayOfWeek() == dayOfWeek;
                    printList(system.filter(onDay));
                    break;
                }
                case "FILTER_AFTER": {
                    LocalTime time = LocalTime.parse(parts[1], Booking.TIME);
                    printList(system.filter(b -> !b.getStart().toLocalTime().isBefore(time)));
                    break;
                }
                case "FILTER_NULL":
                    try {
                        system.filter(null);
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                    }
                    break;
                default:
                    System.out.println("Unknown command");
            }
        }
    }
}
