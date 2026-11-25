# Lab 4a – FINKI Rooms

Implement **FINKI Rooms**, a system for booking rooms (classrooms and labs) at the faculty. The system reads bookings from standard input, checks whether they are valid and whether they overlap, stores them, sorts them and prints statistics.

There are three kinds of bookings: lectures (`Lecture`), exams (`Exam`) and meetings (`Meeting`). All three extend the abstract class `Booking`.

Use the `java.time` classes for dates and times: `LocalDate`, `LocalTime`, `LocalDateTime`, `Duration` and `DateTimeFormatter`.

---

## 1. Exceptions

All three are **checked** exceptions (they extend `Exception`):

- `InvalidBookingException(String line)` – message: `Invalid booking: <line>`
- `BookingConflictException(Booking booking, Booking existing)` – message: `Conflict: booking <booking id> overlaps with booking <existing id> in room <room>`
- `RoomNotFoundException(String room)` – message: `Room <room> not found`

---

## 2. Abstract class `Booking`

The class implements the generic interface `Comparable<Booking>`. It stores `int id`, `String room`, `String organizer`, the start `LocalDateTime start` and the length `Duration duration`.

The following constants are given in the starter code:

```java
DATE_TIME  = DateTimeFormatter.ofPattern("dd.MM.uuuu HH:mm").withResolverStyle(ResolverStyle.STRICT);
DATE       = DateTimeFormatter.ofPattern("dd.MM.uuuu").withResolverStyle(ResolverStyle.STRICT);
TIME       = DateTimeFormatter.ofPattern("HH:mm");
WORK_START = LocalTime.of(8, 0);
WORK_END   = LocalTime.of(20, 0);
```

`ResolverStyle.STRICT` means that non-existent dates such as `31.11.2026` throw `DateTimeParseException`. In the default mode they would silently become `30.11.2026`.

The class must provide:

- the constructor `Booking(int id, String room, String organizer, LocalDateTime start, Duration duration)` and the methods `getId()`, `getRoom()`, `getOrganizer()`, `getStart()`, `getDuration()`;
- `LocalDateTime getEnd()` – the end of the booking (start + duration);
- `LocalDate getDate()` – the date of the booking;
- the abstract methods `Duration getBuffer()` and `char getTypeCode()`;
- `getBlockedFrom()` and `getBlockedTo()` – the interval during which the room is occupied: `[start − buffer, end + buffer)`. The buffer is the time needed to set up before and clean up after the event;
- `boolean overlaps(Booking other)` – returns `true` if both bookings are in the **same room** and their occupied intervals overlap. Intervals `[a1, a2)` and `[b1, b2)` overlap if `a1 < b2` and `b1 < a2`. Intervals that only touch (one ends exactly when the other starts) do **not** overlap;
- `static String formatDuration(Duration d)` – returns `String.format("%dh %02dm", hours, minutes)`, e.g. `1h 30m`, `0h 45m`, `12h 00m`;
- `compareTo` – the natural order: by start ascending, then by room ascending, then by id ascending;
- `toString()`: `String.format("%c %-3d %-6s %s %s-%s %-10s %s", type, id, room, date, startTime, endTime, organizer, duration)`. The date is formatted with `DATE`, the start and end times with `TIME`, and the duration with `formatDuration`.

---

## 3. Subclasses

| Class     | Type | Extra field         | Buffer                                          | Appended to `toString()`                          |
|-----------|------|---------------------|-------------------------------------------------|---------------------------------------------------|
| `Lecture` | `L`  | `String courseCode` | 0 minutes (`Duration.ZERO`)                     | `\| course: <courseCode>`                          |
| `Exam`    | `E`  | `int students`      | 15 minutes if students ≤ 60, otherwise 30 minutes | `\| students: <students>, buffer: <minutes>m`      |
| `Meeting` | `M`  | `int participants`  | 10 minutes                                      | `\| participants: <participants>, buffer: <minutes>m` |

Constructors take the same arguments as `Booking`, plus the extra field at the end. Each subclass calls the parent's `toString()` and appends its own part.

---

## 4. Line format and `createBooking`

Each booking is given on one line with exactly 7 fields separated by `;`. **Trim every field before parsing.**

```
TYPE;id;room;organizer;start;duration;extra
L;1;B2.2;Trajanov;23.11.2026 08:00;PT1H30M;NP
```

- `start` uses the format `dd.MM.yyyy HH:mm` and is parsed with `LocalDateTime.parse(..., DATE_TIME)`;
- `duration` uses the ISO-8601 format and is parsed with `Duration.parse(...)`. Examples: `PT45M` (45 minutes), `PT2H` (2 hours), `PT1H30M`;
- `extra` is the course code (`L`), the number of students (`E`) or the number of participants (`M`).

`static Booking createBooking(String line) throws InvalidBookingException` creates an object of the appropriate subclass. It throws if:

- the number of fields is not exactly 7 (use `line.split(";", -1)`);
- the type is not `L`, `E` or `M`;
- `id` is not an integer, or the date or duration cannot be parsed. Catch `NumberFormatException` and `DateTimeParseException`;
- `room`, `organizer` or `extra` is an empty string;
- the duration is not positive or is not a whole number of minutes (e.g. `PT1H30S`);
- the booking is outside working hours: the start is before 08:00, the end is after 20:00, or the end is on a different date. Ending exactly at 20:00 is allowed. The buffer is not part of this check;
- for `E` and `M`, `extra` is not an integer greater than 0.

---

## 5. Class `BookingSystem`

Stores the accepted bookings in a list. Implement:

- `void addBooking(Booking booking) throws BookingConflictException` – if the new booking overlaps an existing one, throws an exception with the **first** such existing booking (in insertion order). Otherwise the booking is added.
- `int readBookings(InputStream is, OutputStream log) throws IOException` – reads the lines with a `BufferedReader`. Blank lines are ignored. Every other line is processed with `createBooking` and `addBooking`. For an invalid line or a conflict, the exception message is printed to `log` with a `PrintWriter` and the matching counter is increased. Returns the number of accepted bookings.
- `int getInvalidLines()` and `int getConflicts()` – the counters.
- `void printSchedule(OutputStream os)` – prints all bookings in natural order.
- `void printDay(OutputStream os, LocalDate date)` – prints the bookings on that date, sorted by room, then by start. If there are none, prints `No bookings`.
- `void printRoom(OutputStream os, String room) throws RoomNotFoundException` – prints the bookings in the given room (exact match), sorted with a `Comparator` by:
  1. date descending (the latest day first),
  2. start time (`LocalTime`) ascending,
  3. id ascending.

  If the room has no bookings, throws `RoomNotFoundException`.
- `void printStatistics(OutputStream os)` – prints:

  ```
  Total: <n> (lectures: <l>, exams: <e>, meetings: <m>)
  Total booked: <sum of durations, formatDuration>
  Shortest: <shortest booking>
  Longest: <longest booking>
  Average duration: <average duration in minutes, %.2f> min
  Busiest day: <date> (<day of week>) <total duration on that day>
  ```

  - The shortest and longest bookings are compared by duration. Equal durations are decided by the natural order, i.e. the minimum and maximum by `Comparator.comparing(Booking::getDuration).thenComparing(Comparator.naturalOrder())`.
  - The busiest day is the date with the largest sum of durations. On a tie, the **earliest** date wins.
  - The day of the week is `date.getDayOfWeek()`, e.g. `MONDAY`.
  - If there are no bookings, print only `No bookings`.

In all printing methods, call `flush()` on the `PrintWriter`, but do **not** `close()` it.

---

## 6. Test class

The `BookingSystemTest` class is given. The input contains booking lines, a `COMMANDS` line, and the commands `SCHEDULE`, `DAY <dd.MM.yyyy>`, `ROOM <room>` and `STATS`.

---

## Example

**Input:**

```
M;1;A1;Ana;02.12.2026 10:00;PT1H;3
M;2;A2;Bojan;01.12.2026 10:00;PT1H;3
L;3;A1;Ana;01.12.2026 12:00;PT2H;X
L;4;A2;Bojan;02.12.2026 12:00;PT2H;Y
E;5;A1;Ana;03.12.2026 08:00;PT1H;10
M;6;A1;Ana;01.12.2026 08:00;PT1H;2
M;7;A2;Bojan;01.12.2026 08:00;PT1H;2
L;8;A1;Ana;02.12.2026 12:00;PT2H;Z
COMMANDS
SCHEDULE
ROOM A1
DAY 02.12.2026
DAY 01.12.2026
STATS
```

**Output:**

```
Accepted: 8
Invalid: 0
Conflicts: 0
=== SCHEDULE ===
M 6   A1     01.12.2026 08:00-09:00 Ana        1h 00m | participants: 2, buffer: 10m
M 7   A2     01.12.2026 08:00-09:00 Bojan      1h 00m | participants: 2, buffer: 10m
M 2   A2     01.12.2026 10:00-11:00 Bojan      1h 00m | participants: 3, buffer: 10m
L 3   A1     01.12.2026 12:00-14:00 Ana        2h 00m | course: X
M 1   A1     02.12.2026 10:00-11:00 Ana        1h 00m | participants: 3, buffer: 10m
L 8   A1     02.12.2026 12:00-14:00 Ana        2h 00m | course: Z
L 4   A2     02.12.2026 12:00-14:00 Bojan      2h 00m | course: Y
E 5   A1     03.12.2026 08:00-09:00 Ana        1h 00m | students: 10, buffer: 15m
=== ROOM A1 ===
E 5   A1     03.12.2026 08:00-09:00 Ana        1h 00m | students: 10, buffer: 15m
M 1   A1     02.12.2026 10:00-11:00 Ana        1h 00m | participants: 3, buffer: 10m
L 8   A1     02.12.2026 12:00-14:00 Ana        2h 00m | course: Z
M 6   A1     01.12.2026 08:00-09:00 Ana        1h 00m | participants: 2, buffer: 10m
L 3   A1     01.12.2026 12:00-14:00 Ana        2h 00m | course: X
=== DAY 02.12.2026 ===
M 1   A1     02.12.2026 10:00-11:00 Ana        1h 00m | participants: 3, buffer: 10m
L 8   A1     02.12.2026 12:00-14:00 Ana        2h 00m | course: Z
L 4   A2     02.12.2026 12:00-14:00 Bojan      2h 00m | course: Y
=== DAY 01.12.2026 ===
M 6   A1     01.12.2026 08:00-09:00 Ana        1h 00m | participants: 2, buffer: 10m
L 3   A1     01.12.2026 12:00-14:00 Ana        2h 00m | course: X
M 7   A2     01.12.2026 08:00-09:00 Bojan      1h 00m | participants: 2, buffer: 10m
M 2   A2     01.12.2026 10:00-11:00 Bojan      1h 00m | participants: 3, buffer: 10m
=== STATS ===
Total: 8 (lectures: 3, exams: 1, meetings: 4)
Total booked: 11h 00m
Shortest: M 6   A1     01.12.2026 08:00-09:00 Ana        1h 00m | participants: 2, buffer: 10m
Longest: L 4   A2     02.12.2026 12:00-14:00 Bojan      2h 00m | course: Y
Average duration: 82.50 min
Busiest day: 01.12.2026 (TUESDAY) 5h 00m
```
