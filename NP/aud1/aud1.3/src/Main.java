import java.util.Scanner;

class Calculator {
    private double result;
    private static final char PLUS = '+';
    private static final char MINUS = '-';
    private static final char MULTIPLY = '*';
    private static final char DIVIDE = '/';

    public Calculator() {
        result = 0;
    }

    public String init() {
        return "result = " + result;
    }

    public double getResult() {
        return result;
    }

    public String execute(char operator, double value) throws UnknownOperatorException {
        if (operator == PLUS) {
            result += value;
        } else if (operator == MINUS) {
            result -= value;
        } else if (operator == MULTIPLY) {
            result *= value;
        } else if (operator == DIVIDE) {
            result /= value;
        } else {
            throw new UnknownOperatorException(operator);
        }
        return "result " + operator + " " + value + " = " + result;
    }

    static class UnknownOperatorException extends Exception {
        public UnknownOperatorException(char operator) {
            super(String.format("%c is an unknown operation.", operator));
        }
    }

    @Override
    public String toString() {
        return "updated result = " + result;
    }
}

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Calculator is on.");
        while (true) {
            Calculator calc = new Calculator();
            System.out.println(calc.init());
            while (true) {
                String line = in.nextLine().trim();
                if (line.isEmpty()) {
                    continue;
                }
                char operator = line.charAt(0);
                if (Character.toLowerCase(operator) == 'r') {
                    System.out.println("Final result = " + calc.getResult());
                    break;
                }
                double value = Double.parseDouble(line.substring(1).trim());
                try {
                    System.out.println(calc.execute(operator, value));
                    System.out.println(calc);
                } catch (Calculator.UnknownOperatorException e) {
                    System.out.println(e.getMessage());
                    System.out.println("Reenter, your last line:");
                }
            }
            System.out.println("Again? (y/n)");
            String answer = in.nextLine().trim();
            while (answer.isEmpty()) {
                answer = in.nextLine().trim();
            }
            if (Character.toLowerCase(answer.charAt(0)) == 'n') {
                System.out.println("End of Program");
                break;
            }
        }
    }
}