import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class GradeReport {
    private List<Integer> maxPoints;
    private List<Student> students;
    GradeReport(List<Integer> maxPoints) {
        this.maxPoints = maxPoints;
    }
    public void evaluate(InputStream is, OutputStream os) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        students = br.lines().map(Student::createStudent).collect(Collectors.toList());
        PrintWriter pw = new PrintWriter(os);
        students.forEach(s -> s.evalPts(maxPoints));
        students.stream()
                .sorted(Comparator.comparing(Student::getPtsPercentage, Comparator.reverseOrder()).thenComparing(Student::getIndex))
                .forEach(pw::println);
        pw.flush();
    }
}

class Student {
    private String index;
    private List<Integer> pts;
    private double ptsPercentage = 0;

    public Student(String index, List<Integer> pts) {
        this.index = index;
        this.pts = pts;
    }

    public static Student createStudent(String line) {
        String[] parts = line.trim().split("\\s+");
        String index = parts[0];
        List<Integer> pts = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            pts.add(Integer.valueOf(parts[i]));
        }
        return new Student(index, pts);
    }

    public void evalPts(List<Integer> maxPoints) {
        int earned = 0;
        for (int i = 0; i < Math.min(pts.size(), maxPoints.size()); i++) {
            earned += Math.min(pts.get(i), maxPoints.get(i));
        }
        int total = maxPoints.stream().mapToInt(Integer::intValue).sum();
        ptsPercentage = earned * 100.0 / total;
    }

    public String getIndex() {
        return index;
    }

    public double getPtsPercentage() {
        return ptsPercentage;
    }

    @Override
    public String toString() {
        return String.format("%s %.2f%%", index, ptsPercentage);
    }
}

public class GradeReportTest {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<Integer> maxPoints = Arrays.stream(sc.nextLine().trim().split("\\s+"))
                .map(Integer::parseInt)
                .collect(Collectors.toList());

        StringBuilder sb = new StringBuilder();
        while (sc.hasNextLine()) {
            sb.append(sc.nextLine()).append("\n");
        }

        GradeReport report = new GradeReport(maxPoints);
        report.evaluate(new ByteArrayInputStream(sb.toString().getBytes()), System.out);
    }
}
