import java.util.ArrayList;
import java.util.Arrays;

public class MyMathClass {

    public static <T extends Number> double standardDeviation(ArrayList<T> array) {
        double sum = 0;
        for (T n : array) {
            sum += n.doubleValue();
        }
        double avg = sum / array.size();
        sum = 0;
        for (T n : array) {
            sum += (avg - n.doubleValue()) * (avg - n.doubleValue());
        }
        return Math.sqrt(sum / array.size());
    }

    public static void main(String[] args) {
        ArrayList<Integer> ints = new ArrayList<>(Arrays.asList(1, 10, 20, 30, 40, 50));
        System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(ints)));     // STD: 16.84

        ArrayList<Double> doubles = new ArrayList<>(Arrays.asList(3.4));
        System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(doubles)));  // STD: 0.00

        ArrayList<Integer> bag = new ArrayList<>(Arrays.asList(2, 4, 4, 4, 5, 5, 7, 9));
        System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(bag)));      // STD: 2.00

        ArrayList<Double> two = new ArrayList<>(Arrays.asList(1.5, 2.5));
        System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(two)));      // STD: 0.50

        System.out.println(String.format("STD: %.2f", MyMathClass.standardDeviation(new ArrayList<Integer>())));   // STD: NaN
    }
}
