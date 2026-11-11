import java.util.*;

public class Main {
    public static void main(String[] args) {
        int[] arrive = {1, 2, 9, 5, 5};
        int[] leave = {4, 5, 12, 9, 9};
        System.out.println("docks needed: " + maxDocks(arrive, leave));
        System.out.println("brute force: " + bruteDocks(arrive, leave));

        // Practice: study rooms (a session ending at hour X frees the room at X)
        int[] start = {9, 10, 11, 13, 13, 14};
        int[] end = {12, 13, 14, 15, 16, 15};
        System.out.println("rooms needed: " + minRooms(start, end));
        System.out.println("busiest hour: " + busiestHour(start, end));

        int[] start2 = {1, 3, 5};
        int[] end2 = {3, 5, 7};
        System.out.println("rooms needed: " + minRooms(start2, end2));
        System.out.println("busiest hour: " + busiestHour(start2, end2));
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
        while (i < arrivals.length) {
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
        for (int minute = first; minute <= last; minute++) {
            int present = 0;
            for (int i = 0; i < arrive.length; i++) {
                if (arrive[i] <= minute && minute <= leave[i]) {
                    present++;
                }
            }
            maxTrucks = Math.max(maxTrucks, present);
        }
        return maxTrucks;
    }

    static int minRooms(int[] start, int[] end) {
        start = start.clone();
        end = end.clone();
        Arrays.sort(start); // {9, 10, 11, 13, 13, 14};
        Arrays.sort(end); // {12, 13, 14, 15, 16, 15};
        int maxRooms = 0;
        int current = 0;
        int j = 0;
        for (int i = 0; i < start.length; i++) {
            if (end[j] <= start[i]) {
                current--;
                j++;
            }
            current++;
            maxRooms = Math.max(current, maxRooms);
        }
        return maxRooms;
    }

    static int busiestHour(int[] start, int[] end) {
        int first = Integer.MAX_VALUE;
        int last = Integer.MIN_VALUE;
        for (int s : start) {
            first = Math.min(first, s);
            last = Math.max(last, s);
        }
        int maxRoom = 0;
        int maxHours = 0;
        for (int hour = first; hour <= last; hour++) {
            int current = 0;
            for (int i = 0; i < start.length; i++) { // {9, 10, 11, 13, 13, 14}, {12, 13, 14, 15, 16, 15};
                if (start[i] <= hour && hour <= end[i]) {
                    current++;
                }
            }
            if (current > maxRoom) {
                maxRoom = current;
                maxHours = hour;
            }
        }
        return maxHours;
    }
}