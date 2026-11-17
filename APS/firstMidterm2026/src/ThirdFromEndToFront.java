import aps.*;

/*
 * Entry task (termin 2, group B): DLL of N integers + value X. Work from the end to the start.
 * If X appears at least 3 times: find the 3rd X counting from the END.
 * Every element after it is moved to the front, in the order you meet them
 * walking from the end (so that part comes out reversed). The 3rd X itself stays.
 * Print the original list, then the new list.
 * If X appears fewer than 3 times, only a message is printed.
 */
public class ThirdFromEndToFront {

    static void solve(int[] values, int x) {
        DLL<Integer> list = new DLL<>();
        for (int v : values) list.insertLast(v);

        // 1. walk backwards from the last node and stop on the 3rd X
        DLLNode<Integer> third = null;
        int count = 0;
        for (DLLNode<Integer> p = list.getLast(); p != null; p = p.pred) {
            if (p.element == x) {
                count++;
                if (count == 3) {
                    third = p;
                    break;
                }
            }
        }

        if (third == null) {                         // fewer than 3: only the message
            System.out.println("Node so vrednost " + x + " ne se pojavuva barem 3 pati.");
            return;
        }

        System.out.println(list);                    // the original list

        // 2. take nodes from the END until the 3rd X is last; put them at the front
        //    in the order they come off (the first one at the very front, the next after it, ...)
        DLLNode<Integer> lastMoved = null;
        while (list.getLast() != third) {
            int v = list.deleteLast();
            if (lastMoved == null) {
                list.insertFirst(v);
                lastMoved = list.getFirst();
            } else {
                list.insertAfter(v, lastMoved);
                lastMoved = lastMoved.succ;
            }
        }
        System.out.println(list);                    // the new list
    }

    public static void main(String[] args) {
        int[][] lists = {
                {1, 2, 2, 4, 2, 5},
                {2, 9, 2, 8, 2},
                {2, 2, 2},
                {1, 2, 3, 2},
        };
        int[] xs = {2, 2, 2, 2};
        String[] expected = {
                "1<->2<->2<->4<->2<->5\n5<->2<->4<->2<->1<->2",
                "2<->9<->2<->8<->2\n2<->8<->2<->9<->2",
                "2<->2<->2\n2<->2<->2",
                "Node so vrednost 2 ne se pojavuva barem 3 pati.",
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
