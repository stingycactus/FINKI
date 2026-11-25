import java.util.Arrays;

public class DeleteDistance {

    static int[][] memo;

    static int solve(String first, String second, int lengthFirst, int lengthSecond) {
        // TODO: base case: first is empty → how many deletions?
        // TODO: base case: second is empty → how many deletions?
        if (lengthFirst == 0) {
            return second.length();
        }
        if (lengthSecond == 0) {
            return lengthFirst;
        }

        // TODO: if memo[lengthFirst][lengthSecond] is filled (!= -1), return it
        if (memo[lengthFirst][lengthSecond] != -1) {
            return memo[lengthFirst][lengthSecond];
        }

        int result;
        if (first.charAt(lengthFirst - 1) == second.charAt(lengthSecond - 1)) {
            // TODO: last letters match
            result = solve(first, second, lengthFirst - 1, lengthSecond - 1);
        } else {
            // TODO: 1 + the smaller of the two deletion options
            int deleteFromFirst = solve(first, second, lengthFirst - 1, lengthSecond);
            int deleteFromSecond = solve(first, second, lengthFirst, lengthSecond - 1);
            result = 1 + Math.min(deleteFromFirst, deleteFromSecond);
        }
        // TODO: store result in memo, then return it
        memo[lengthFirst][lengthSecond] = result;
        return result;
    }

    static int deleteDistance(String first, String second) {
        memo = new int[first.length() + 1][second.length() + 1];
        for (int[] row : memo) Arrays.fill(row, -1);
        return solve(first, second, first.length(), second.length());
    }

    public static void main(String[] args) {
        System.out.println(deleteDistance("sea", "eat"));   // 2
        System.out.println(deleteDistance("ab", "ba"));     // 2
        System.out.println(deleteDistance("abc", "abc"));   // 0
        System.out.println(deleteDistance("abc", "def"));   // 6
        System.out.println(deleteDistance("", "hello"));    // 5
    }
}
