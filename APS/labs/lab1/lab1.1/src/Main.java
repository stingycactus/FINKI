import java.util.Scanner;

class Employee {
    private String id;
    private String name;
    protected double baseSalary;

    public String getId() {
        return id;
    }

    public double getBaseSalary() {
        return baseSalary;
    }

    public String getName() {
        return name;
    }

    public Employee(String id, String name, double baseSalary) {
        this.id = id;
        this.name = name;
        this.baseSalary = baseSalary;
    }

    public double calculateSalary() {
        return baseSalary;
    }

    @Override
    public String toString() {
        return String.format("%s %s salary=%.2f", id, name, calculateSalary());
    }
}

class Developer extends Employee {
    private int overtimeHours;

    public Developer(String id, String name, double baseSalary, int overtimeHours) {
        super(id, name, baseSalary);
        this.overtimeHours = overtimeHours;
    }

    @Override
    public double calculateSalary() {
        return baseSalary + 300 * overtimeHours;
    }

    @Override
    public String toString() {
        return String.format("%s overtime=%d", super.toString(), overtimeHours);
    }
}

class TeamLead extends Developer {
    private int teamSize;

    public TeamLead(String id, String name, double baseSalary, int overtimeHours, int teamSize) {
        super(id, name, baseSalary, overtimeHours);
        this.teamSize = teamSize;
    }

    @Override
    public double calculateSalary() {
        double salary = super.calculateSalary() + 1000 * teamSize;
        return teamSize >= 5 ? salary * 1.05 : salary;
    }

    @Override
    public String toString() {
        return String.format("%s team=%d", super.toString(), teamSize);
    }
}

class Intern extends Employee {
    private int months;

    public Intern(String id, String name, double baseSalary, int months) {
        super(id, name, baseSalary);
        this.months = months;
    }

    @Override
    public double calculateSalary() {
        return months >= 6 ? super.calculateSalary() * 0.8 : super.calculateSalary() * 0.6;
    }

    @Override
    public String toString() {
        return String.format("%s months=%d", super.toString(), months);
    }
}

class Company {
    private Employee[] employees;
    private String name;
    private int capacity;
    private int count;

    public Company(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
        this.count = 0;
        employees = new Employee[capacity];
    }

    public void hire(Employee e) {
        employees[count] = e;
        count++;
    }

    public void printAll() {
        System.out.printf("=== %s ===%n", name);
        for (int i = 0; i < count; i++) {
            System.out.println(employees[i]);
        }
    }

    public void printStatistics() {
        int developersCount = 0;
        int teamLeadsCount = 0;
        int internsCount = 0;
        int othersCount = 0;
        for (int i = 0; i < count; i++) {
            if (employees[i].getClass() == Developer.class){
                developersCount++;
            }
            else if (employees[i].getClass() == TeamLead.class){
                teamLeadsCount++;
            }
            else if (employees[i].getClass() == Intern.class){
                internsCount++;
            }
            else {
                othersCount++;
            }
        }
        System.out.printf("Developers: %d, Team leads: %d, Interns: %d, Others: %d%n", developersCount, teamLeadsCount, internsCount, othersCount);
    }

    public double totalPayroll() {
        double totalSalary = 0;
        for (int i = 0; i < count; i++) {
            totalSalary+=employees[i].calculateSalary();
        }
        return totalSalary;
    }

    public double averageSalary() {
        return totalPayroll()/count;
    }

    public Employee highestPaid() {
        int index = 0;
        for (int i = 1; i < count; i++) {
            if (employees[i].calculateSalary()>employees[index].calculateSalary()) {
                index=i;
            }
        }
        return employees[index];
    }

    public int countAbove(double threshold){
        int employeeCount = 0;
        for (int i = 0; i < count; i++) {
            if (employees[i].calculateSalary()>threshold){
                employeeCount++;
            }
        }
        return employeeCount;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Company c = new Company("FINKI Soft", n);
        for (int i = 0; i < n; i++) {
            String type = in.next();
            String id = in.next();
            String name = in.next();
            double base = in.nextDouble();
            if (type.equals("E")){
                c.hire(new Employee(id, name, base));
            }
            else if (type.equals("D")){
                int overtime = in.nextInt();
                c.hire(new Developer(id, name, base, overtime));
            }
            else if (type.equals("L")){
                int overtime = in.nextInt();
                int teamSize = in.nextInt();
                c.hire(new TeamLead(id, name, base, overtime, teamSize));
            }
            else if (type.equals("I")){
                int months = in.nextInt();
                c.hire(new Intern(id, name, base, months));
            }
        }
        double threshold = in.nextDouble();
        c.printAll();
        c.printStatistics();
        System.out.printf("Total payroll: %.2f%n", c.totalPayroll());
        System.out.printf("Average salary: %.2f%n", c.averageSalary());
        Employee highestPaid = c.highestPaid();
        System.out.printf("Highest paid: %s %s (%.2f)%n", highestPaid.getId(), highestPaid.getName(), highestPaid.calculateSalary());
        System.out.printf("Employees with salary above %.2f: %d%n", threshold, c.countAbove(threshold));
    }
}