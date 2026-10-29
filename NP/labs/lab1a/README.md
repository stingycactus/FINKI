# Lab 1, Part A: Parking Garage System

In Part A, you implement the basic classes at home. In Part B (during the lab session), you will extend your own classes from Part A, so follow the names and signatures below exactly.

Part B (in the lab) adds extra requirements to this task, involving interfaces, lambda expressions and functional interfaces.

---

## 1. Class `Ticket`

Create an abstract, immutable class `Ticket` representing a parking ticket for one vehicle.

**Attributes:**

- `private final String plate` — the vehicle's license plate.
- `private final int minutes` — the length of the stay in minutes.

**Methods:**

- `protected Ticket(String plate, int minutes)` — a constructor that initializes the attributes. The license plate must not be `null` or an empty string, and the duration must be greater than `0`. Throw `IllegalArgumentException` for invalid values.
- `public String getPlate()` — returns the license plate.
- `public int getMinutes()` — returns the duration in minutes.
- `public abstract double price()` — returns the ticket price.
- `public String toString()` — returns a string representation containing the license plate.

**Note:** All attributes must be `private final`. You must not add any `set` methods.

## 2. Class `HourlyTicket`

Create a class `HourlyTicket` that extends `Ticket` and represents a ticket with hourly billing.

**Methods:**

- `public HourlyTicket(String plate, int minutes)` — a constructor that initializes the attributes through the `Ticket` constructor.
- `public double price()` — returns the price based on the number of started hours. Each started hour costs `50`.

Example: `60` minutes cost `50`, while `61` minutes cost `100`.

## 3. Class `DailyTicket`

Create a class `DailyTicket` that extends `Ticket` and represents a ticket with daily billing.

**Methods:**

- `public DailyTicket(String plate, int minutes)` — a constructor that initializes the attributes through the `Ticket` constructor.
- `public double price()` — returns the price based on the number of started days. Each started day costs `300`, where one day is `1440` minutes.

## 4. Exception `LotFullException`

Create an exception class `LotFullException` that extends `Exception`, with a constructor `LotFullException()`. It is thrown only when there is no space left in the parking garage. After a failed attempt, the state of the garage must not change (the ticket count and revenue must remain the same).

## 5. Class `ParkingLot`

Create a class `ParkingLot` that stores parking tickets in an array.

**Attributes:**

- `private Ticket[] tickets` — the array used to store tickets.
- `private int ticketCount` — the number of tickets currently stored in the garage.
- `private int capacity` — the capacity of the garage.

**Methods:**

- `public ParkingLot(int capacity)` — a constructor that creates the array with the specified capacity. The capacity must be greater than `0`; otherwise, throw `IllegalArgumentException`.
- `public void addTicket(Ticket ticket) throws LotFullException` — adds a ticket to the garage. If the ticket is `null`, throw `IllegalArgumentException`. If the garage is full, throw `LotFullException`.
- `public int getTicketCount()` — returns the number of tickets.
- `public double totalRevenue()` — returns the total revenue, calculated as the sum of the prices of all added tickets. If the garage is empty, return `0.0`.

**Important:** If an attempt to add a ticket fails, the state of the garage must not change. The ticket count and total revenue must remain the same.

---

## Example

INPUT
```text
NEW_HOURLY SK1234AB 1
NEW_HOURLY SK1234AB 60
NEW_HOURLY SK1234AB 61
NEW_DAILY BT5678CD 1440
NEW_DAILY BT5678CD 1441
NEW_DAILY OH9012EF 3000
END
```
RESULT
```text
HourlyTicket SK1234AB 1 50.0
HourlyTicket SK1234AB 60 50.0
HourlyTicket SK1234AB 61 100.0
DailyTicket BT5678CD 1440 300.0
DailyTicket BT5678CD 1441 600.0
DailyTicket OH9012EF 3000 900.0
```

## Extra test: the lot and invalid values

Uses the other commands of the given `main` (`LOT`, `ADD_*`, `ADD_NULL`, `COUNT`, `REVENUE`; `NULL` / `EMPTY` as a plate mean `null` / `""`).

INPUT
```text
LOT 0
LOT 2
NEW_HOURLY NULL 10
NEW_HOURLY EMPTY 10
NEW_DAILY AB1 0
ADD_HOURLY A1 61
ADD_NULL
ADD_DAILY B2 1441
ADD_HOURLY C3 30
COUNT
REVENUE
END
```
RESULT
```text
IllegalArgumentException
Lot created (capacity 2)
IllegalArgumentException
IllegalArgumentException
IllegalArgumentException
Added
IllegalArgumentException
Added
LotFullException
Count: 2
Revenue: 700.0
```
The failed `ADD_NULL` and the `LotFullException` don't change the count or the revenue (100 + 600 = 700).
