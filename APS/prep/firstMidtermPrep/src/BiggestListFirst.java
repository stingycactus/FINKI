import aps.*;

import java.util.Scanner;

public class BiggestListFirst {
    public static void main(String[] args) {
        DLL<DLL<Integer>> outer = new DLL<>();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            int k = in.nextInt();
            DLL<Integer> inner = new DLL<>();
            for (int j = 0; j < k; j++) {
                inner.insertLast(in.nextInt());
            }
            outer.insertLast(inner);
        }

        DLLNode<DLL<Integer>> o = outer.getFirst();

        int bestSum = Integer.MIN_VALUE;
        DLLNode<DLL<Integer>> best = null;
        while (o!=null) {
            int sum = 0;
            DLL<Integer> inner = o.element;
            DLLNode<Integer> x = inner.getFirst();
            while (x!=null) {
                sum+=x.element;
                x = x.succ;
            }
            if (sum>bestSum) {
                bestSum = sum;
                best = o;
            }
            o = o.succ;
        }

        outer.delete(best);
        outer.insertFirst(best.element);

        DLLNode<DLL<Integer>> p = outer.getFirst();
        while (p!=null) {
            System.out.println(p);
            p = p.succ;
        }
    }
}
