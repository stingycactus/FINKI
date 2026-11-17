import java.util.Scanner;

public class BusTickets {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();

        int max = (m+n-1) * 100;
        int min = Math.max(n, m) * 100;
    }
}
