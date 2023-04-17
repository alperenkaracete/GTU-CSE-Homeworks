public class QuickSort {



    /**
     *
     * @param arr unsorted array
     * @param firstIndex first index of array
     * @param lastIndex last index of array
     */
    public static void quickSort(Integer[] arr, int firstIndex, int lastIndex)
    {
        if (firstIndex < lastIndex)
        {
            /* pivot is partitioning index*/
            int pivot = partition(arr, firstIndex, lastIndex);

            // Recursively sort elements
            quickSort(arr, firstIndex, --pivot);
            quickSort(arr, ++pivot, lastIndex);
        }

    }


    static int partition(Integer[] arr, int firstIndex, int lastIndex)
    {
        int pivot = arr[lastIndex];
        int j = firstIndex; // index of first element
        for (int i=firstIndex; i<lastIndex; i++)
        {
            // If current element is smaller than or equal to pivot
            if (arr[i] <= pivot)
            {

                // swap current element and a[j]
                int tempVal = arr[j];
                arr[j] = arr[i];
                arr[i] = tempVal;
                j++;
            }
        }

        // swap arr[j] and or pivot
        int tempVal = arr[j];
        arr[j] = arr[lastIndex];
        arr[lastIndex] = tempVal;

        return j;
    }

}
