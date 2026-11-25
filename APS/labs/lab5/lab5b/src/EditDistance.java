import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class EditDistance {

    static int[][] memo;

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String first = reader.readLine();
        String second = reader.readLine();
        if (first == null) first = "";
        if (second == null) second = "";
        first = first.trim();
        second = second.trim();
        System.out.println(editDistance(first, second));
    }

    private static int solve(String first, String second, int lengthFirst, int lengthSecond) {
        if (lengthFirst == 0) {
            return lengthSecond;
        }
        if (lengthSecond == 0) {
            return lengthFirst;
        }
        if (memo[lengthFirst][lengthSecond] != -1) {
            return memo[lengthFirst][lengthSecond];
        }
        int result;
        if (first.charAt(lengthFirst-1) == second.charAt(lengthSecond-1)) {
            result = solve(first, second, lengthFirst-1, lengthSecond-1);
        } else {
            int delete  = 1 + solve(first, second, lengthFirst - 1, lengthSecond);
            int insert  = 1 + solve(first, second, lengthFirst, lengthSecond - 1);
            int replace = 1 + solve(first, second, lengthFirst - 1, lengthSecond - 1);
            result = Math.min(delete, Math.min(insert, replace));
        }
        memo[lengthFirst][lengthSecond] = result;
        return result;
    }

    private static int editDistance(String first, String second) {
        memo = new int[first.length() + 1][second.length() + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        return solve(first, second, first.length(), second.length());
    }
}