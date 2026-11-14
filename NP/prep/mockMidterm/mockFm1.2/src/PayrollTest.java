import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class Payroll {
    double minSalary;
    List<Employee> employees = new ArrayList<>();

    public Payroll(double minSalary) {
        this.minSalary = minSalary;
    }

    public void process(InputStream is, OutputStream os) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        PrintWriter pw = new PrintWriter(os);

        br.lines()
                .filter(line -> !line.trim().isEmpty())
                .forEach(line -> {
                    try {
                        employees.add(Employee.createEmployee(line, minSalary));
                    } catch (InvalidSalaryException e) {
                        pw.println(e.getMessage());
                    }
                });

        employees.stream()
                .sorted(Comparator.comparing(Employee::getSalary, Comparator.reverseOrder())
                        .thenComparing(Employee::getId))
                .forEach(e -> pw.printf("%-6s %-10s %10.2f%n", e.getId(), e.getName(), e.getSalary()));
        pw.flush();
    }
}

class InvalidSalaryException extends Exception {
    public InvalidSalaryException(String message) {
        super(message);
    }
}

class Employee {
    private String id;
    private String name;
    private int hours;
    private double rate;
    private double salary;

    public Employee(String id, String name, int hours, double rate, double salary) {
        this.id = id;
        this.name = name;
        this.hours = hours;
        this.rate = rate;
        this.salary = salary;
    }

    public static double calculateSalary(int hours, double rate) {
        if (hours > 160) {
            return 160 * rate + (hours - 160) * rate * 1.5;
        }
        return hours * rate;
    }

    public static Employee createEmployee(String line, double minSalary) throws InvalidSalaryException {
        String[] parts = line.trim().split("\\s+");
        String id = parts[0];
        String name = parts[1];
        int hours = Integer.parseInt(parts[2]);
        double rate = Double.parseDouble(parts[3]);
        double salary = calculateSalary(hours, rate);
        if (salary < minSalary) {
            throw new InvalidSalaryException(String.format("Employee %s has salary %.2f below the minimum of %.2f", id, salary, minSalary));
        }
        return new Employee(id, name, hours, rate, salary);
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getHours() {
        return hours;
    }

    public double getRate() {
        return rate;
    }

    public double getSalary() {
        return salary;
    }
}

public class PayrollTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double minSalary = Double.parseDouble(sc.nextLine().trim());

        StringBuilder sb = new StringBuilder();
        while (sc.hasNextLine()) {
            sb.append(sc.nextLine()).append("\n");
        }

        Payroll payroll = new Payroll(minSalary);
        payroll.process(new ByteArrayInputStream(sb.toString().getBytes()), System.out);
    }
}