import aps.LinkedStack;

import java.util.Scanner;

public class BrowserHistory {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        LinkedStack<String> history = new LinkedStack<>();
        for (int i = 0; i < n; i++) {
            String line = in.nextLine();
            String[] parts = line.trim().split("\\s+");
            String cmd = parts[0];
            String site = "";
            if (parts.length == 2) {
                site = parts[1];
            }
            if (cmd.equals("VISIT")){
                history.push(site);
            } else if (cmd.equals("BACK")) {
                if (history.size() <= 1) {
                    continue;
                }
                history.pop();
            } else {
                if (history.isEmpty()) System.out.println("empty");
                else System.out.println(history.peek());
            }
        }
    }
}
