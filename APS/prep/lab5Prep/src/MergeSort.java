import java.util.Arrays;

public class MergeSort {

    private static void mergeSort(int[] array) {
        int length = array.length;
        if (length <= 1) {
            return;
        }
        int middle = length / 2;
        int[] leftArray = Arrays.copyOfRange(array, 0, middle);
        int[] rightArray = Arrays.copyOfRange(array, middle, length);
        mergeSort(leftArray);
        mergeSort(rightArray);
        merge(leftArray, rightArray, array);
    }

    private static void merge(int[] leftArray, int[] rightArray, int[] array) {
        int arrayIndex = 0;
        int leftIndex = 0;
        int rightIndex = 0;

        while (leftIndex < leftArray.length && rightIndex < rightArray.length) {
            if (leftArray[leftIndex] <= rightArray[rightIndex]) {
                array[arrayIndex] = leftArray[leftIndex];
                arrayIndex++;
                leftIndex++;
            } else {
                array[arrayIndex] = rightArray[rightIndex];
                arrayIndex++;
                rightIndex++;
            }
        }

        while (leftIndex < leftArray.length) {
            array[arrayIndex] = leftArray[leftIndex];
            arrayIndex++;
            leftIndex++;
        }
        while (rightIndex < rightArray.length) {
            array[arrayIndex] = rightArray[rightIndex];
            arrayIndex++;
            rightIndex++;
        }
    }

    public static void main(String[] args) {
        int[] array = {8, 2, 4, 9, 3, 6, 7, 5};
        mergeSort(array);
        System.out.println(Arrays.toString(array));   // [2, 3, 4, 5, 6, 7, 8, 9]

        int[] reversed = {5, 4, 3, 2, 1};
        mergeSort(reversed);
        System.out.println(Arrays.toString(reversed)); // [1, 2, 3, 4, 5]
    }
}