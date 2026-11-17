import java.util.ArrayList;
import java.util.Comparator;
import java.util.Scanner;

public class TrainPlatforms {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        ArrayList<Integer> arrivals = new ArrayList<>();
        ArrayList<Integer> departures = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            arrivals.add(in.nextInt());
            departures.add(in.nextInt());
        }
        arrivals.sort(Comparator.naturalOrder());
        departures.sort(Comparator.naturalOrder());

        int maxCount = 0;
        int count = 0;
        int i = 0, j = 0;
        while (i < arrivals.size()) {
            if (arrivals.get(i) <= departures.get(j)) {
                count++;
                i++;                       // this arrival is done
                maxCount = Math.max(count, maxCount);
            } else {
                count--;
                j++;                       // this departure is done; i stays
            }
        }
        System.out.println(maxCount);
    }
}
