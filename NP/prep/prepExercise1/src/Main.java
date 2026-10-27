import java.util.Arrays;
import java.util.Scanner;

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
        for (int i = 0; i < count; i++) {
            if (vehicles[i] instanceof Chargeable) {
                Chargeable ev = (Chargeable) vehicles[i];
                ev.charge();
            }
        }
    }

    static class UnknownVehicleTypeException extends Exception {
        public UnknownVehicleTypeException(char type) {
            super(String.format("%c is an unknown vehicle type", type));
        }
    }


    static Vehicle create(char type, String plate, int hours) throws UnknownVehicleTypeException {
        if (type == 'C') {
            return new Car(plate, hours);
        }
        else if (type == 'T') {
            return new Truck(plate, hours);
        }
        else if (type == 'M') {
            return new Motorcycle(plate, hours);
        }
        throw new UnknownVehicleTypeException(type);
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
        while (true) {
            String line = in.nextLine();
            String[] parts = line.trim().split("\\s+");
            char type = parts[0].charAt(0);
            if (Character.toLowerCase(type)=='q'){
                break;
            }
            String plate = parts[1];
            int hours = Integer.parseInt(parts[2]);
            try {
                Vehicle v = Garage.create(type, plate, hours);
                g.park(v);
                System.out.println("Parked " + v);
            } catch (Garage.UnknownVehicleTypeException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}