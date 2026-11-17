import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/*
 * Advanced 1 (greedy): N intervals with a start and an end time,
 * numbered from 1 in input order. Pick as many non-overlapping intervals as
 * possible (one may start exactly when the previous one ends).
 * Print how many were picked, then their numbers.
 */
class Interval {
    int start, end, id;

    Interval(int start, int end, int id) {
        this.start = start;
        this.end = end;
        this.id = id;
    }

    int getEnd() {
        return end;
    }
}

public class MeetingSelection {

    static String solve(int[][] times) {
        List<Interval> list = new ArrayList<>();
        for (int i = 0; i < times.length; i++) {
            list.add(new Interval(times[i][0], times[i][1], i + 1));   // number from 1
        }
        list.sort(Comparator.comparing(Interval::getEnd));             // the one that ends first goes first

        List<Interval> chosen = new ArrayList<>();
        int time = Integer.MIN_VALUE;                                   // when the last chosen one ends
        for (Interval it : list) {
            if (it.start >= time) {                                     // starts after the last one ended
                chosen.add(it);
                time = it.end;
            }
        }

        StringBuilder sb = new StringBuilder();
        sb.append(chosen.size()).append("\n");
        for (int i = 0; i < chosen.size(); i++) {
            if (i > 0) sb.append(" ");
            sb.append(chosen.get(i).id);
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        int[][][] tests = {
                {{1, 4}, {2, 5}, {4, 7}, {3, 8}, {7, 9}, {8, 10}},   // touching: 1-4, 4-7, 7-9
                {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}},
                {{0, 10}, {1, 2}, {3, 4}},
                {{1, 3}, {3, 5}, {5, 7}},
        };
        String[] expected = {
                "3\n1 3 5",
                "3\n1 4 5",
                "2\n2 3",
                "3\n1 2 3",
        };
        for (int i = 0; i < tests.length; i++) {
            String got = solve(tests[i]);
            System.out.println((got.equals(expected[i]) ? "OK   " : "FAIL ") + got.replace("\n", " | "));
        }
    }
}
