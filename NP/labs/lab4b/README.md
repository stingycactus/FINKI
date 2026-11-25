# Part B – Dates, Times and Sorting – FINKI Rooms

In this part you will extend the booking system you implemented in Part A. The system must now find the free time slots in a room, search for the first free slot of a given length within the next 7 days, print a room utilization report, and support filtering by any condition.

**Important:** Continue working on your Part A solution. All existing functionality must preserve its original behavior.

---

## 1. Class `TimeSlot`

Represents one free interval within a single day. It stores `LocalTime from` and `LocalTime to` and has:

- the constructor `TimeSlot(LocalTime from, LocalTime to)` and the methods `getFrom()`, `getTo()`;
- `Duration getDuration()` – the length of the interval (`Duration.between`);
- `toString()` – `String.format("%s-%s (%s)", from, to, formatDuration(getDuration()))`, with the times formatted using `Booking.TIME`. Example: `11:30-11:45 (0h 15m)`.

---

## 2. New methods in `BookingSystem`

- `List<TimeSlot> getFreeSlots(String room, LocalDate date) throws RoomNotFoundException` – returns the free intervals in the room on the given date, within working hours (08:00–20:00), in chronological order.
  - The occupied intervals (including buffers) of the bookings in that room on that date are taken into account.
  - Occupied intervals are clipped to working hours. For example, an exam at 08:00 with a 15-minute buffer occupies the room from 07:45, but free slots start no earlier than 08:00.
  - Intervals of length 0 are not returned. If two occupied intervals touch, there is no free slot between them.
  - If the room has no bookings at all in the system (on any date), throw `RoomNotFoundException`. If the room exists but has no bookings on that date, return one interval: `08:00–20:00`.

  > **Tip:** sort the bookings by `getBlockedFrom()` and walk through them with a "cursor" that starts at 08:00.

- `void printFreeSlots(OutputStream os, String room, LocalDate date) throws RoomNotFoundException` – prints the free slots, one per line. If there are none, prints `No free slots`. At the end it prints `Total free: <total free time, formatDuration>`.

- `Optional<LocalDateTime> findFirstFit(String room, LocalDateTime from, Duration length) throws RoomNotFoundException` – finds the earliest moment, not before `from`, at which the room is free for at least `length`.
  - Seven days are searched: the day of `from` and the following 6 days.
  - On the first day, a free slot that starts before `from` is cut so that it starts at `from`.
  - Returns the start of the first slot that is long enough (≥ `length`). If there is none, returns `Optional.empty()`.
  - If `length` is `null` or not positive, throw `IllegalArgumentException`. If the room does not exist, throw `RoomNotFoundException`.

- `void printRoomReport(OutputStream os)` – for each room, in alphabetical order, prints:

  ```java
  String.format("%-6s bookings: %d, total: %s, avg: %.2f min, days: %d, utilization: %.2f%%, first: %s, last: %s%n", ...)
  ```

  - `total` – the sum of durations (`formatDuration`);
  - `avg` – the average duration in minutes;
  - `days` – the number of distinct dates with bookings in that room;
  - `utilization` – the utilization percentage: `100 · total minutes / (days · 720)` (a working day lasts 720 minutes);
  - `first` – the earliest start and `last` – the latest end of a booking in that room, formatted with `DATE_TIME`.

  Buffers are not included in these calculations. If there are no bookings, print `No bookings`.

  > **Tip:** `Collectors.groupingBy(Booking::getRoom, TreeMap::new, Collectors.toList())`.

- `List<Booking> filter(Predicate<? super Booking> condition)` – returns a new list with the bookings satisfying the condition, in natural order. If `condition` is `null`, throw `IllegalArgumentException`.

---

## 3. Test class

The `BookingSystemTest` class is given. In addition to the Part A commands, it supports:

| Command | Description |
|---|---|
| `FREE <room> <dd.MM.yyyy>` | `printFreeSlots` |
| `FIRST_FIT <room> <dd.MM.yyyy> <HH:mm> <ISO duration>` | `findFirstFit`, e.g. `FIRST_FIT B2.2 23.11.2026 08:00 PT1H` |
| `REPORT` | `printRoomReport` |
| `FILTER_BETWEEN <d1> <d2>` | bookings with a date in `[d1, d2]` |
| `FILTER_LONGER <ISO duration>` | bookings strictly longer than the given duration |
| `FILTER_WEEKDAY <day>` | bookings on a given day of the week, e.g. `MONDAY` |
| `FILTER_AFTER <HH:mm>` | bookings starting at or after the given time |
| `FILTER_NULL` | calls `filter(null)` |

The filter conditions are given as lambda expressions in the test class.

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
FREE A1 01.12.2026
FIRST_FIT A1 01.12.2026 09:00 PT3H
FIRST_FIT A2 01.12.2026 09:00 PT10H
REPORT
ROOM A1
STATS
```

**Output:**

```
Accepted: 8
Invalid: 0
Conflicts: 0
=== FREE A1 01.12.2026 ===
09:10-12:00 (2h 50m)
14:00-20:00 (6h 00m)
Total free: 8h 50m
=== FIRST_FIT A1 01.12.2026 09:00 PT3H ===
First fit: 01.12.2026 14:00 (TUESDAY)
=== FIRST_FIT A2 01.12.2026 09:00 PT10H ===
First fit: 03.12.2026 08:00 (THURSDAY)
=== REPORT ===
A1     bookings: 5, total: 7h 00m, avg: 84.00 min, days: 3, utilization: 19.44%, first: 01.12.2026 08:00, last: 03.12.2026 09:00
A2     bookings: 3, total: 4h 00m, avg: 80.00 min, days: 2, utilization: 16.67%, first: 01.12.2026 08:00, last: 02.12.2026 14:00
=== ROOM A1 ===
E 5   A1     03.12.2026 08:00-09:00 Ana        1h 00m | students: 10, buffer: 15m
M 1   A1     02.12.2026 10:00-11:00 Ana        1h 00m | participants: 3, buffer: 10m
L 8   A1     02.12.2026 12:00-14:00 Ana        2h 00m | course: Z
M 6   A1     01.12.2026 08:00-09:00 Ana        1h 00m | participants: 2, buffer: 10m
L 3   A1     01.12.2026 12:00-14:00 Ana        2h 00m | course: X
=== STATS ===
Total: 8 (lectures: 3, exams: 1, meetings: 4)
Total booked: 11h 00m
Shortest: M 6   A1     01.12.2026 08:00-09:00 Ana        1h 00m | participants: 2, buffer: 10m
Longest: L 4   A2     02.12.2026 12:00-14:00 Bojan      2h 00m | course: Y
Average duration: 82.50 min
Busiest day: 01.12.2026 (TUESDAY) 5h 00m
```
