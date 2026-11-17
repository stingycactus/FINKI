import aps.*;

import java.util.Scanner;

public class FirstMaxLastMin {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        DLL<Integer> list = new DLL<>();
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.nextInt());
        }
        int max = Integer.MIN_VALUE;
        int min = Integer.MAX_VALUE;
        DLLNode<Integer> p = list.getFirst();
        while (p!=null) {
            int x = p.element;
            max = Math.max(x, max);
            min = Math.min(x, min);
            p = p.succ;
        }
        DLLNode<Integer> maxNode = null;
        DLLNode<Integer> minNode = null;
        p = list.getFirst();
        int maxPos = -1;
        int minPos = -1;
        int count = 0;
        while (p!=null) {
            int x = p.element;
            if (maxNode == null && x == max) {
                maxNode = p;
                maxPos = count;
            } else if (x == min) {
                minNode = p;
                minPos = count;
            }
            count++;
            p = p.succ;
        }
        System.out.printf("%d %d%n", max, maxPos);
        System.out.printf("%d %d%n", min, minPos);

        list.insertAfter(min, maxNode);
        list.delete(maxNode);
        list.insertAfter(max, minNode);
        list.delete(minNode);
        System.out.println(list);
    }
}
