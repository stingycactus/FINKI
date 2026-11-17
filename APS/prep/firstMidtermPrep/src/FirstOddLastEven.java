import aps.*;

import java.util.Scanner;

public class FirstOddLastEven {
    public static void main(String[] args) {
        DLL<Integer> list = new DLL<>();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            list.insertLast(in.nextInt());
        }
        DLLNode<Integer> odd = list.getFirst();
        int oddPos = 0;
        while (odd != null) {
            if (odd.element % 2 != 0){
                break;
            }
            oddPos++;
            odd = odd.succ;
        }
        DLLNode<Integer> even = list.getLast();
        int evenPos = 0;
        while (even!=null) {
            if (even.element % 2 == 0) {
                break;
            }
            evenPos++;
            even = even.pred;
        }
        evenPos = n - 1 - evenPos;
        System.out.println(odd.element + " " + oddPos);
        System.out.println(even.element + " " + evenPos);
        int tmp = odd.element;
        odd.element = even.element;
        even.element = tmp;
        System.out.println(list);
    }
}
