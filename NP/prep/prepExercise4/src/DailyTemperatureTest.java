import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class DailyMeasurement implements Comparable<DailyMeasurement> {
    private int day;
    private List<Double> temperatures;

    public DailyMeasurement(int day, List<Double> temperatures) {
        this.day = day;
        this.temperatures = temperatures;
    }

    public int getDay() {
        return day;
    }

    public static DailyMeasurement createMeasurement(String line) {
        String[] parts = line.trim().split("\\s+");
        int day = Integer.parseInt(parts[0]);
        List<Double> temperatures = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            String unit = parts[i].substring(parts[i].length()-1);
            parts[i] = parts[i].substring(0, parts[i].length()-1);
            double temp = Double.parseDouble(parts[i]);
            if (unit.equals("F")) {
                temp = ((temp - 32) * 5) / 9;
            }
            temperatures.add(temp);
        }
        return new DailyMeasurement(day, temperatures);
    }

    @Override
    public int compareTo(DailyMeasurement o) {
        return Integer.compare(day, o.day);
    }

    public String stats(char scale) {
        //       return String.format("%3d: Count: %3d Min: %6.2f%c Max: %6.2f%c Avg: %6.2f%c", ...)
        List<Double> tempInScale = new ArrayList<>(temperatures);
        if (scale == 'F') {
            tempInScale = tempInScale.stream().map(temp -> ((temp * 9) / 5) + 32).collect(Collectors.toList());
        }
//        int count = tempInScale.size();
//        double min = Collections.min(tempInScale);
//        double max = tempInScale.stream().mapToDouble(Double::doubleValue).max().getAsDouble();
//        double average = tempInScale.stream().mapToDouble(Double::doubleValue).average().getAsDouble();
        DoubleSummaryStatistics s = tempInScale.stream().mapToDouble(Double::doubleValue).summaryStatistics();
        long count = s.getCount();
        double min = s.getMin();
        double max = s.getMax();
        double avg = s.getAverage();
        return String.format("%3d: Count: %3d Min: %6.2f%c Max: %6.2f%c Avg: %6.2f%c", day, count, min, scale, max, scale, avg, scale);
    }
}

class DailyTemperatures {
    private List<DailyMeasurement> measurements = new ArrayList<>();

    public DailyTemperatures() {
    }

    void readTemperatures(InputStream inputStream) {
        BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
        measurements = br.lines().map(DailyMeasurement::createMeasurement).collect(Collectors.toList());
    }

    void writeDailyStats(OutputStream outputStream, char scale) {
        PrintWriter pw = new PrintWriter(outputStream);
        measurements.stream().sorted().
                forEach(dm -> pw.println(dm.stats(scale)));
        pw.flush();
    }
}

public class DailyTemperatureTest {
    public static void main(String[] args) {
        DailyTemperatures dailyTemperatures = new DailyTemperatures();
        dailyTemperatures.readTemperatures(System.in);
        System.out.println("=== Daily temperatures in Celsius (C) ===");
        dailyTemperatures.writeDailyStats(System.out, 'C');
        System.out.println("=== Daily temperatures in Fahrenheit (F) ===");
        dailyTemperatures.writeDailyStats(System.out, 'F');
    }
}