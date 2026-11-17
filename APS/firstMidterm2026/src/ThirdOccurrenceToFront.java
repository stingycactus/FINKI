import aps.*;

/*
 * Entry task (termin 1, group A): SLL + value x.
 * If x appears at least 3 times, every element AFTER the 3rd x is moved
 * to the front of the list with insertFirst, one by one.
 * Otherwise print that there aren't 3 nodes with value x.
 */
public class ThirdOccurrenceToFront {

    static String solve(int[] values, int x) {
        SLL<Integer> list = new SLL<>();
        for (int v : values) list.insertLast(v);

        // 1. walk the list and stop on the 3rd x
        SLLNode<Integer> third = null;
        int count = 0;
        for (SLLNode<Integer> p = list.getFirst(); p != null; p = p.succ) {
            if (p.element == x) {
                count++;
                if (count == 3) {
                    third = p;
                    break;
                }
            }
        }
        if (third == null) {
            return "Nema 3 jazli so vrednost " + x;
        }

        // 2. skip the 3rd x itself: start from the node right after it
        SLLNode<Integer> curr = third.succ;

        // 3. move every node from here to the end to the front
        while (curr != null) {
            SLLNode<Integer> next = curr.succ;   // save before deleting
            list.delete(curr);
            list.insertFirst(curr.element);
            curr = next;
        }
        return list.toString();
    }

    public static void main(String[] args) {
        int[][] lists = {
                {5, 3, 1, 3, 2, 3, 7, 8},
                {3, 3, 3, 1, 2},
                {1, 3, 2, 3},
                {4, 4, 4},
        };
        int[] xs = {3, 3, 3, 4};
        String[] expected = {
                "8->7->5->3->1->3->2->3",
                "2->1->3->3->3",
                "Nema 3 jazli so vrednost 3",
                "4->4->4",
        };
        for (int i = 0; i < lists.length; i++) {
            String got = solve(lists[i], xs[i]);
            System.out.println((got.equals(expected[i]) ? "OK   " : "FAIL ") + got);
        }
    }
}
