import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class RankInversions
{
    /**
     * Counts the pairs of students whose relative order changed between
     * the two ranking lists.
     *
     * @param ranks ranks[i] is the first-midterm rank of the student at
     *              position i on the second-midterm ranking list
     * @return the number of pairs (i, j), i &lt; j, with ranks[i] &gt; ranks[j]
     */
    public static long countSwappedPairs(int[] ranks)
    {
        long count = 0;
        int length = ranks.length;
        if (length <= 1) {
            return 0;
        }
        int middle = length / 2;
        int[] leftArray = Arrays.copyOfRange(ranks, 0, middle);
        int[] rightArray = Arrays.copyOfRange(ranks, middle, length);
        count+=countSwappedPairs(leftArray);
        count+=countSwappedPairs(rightArray);
        count+=merge(leftArray,rightArray,ranks);
        return count;
    }

    public static long merge(int[] leftArray, int[] rightArray, int[] array) {
        int arrayIndex = 0;
        int leftIndex = 0;
        int rightIndex = 0;

        long count = 0;
        while (leftIndex < leftArray.length && rightIndex < rightArray.length) {
            if (leftArray[leftIndex] <= rightArray[rightIndex]) {
                array[arrayIndex++] = leftArray[leftIndex++];
            } else {
                array[arrayIndex++] = rightArray[rightIndex++];
                count += leftArray.length - leftIndex;
            }
        }

        while (leftIndex < leftArray.length) {
            array[arrayIndex++] = leftArray[leftIndex++];
        }
        while (rightIndex < rightArray.length) {
            array[arrayIndex++] = rightArray[rightIndex++];
        }
        return count;
    }

    public static void main(String[] args) throws IOException
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine().trim());
        int[] ranks = new int[n];
        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i = 0; i < n; i++)
        {
            ranks[i] = Integer.parseInt(st.nextToken());
        }

        System.out.println(countSwappedPairs(ranks));
    }
}
