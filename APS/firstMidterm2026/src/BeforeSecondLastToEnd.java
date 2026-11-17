import aps.*;

/*
 * Entry task (termin 2, group A): DLL of N integers + value X.
 * If X appears fewer than 2 times, print only:
 *     Node so vrednost X ne se pojavuva barem 2 pati.
 * Otherwise print the original list, then (on a new line) the list where every
 * element BEFORE the second-to-last occurrence of X (not that X node itself)
 * is moved to the end of the list, keeping their order.
 */
public class BeforeSecondLastToEnd {

    static void solve(int[] values, int x) {
        DLL<Integer> list = new DLL<>();
        for (int v : values) list.insertLast(v);

        // walk backwards from the last node: the 2nd X we meet is the second-to-last occurrence
        DLLNode<Integer> target = null;
        int count = 0;
        for (DLLNode<Integer> p = list.getLast(); p != null; p = p.pred) {
            if (p.element == x) {
                count++;
                if (count == 2) {
                    target = p;
                    break;
                }
            }
        }
        if (target == null) {
            System.out.println("Node so vrednost " + x + " ne se pojavuva barem 2 pati.");
            return;
        }

        System.out.println(list);          // the original list, before any changes

        // move everything in front of target to the end, in order
        while (list.getFirst() != target) {
            int v = list.deleteFirst();
            list.insertLast(v);
        }
        System.out.println(list);          // the transformed list
    }

    public static void main(String[] args) {
        int[][] lists = {
                {1, 2, 3, 2, 4, 2, 5},
                {5, 7, 7},
                {7, 1, 7, 9},
                {1, 2, 3},
        };
        int[] xs = {2, 7, 7, 2};
        String[] expected = {
                "1<->2<->3<->2<->4<->2<->5\n2<->4<->2<->5<->1<->2<->3",
                "5<->7<->7\n7<->7<->5",
                "7<->1<->7<->9\n7<->1<->7<->9",
                "Node so vrednost 2 ne se pojavuva barem 2 pati.",
        };
        for (int i = 0; i < lists.length; i++) {
            System.out.println("--- test " + (i + 1) + ", expected:");
            System.out.println(expected[i]);
            System.out.println("--- got:");
            solve(lists[i], xs[i]);
            System.out.println();
        }
    }
}
