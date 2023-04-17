public class MergeSort {

    /**
     *
     * @param array unsorted array
     * @param arrayLength array length
     */
    public static void mergeSort(Integer[] array, int arrayLength) {
        if (arrayLength < 2) {
            return;
        }
        int j=0;
        int mid = arrayLength / 2;
        Integer[] leftArray = new Integer[mid];
        Integer[] rightArray = new Integer[arrayLength - mid];

        for (int i = 0; i < mid; i++) {
            leftArray[i] = array[i];
        }
        for (int i = mid; i < arrayLength; i++) {
            rightArray[j] = array[i];
            j++;
        }
        mergeSort(leftArray, mid);
        mergeSort(rightArray, arrayLength - mid);

        merge(array, leftArray, rightArray);
    }

    /**
     *
     * @param arr big array
     * @param leftArray small left array
     * @param rightArray small right array
     */
    public static void merge(
            Integer[] arr, Integer[] leftArray, Integer[] rightArray){

        int i = 0,
                j = 0,
                k = 0;
        while (i < leftArray.length && j < rightArray.length) {
            if (leftArray[i].compareTo(rightArray[j]) <=0) {
                arr[k] = leftArray[i];
                k++;
                i++;
            }
            else {
                arr[k] = rightArray[j];
                k++;
                j++;
            }
        }
        while (i < leftArray.length) {
            arr[k] = leftArray[i];
            k++;
            i++;
        }
        while (j < rightArray.length) {
            arr[k] = rightArray[j];
            k++;
            j++;
        }
    }
}
