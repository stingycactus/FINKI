import java.util.*;

public class Main {
    public static void main(String[] args) {
        int[] arrive = {1, 2, 9, 5, 5};
        int[] leave  = {4, 5, 12, 9, 9};
        System.out.println("docks needed: " + maxDocks(arrive, leave));
        System.out.println("brute force: " + bruteDocks(arrive, leave));
    }

    static int maxDocks(int[] arrive, int[] leave) {
        int[] arrivals = arrive.clone();
        int[] departures = leave.clone();
        Arrays.sort(arrivals);
        Arrays.sort(departures);
        int i = 0;
        int j = 0;
        int current = 0;
        int maxTrucks = 0;
        while (i<arrivals.length) {
            if (arrivals[i] <= departures[j]) {
                current++;
                i++;
                maxTrucks = Math.max(maxTrucks, current);
            } else {
                current--;
                j++;
            }
        }
        return maxTrucks;
    }
    static int bruteDocks(int[] arrive, int[] leave) {
        int first = Integer.MAX_VALUE;
        int last = Integer.MIN_VALUE;
        for (int i = 0; i < arrive.length; i++) {
            first = Math.min(first, arrive[i]);
            last = Math.max(last, leave[i]);
        }
        int maxTrucks = 0;
        for (int minute = first; minute<=last; minute++) {
            int present = 0;
            for (int i = 0; i < arrive.length; i++) {
                if (arrive[i] <= minute && minute <= leave[i]) {
                    present++;
                }
            }
            maxTrucks = Math.max(maxTrucks,present);
        }
        return maxTrucks;
    }
}