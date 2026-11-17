import aps.LinkedStack;

import java.util.Scanner;

public class RoundBrackets {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        for (int i = 0; i < n; i++) {
            LinkedStack<Character> brackets = new LinkedStack<>();
            String line = in.nextLine();
            boolean valid = true;
            for (int j = 0; j < line.length(); j++) {
                if (line.charAt(j) == '(') {
                    brackets.push('(');
                }
                if (line.charAt(j) == ')') {
                    if (brackets.isEmpty() || brackets.peek() != '(') {
                        valid = false;
                    } else {
                        brackets.pop();
                    }
                }
                if (!valid) {
                    break;
                }
            }
            if (valid && brackets.isEmpty()) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }
}
