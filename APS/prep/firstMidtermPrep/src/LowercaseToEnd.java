import aps.*;

import java.util.Scanner;

public class LowercaseToEnd {
    public static void main(String[] args) {
        SLL<String> list = new SLL<>();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.next());
        }
        System.out.println(list);
        SLLNode<String> curr = list.getFirst();
        for (int i = 0; i < n; i++) {
            SLLNode<String> next = curr.succ;
            if (Character.isLowerCase(curr.element.charAt(0))) {
                list.delete(curr);
                list.insertLast(curr.element);
            }
            curr = next;
        }
        System.out.println(list);
    }
}
