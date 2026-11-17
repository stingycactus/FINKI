import aps.*;

/*
 * Entry task (termin 1, group B): SLL + value x.
 * If x appears fewer than 2 times, the list stays as it is.
 * Otherwise, take elements from the start one by one and move them to the end
 * (insertLast + deleteFirst), until the 2nd x is at the front. The 2nd x stays.
 * Print the list.
 */
public class SecondOccurrenceToEnd {

    static String solve(int[] values, int x) {
        SLL<Integer> list = new SLL<>();
        for (int v : values) list.insertLast(v);

        // 1. count how many times x is in the list
        int count = 0;
        for (SLLNode<Integer> p = list.getFirst(); p != null; p = p.succ) {
            if (p.element == x) count++;
        }

        // 2. at least 2: move elements from the front to the back until the 2nd x is first
        if (count >= 2) {
            int seen = 0;
            SLLNode<Integer> first = list.getFirst();
            while (true) {
                if (first.element == x) {
                    seen++;
                    if (seen == 2) break;          // the 2nd x stays at the front
                }
                list.insertLast(first.element);    // copy the front element to the back
                list.deleteFirst();                // remove it from the front
                first = list.getFirst();           // the new first node
            }
        }
        return list.toString();
    }

    public static void main(String[] args) {
        int[][] lists = {
                {1, 5, 2, 5, 3, 4},
                {5, 5, 9},
                {1, 2, 5, 3},
                {7, 5, 8, 5, 5, 6},
        };
        int[] xs = {5, 5, 5, 5};
        String[] expected = {
                "5->3->4->1->5->2",
                "5->9->5",
                "1->2->5->3",
                "5->5->6->7->5->8",
        };
        for (int i = 0; i < lists.length; i++) {
            String got = solve(lists[i], xs[i]);
            System.out.println((got.equals(expected[i]) ? "OK   " : "FAIL ") + got);
        }
    }
}
