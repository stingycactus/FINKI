import aps.*;

import java.util.Scanner;

public class FirstEvenLastOdd {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        DLL<Integer> list = new DLL<>();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.nextInt());
        }
        DLLNode<Integer> even = list.getFirst();
        int evenPos = 0;
        while (even!=null) {
            if (even.element % 2 == 0) {
                break;
            }
            evenPos++;
            even = even.succ;
        }
        DLLNode<Integer> odd = list.getLast();
        int oddPos = 0;
        while (odd!=null) {
            if (odd.element % 2 != 0) {
                break;
            }
            oddPos++;
            odd=odd.pred;
        }
        oddPos = n - 1 - oddPos;
        System.out.printf("%s, %d | %s, %d%n", even, evenPos, odd, oddPos);
//        int temp = even.element;
//        even.element = odd.element;
//        odd.element = temp;
        list.insertAfter(odd.element, even);
        list.insertAfter(even.element, odd);
        list.delete(even);
        list.delete(odd);
        System.out.println(list);
    }
}
