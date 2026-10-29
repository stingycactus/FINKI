import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.function.*;

// ===================== Part A: solution classes =====================

abstract class Ticket {
    private final String plate;
    private final int minutes;

    protected Ticket(String plate, int minutes) {
        if (plate == null || plate.isEmpty() || minutes <= 0) {
            throw new IllegalArgumentException();
        }
        this.plate = plate;
        this.minutes = minutes;
    }

    public String getPlate() {
        return plate;
    }

    public int getMinutes() {
        return minutes;
    }

    public abstract double price();

    @Override
    public String toString() {
        return String.format("plate = %s", plate);
    }
}

class HourlyTicket extends Ticket {
    public HourlyTicket(String plate, int minutes) {
        super(plate, minutes);
    }

    @Override
    public double price() {
        return (Math.ceil((double) getMinutes() / 60)) * 50;
    }
}

class DailyTicket extends Ticket {
    public DailyTicket(String plate, int minutes) {
        super(plate, minutes);
    }

    @Override
    public double price() {
        return (Math.ceil((double) getMinutes() / 1440)) * 300;
    }
}

class LotFullException extends Exception {
    public LotFullException(String message) {
        super(message);
    }
}

class ParkingLot {
    private Ticket[] tickets;
    private int ticketCount;
    private int capacity;

    public ParkingLot(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        this.capacity = capacity;
        this.tickets = new Ticket[capacity];
    }

    public void addTicket(Ticket ticket) throws LotFullException {
        if (ticket == null) {
            throw new IllegalArgumentException();
        }
        if (ticketCount == capacity) {
            throw new LotFullException("lot full");
        }
        tickets[ticketCount++] = ticket;
    }

    public int getTicketCount() {
        return ticketCount;
    }

    public double totalRevenue() {
        double total = 0;
        for (int i = 0; i < ticketCount; i++) {
            total += tickets[i].price();
        }
        return total;
    }

    public double totalChargingFees() {
        double total = 0;
        for (int i = 0; i < ticketCount; i++) {
            if (tickets[i] instanceof Chargeable c) {
                total += c.chargingFee();
            }
        }
        return total;
    }

    void forEach(Consumer<Ticket> action) {
        for (int i = 0; i < ticketCount; i++) {
            action.accept(tickets[i]);
        }
    }

    int count(Predicate<Ticket> condition) {
        int counter = 0;
        for (int i = 0; i < ticketCount; i++) {
            if (condition.test(tickets[i])) {
                counter++;
            }
        }
        return counter;
    }

    Ticket findFirst(Predicate<Ticket> condition) {
        for (int i = 0; i < ticketCount; i++) {
            if (condition.test(tickets[i])) {
                return tickets[i];
            }
        }
        return null;
    }

    Ticket[] filter(Predicate<Ticket> condition) {
        Ticket[] result = new Ticket[count(condition)];
        int j = 0;
        for (int i = 0; i < ticketCount; i++) {
            if (condition.test(tickets[i])) {
                result[j++] = tickets[i];
            }
        }
        return result;
    }
    int addAll(int n, Supplier<Ticket> supplier) {
        int added = 0;
        for (int i = 0; i < n; i++) {
            try {
                addTicket(supplier.get());
                added++;
            } catch (LotFullException e) {
                break;
            }
        }
        return added;
    }
    String[] mapToLabels(Function<Ticket, String> mapper) {
        String[] labels = new String[ticketCount];
        for (int i = 0; i < ticketCount; i++) {
            labels[i] = mapper.apply(tickets[i]);
        }
        return labels;
    }
}

class FunctionalInterfacesTest {
    public static void main(String[] args) throws LotFullException {
        ParkingLot lot = new ParkingLot(10);

        Ticket[] tickets = {
                new HourlyTicket("A1", 61),
                new DailyTicket("B2", 1441),
                new HourlyTicket("C3", 30),
                new DailyTicket("D4", 100),
                new ElectricHourlyTicket("E5", 90)
        };
        for (Ticket t : tickets) {
            lot.addTicket(t);
        }

//        System.out.println(lot.count(ticket -> ticket instanceof DailyTicket));
//        lot.forEach(ticket -> System.out.println(ticket instanceof DailyTicket));
//        lot.forEach(ticket -> {
//            if (ticket instanceof DailyTicket) {
//                System.out.printf("dailyticket: %s%n", ticket);
//            }
//        });
//        System.out.println(lot.findFirst(ticket -> (ticket instanceof ElectricHourlyTicket)));
//        System.out.printf("filtered list: %s%n", Arrays.toString(lot.filter(ticket -> ticket instanceof DailyTicket)));
        System.out.println(Arrays.toString(lot.mapToLabels(t -> t.getPlate() + ":" + t.price())));
        lot.forEach(System.out::println);
        System.out.printf("added %d tickets to lot%n", lot.addAll(5, () -> new HourlyTicket("SUP", 30)));
        lot.forEach(System.out::println);
    }
}

interface Chargeable {
    double chargingFee();
}

class ElectricHourlyTicket extends HourlyTicket implements Chargeable {
    private static final double FEE = 30;

    public ElectricHourlyTicket(String plate, int minutes) {
        super(plate, minutes);
    }

    @Override
    public double chargingFee() {
        return FEE;
    }

    @Override
    public double price() {
        return super.price() + chargingFee();
    }
}

@FunctionalInterface
interface TicketFactory {
    Ticket create(String plate, int minutes);
}

class TicketFactories {
    private static final TicketFactory HOURLY = HourlyTicket::new;
    private static final TicketFactory DAILY = DailyTicket::new;
    private static final TicketFactory ELECTRIC = (plate, minutes) -> new ElectricHourlyTicket(plate, minutes);

    static TicketFactory getFactory(String type) {
        if (type.equals("H")) {
            return HOURLY;
        } else if (type.equals("D")) {
            return DAILY;
        } else if (type.equals("E")) {
            return ELECTRIC;
        }
        throw new IllegalArgumentException(String.format("Unknown type %s", type));
    }

}

// ===================== Main: command interpreter =====================
//
// Reads commands from standard input (one per line) and calls the matching constructor / method.
//
//   LOT <capacity>                  new ParkingLot(capacity)
//   NEW_HOURLY <plate> <minutes>    new HourlyTicket(plate, minutes)   -> prints type, plate, minutes, price()
//   NEW_DAILY  <plate> <minutes>    new DailyTicket(plate, minutes)    -> prints type, plate, minutes, price()
//   ADD_HOURLY <plate> <minutes>    lot.addTicket(new HourlyTicket(plate, minutes))
//   ADD_DAILY  <plate> <minutes>    lot.addTicket(new DailyTicket(plate, minutes))
//   ADD_NULL                        lot.addTicket(null)
//   COUNT                           lot.getTicketCount()
//   REVENUE                         lot.totalRevenue()
//   END                             stop reading
//
// In <plate>, the word NULL means a null plate and the word EMPTY means the empty string "".

public class Lab1 {
    private static ParkingLot lot = null;

    private static String plateArg(String token) {
        if (token.equals("NULL")) return null;
        if (token.equals("EMPTY")) return "";
        return token;
    }

    private static void addToLot(Ticket ticket) {
        // 'ticket' may be null (ADD_NULL) or the constructor may already have failed (handled by the caller)
        try {
            lot.addTicket(ticket);
            System.out.println("Added");
        } catch (LotFullException e) {
            System.out.println("LotFullException");
        } catch (IllegalArgumentException e) {
            System.out.println("IllegalArgumentException");
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = in.readLine()) != null) {
            line = line.trim();
            if (line.isEmpty()) continue;
            String[] p = line.split("\\s+");
            String cmd = p[0];
            if (cmd.equals("END")) break;

            switch (cmd) {
                case "LOT":
                    try {
                        lot = new ParkingLot(Integer.parseInt(p[1]));
                        System.out.println("Lot created (capacity " + p[1] + ")");
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                    }
                    break;

                case "NEW_HOURLY":
                case "NEW_DAILY":
                    try {
                        Ticket t = cmd.equals("NEW_HOURLY")
                                ? new HourlyTicket(plateArg(p[1]), Integer.parseInt(p[2]))
                                : new DailyTicket(plateArg(p[1]), Integer.parseInt(p[2]));
                        System.out.println((cmd.equals("NEW_HOURLY") ? "HourlyTicket " : "DailyTicket ")
                                + t.getPlate() + " " + t.getMinutes() + " " + t.price());
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                    }
                    break;

                case "ADD_HOURLY":
                case "ADD_DAILY":
                    if (lot == null) {
                        System.out.println("No lot created");
                        break;
                    }
                    Ticket ticket;
                    try {
                        ticket = cmd.equals("ADD_HOURLY")
                                ? new HourlyTicket(plateArg(p[1]), Integer.parseInt(p[2]))
                                : new DailyTicket(plateArg(p[1]), Integer.parseInt(p[2]));
                    } catch (IllegalArgumentException e) {
                        System.out.println("IllegalArgumentException");
                        break;
                    }
                    addToLot(ticket);
                    break;

                case "ADD_NULL":
                    if (lot == null) {
                        System.out.println("No lot created");
                    } else {
                        addToLot(null);
                    }
                    break;

                case "COUNT":
                    System.out.println(lot == null ? "No lot created" : "Count: " + lot.getTicketCount());
                    break;

                case "REVENUE":
                    System.out.println(lot == null ? "No lot created" : "Revenue: " + lot.totalRevenue());
                    break;

                default:
                    System.out.println("Unknown command");
            }
        }
    }
}