import java.awt.print.Book;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.time.*;
import java.time.chrono.ChronoLocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;
import java.util.*;
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
}

public class BookingSystemTest {
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
                default:
                    System.out.println("Unknown command");
            }
        }
    }
}
