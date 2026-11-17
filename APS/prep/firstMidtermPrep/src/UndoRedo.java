import aps.LinkedStack;
import java.util.Scanner;

public class UndoRedo {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        LinkedStack<Character> list = new LinkedStack<>();    // what is on the screen
        LinkedStack<Character> undos = new LinkedStack<>();   // what was undone

        for (int i = 0; i < n; i++) {
            String type = in.next();
            if (type.equals("TYPE")) {
                list.push(in.next().charAt(0));
                undos.clear();                                  // new typing kills redo
            } else if (type.equals("UNDO")) {
                if (!list.isEmpty()) undos.push(list.pop());
            } else if (type.equals("REDO")) {
                if (!undos.isEmpty()) list.push(undos.pop());
            } else {                                            // SHOW
                if (list.isEmpty()) {
                    System.out.println("empty");
                } else {
                    LinkedStack<Character> tmp = new LinkedStack<>();
                    while (!list.isEmpty()) tmp.push(list.pop());   // reverse: oldest ends on top
                    StringBuilder sb = new StringBuilder();
                    while (!tmp.isEmpty()) {
                        char c = tmp.pop();
                        sb.append(c);       // print oldest first
                        list.push(c);       // and put it back, so the text isn't lost
                    }
                    System.out.println(sb);
                }
            }
        }
    }
}