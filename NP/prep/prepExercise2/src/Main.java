import java.util.Arrays;
import java.util.Scanner;
import java.util.function.*;

abstract class Vehicle {
    private String plate;
    private int hours;
    private static int nextTicket = 1;
    private final int ticket;

    public Vehicle(String plate, int hours) {
        this.plate = plate;
        if (hours<0) {
            throw new IllegalArgumentException();
        }
        this.hours = hours;
        this.ticket = nextTicket++;
    }

    public String getPlate() {
        return plate;
    }

    public int getHours() {
        return hours;
    }

    abstract double fee();

    @Override
    public String toString() {
        return String.format("#%d %s %dh fee=%.2f", ticket, plate, hours, fee());
    }
}

class Car extends Vehicle {
    static final double RATE = 2.0;
    public Car(String plate, int hours) {
        super(plate, hours);
    }

    @Override
    double fee() {
        return RATE*getHours();
    }
}

class Truck extends Vehicle {
    static final double RATE = 5.0;
    public Truck(String plate, int hours) {
        super(plate, hours);
    }

    @Override
    double fee() {
        return RATE*getHours();
    }
}

interface Chargeable {
    void charge();
}

class ElectricCar extends Car implements Chargeable {
    private int battery;
    protected static final int CHARGE_STEP = 20;

    public ElectricCar(String plate, int hours, int battery) {
        super(plate, hours);
        this.battery = battery;
    }

    protected void addBattery(int amount) {
        battery+=amount;
        if (battery>=100) {
            battery=100;
        }
    }

    @Override
    public void charge() {
        addBattery(CHARGE_STEP);
    }

    @Override
    public String toString() {
        return String.format("%s battery=%d%%", super.toString(), battery);
    }
}

class FastElectricCar extends ElectricCar {
    public FastElectricCar(String plate, int hours, int battery) {
        super(plate, hours, battery);
    }
    @Override
    public void charge() {
        addBattery(CHARGE_STEP * 2);
    }
}

class Garage {
    private Vehicle[] vehicles;
    private int count;
    private int capacity;

    public Garage(int capacity) {
        this.capacity = capacity;
        this.vehicles = new Vehicle[capacity];
    }

    public Garage park(Vehicle v) {
        if (count==capacity) {
            capacity *= 2;
            vehicles = Arrays.copyOf(vehicles, capacity);
        }
        vehicles[count++] = v;
        return this;
    }

    public void printAll() {
        for (int i = 0; i < count; i++) {
            System.out.println(vehicles[i]);
        }
    }

    public double totalFees() {
        double total = 0;
        for (int i = 0; i < count; i++) {
            total+=vehicles[i].fee();
        }
        return total;
    }

    public void chargeAll() {
        applyIf(v -> v instanceof Chargeable, v -> ((Chargeable) v).charge());
    }

    static class UnknownVehicleTypeException extends Exception {
        public UnknownVehicleTypeException(char type) {
            super(String.format("%c is an unknown vehicle type", type));
        }
    }

    private static final BiFunction<String, Integer, Vehicle> CAR = (plate, hours) -> new Car(plate,hours);
    private static final BiFunction<String, Integer, Vehicle> TRUCK = (plate, hours) -> new Truck(plate, hours);
    private static final BiFunction<String, Integer, Vehicle> MOTO = (plate, hours) -> new Motorcycle(plate, hours);

    static BiFunction<String, Integer, Vehicle> getMaker(char type) throws UnknownVehicleTypeException {
        if (type == 'C') {
            return CAR;
        } else if (type == 'T') {
            return TRUCK;
        } else if (type == 'M') {
            return MOTO;
        }
        throw new UnknownVehicleTypeException(type);
    }

    void forEach(Consumer<Vehicle> action) {
        for (int i = 0; i < count; i++) {
            action.accept(vehicles[i]);
        }
    }

    int count(Predicate<Vehicle> condition) {
        int totalCount = 0;
        for (int i = 0; i < count; i++) {
            if (condition.test(vehicles[i])){
                totalCount++;
            }
        }
        return totalCount;
    }

    Vehicle findFirst(Predicate<Vehicle> condition) {
        for (int i = 0; i < count; i++) {
            if (condition.test(vehicles[i])) {
                return vehicles[i];
            }
        }
        return null;
    }

    Vehicle[] filter(Predicate<Vehicle> condition) {
        int newCount = count(condition);
        Vehicle[] result = new Vehicle[newCount];
        int j = 0;
        for (int i = 0; i < count; i++) {
            if (condition.test(vehicles[i])) {
                result[j++]=vehicles[i];
            }
        }
        return result;
    }

    String[] mapToLabels(Function<Vehicle, String> mapper) {
        String[] labels = new String[count];          // 1. one slot per vehicle
        for (int i = 0; i < count; i++) {
            labels[i] = mapper.apply(vehicles[i]);    // 2. store each result
        }
        return labels;                                // 3. hand the array back
    }

    void applyIf(Predicate<Vehicle> condition, Consumer<Vehicle> action) {
        for (int i = 0; i < count; i++) {
            if (condition.test(vehicles[i])){
                action.accept(vehicles[i]);
            }
        }
    }

}

class Motorcycle extends Vehicle {
    private static final double RATE = 1;

    public Motorcycle(String plate, int hours) {
        super(plate, hours);
    }

    @Override
    double fee() {
        return RATE*getHours();
    }
}

public class Main {
    public static void main(String[] args) {
//        Car c = new Car("SK1", 3);
//        Truck t = new Truck("SK2", 2);
//        System.out.println(c);
//        System.out.println(t);


        Garage g = new Garage(2);
//        g.park(new Car("SK1", 3));
//        g.park(new Truck("SK2", 2));
//        g.park(new ElectricCar("EV1", 2, 50));
//        g.park(new FastElectricCar("EV2", 1, 90));
//        g.printAll();
//        g.chargeAll();
//        g.printAll();
//        try {
//            Vehicle c = Garage.create('C', "SK3", 5);
//            System.out.println(c);
//        } catch (Garage.UnknownVehicleTypeException e) {
//            System.out.println(e.getMessage());
//        } finally {
//            System.out.println("finally");
//        }


        Scanner in = new Scanner(System.in);
//        while (true) {
//            String line = in.nextLine();
//            String[] parts = line.trim().split("\\s+");
//            char type = parts[0].charAt(0);
//            if (Character.toLowerCase(type)=='q'){
//                break;
//            }
//            String plate = parts[1];
//            int hours = Integer.parseInt(parts[2]);
//            try {
//                Vehicle v = Garage.create(type, plate, hours);
//                g.park(v);
//                System.out.println("Parked " + v);
//            } catch (Garage.UnknownVehicleTypeException e) {
//                System.out.println(e.getMessage());
//            }
//        }
        Chargeable test = () -> System.out.println("charging a test unit");
        Vehicle visitor = new Vehicle("GUEST", 5) {
            @Override
            double fee() {
                return 0;
            }
        };

        try {
            Vehicle v = Garage.getMaker('C').apply("SK1", 3);
            System.out.println(v);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        Supplier<Vehicle> s = () -> {
            String line = in.nextLine().trim();
            String[] parts = line.split("\\s+");
            char type = parts[0].charAt(0);
            String plate = parts[1];
            int hours = Integer.parseInt(parts[2]);
            try {
                Vehicle v = Garage.getMaker(type).apply(plate, hours);
                return v;
            } catch (Garage.UnknownVehicleTypeException e) {
                System.out.println(e.getMessage());
                return null;
            }
        };

        int n = Integer.parseInt(in.nextLine().trim());
        for (int i = 0; i < n; i++) {
            g.park(s.get());
        }
        g.printAll();
        g.forEach(v -> System.out.println(v.getPlate()));
    }
}