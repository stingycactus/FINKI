//package midterms.m1;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class QuizEvaluator{
    private List<String> correctAnswers;
    private List<Student> students;

    public QuizEvaluator(List<String> correctAnswers) {
        this.correctAnswers = correctAnswers;
    }

    public void evaluateQuizAttempts(InputStream is, OutputStream os) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        students = br.lines().map(Student::createStudent).collect(Collectors.toList());
        PrintWriter pw = new PrintWriter(os);
        for (Student student : students) {
            student.evalCorrect(correctAnswers);
        }
        students.stream().sorted(Comparator.comparing(Student::getCorrect, Comparator.reverseOrder())).forEach(student -> pw.printf("%s %d%n", student.getIndex(), student.getCorrect()));
        pw.flush();
    }
}

class Student{
    private String index;
    private List<String> answers;
    private int correct;

    public Student(String index, List<String> grades) {
        this.index = index;
        this.answers = grades;
    }

    public static Student createStudent(String line){
        String[] parts = line.trim().split("\\s+");
        String index = parts[0];
        List<String> grades = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            grades.add(parts[i]);
        }
        return new Student(index, grades);
    }

    public void evalCorrect(List<String> correctAnswers) {
        correct = 0;
        for (int i = 0; i<correctAnswers.size(); i++) {
            if (answers.get(i).equals(correctAnswers.get(i))) {
                correct++;
            }
        }
    }

    public String getIndex() {
        return index;
    }

    public List<String> getAnswers() {
        return answers;
    }

    public int getCorrect() {
        return correct;
    }
}

public class QuizEvaluatorTest {

    public static void wtf (Scanner in) throws FileNotFoundException {
        /*
        Read all lines from scanner and write them to a file input.txt
        * */
        PrintWriter pw = new PrintWriter(new FileOutputStream("input.txt"));
        while (in.hasNextLine()) {
            String line = in.nextLine();
            pw.println(line);
        }

        in.close();
        pw.flush();
    }

    public static void main(String[] args) throws IOException {

        Scanner sc = new Scanner(System.in);
        List<String> correct = Arrays.stream(sc.nextLine().split(";")).collect(Collectors.toList());

        wtf(sc);

        QuizEvaluator qe = new QuizEvaluator(correct);

        qe.evaluateQuizAttempts(new FileInputStream("input.txt"), System.out);
    }
}
