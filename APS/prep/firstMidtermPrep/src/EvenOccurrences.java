import aps.*;

import java.util.Scanner;

public class EvenOccurrences {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        SLL<Integer> list = new SLL<>();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.nextInt());
        }
        int value = in.nextInt();
        SLLNode<Integer> curr = list.getFirst();
        int count = 0;
        while (curr!= null) {
            if (curr.element == value) {
                count++;
            }
            curr = curr.succ;
        }
        if (count % 2 != 0) {
            list.insertBefore(value, list.find(value));
        }
        System.out.println(list);
    }
}
