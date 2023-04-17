import java.util.ArrayList;


public class NewSort {


    static int min=99999,min_indice; // min ivalue and indice
    static int max=-99999,max_indice; //max value and indice
    static ArrayList<Integer> min_max = new ArrayList<>(); //arraylist that stores min indice and max indice
    static int count=0; //hides information that head increment how many times and tail decrement how many times,with that recursion can work truely.

    /**
     *
     * @param array unsorted array
     * @param head head of array
     * @param tail end of array
     * @return sorted array
     */
    public static int[] new_sort (int[] array,int head,int tail){

        if (head>tail){

            return array;
        }

        else {

            min_max = min_max_finder(array,head,tail);
            swap(array,head,min_max.get(0));
            swap(array,tail,min_max.get(1));
            return new_sort(array, head + 1, tail -1);

        }
    }

    /**
     *
     * @param array unsorted array
     * @param head start of array
     * @param tail end of array
     * @return returns min and max of array
     */
    public static ArrayList<Integer> min_max_finder(int[] array,int head,int tail){

        if (tail+count==array.length-1 && head-count<tail) {

            min_max_finder(array, head + 1, tail);
            if (min > array[head]) {

                min = array[head];
                min_indice= head;
            }
        }
        else if (tail>=count) {
            min_max_finder(array, head, tail - 1);
            if (max < array[tail]) {

                max = array[tail];
                max_indice=tail;
            }
        }
        if (head-count==0 && tail+count== array.length-1){ /*In last step head-count becomes zero and tail+count becomes (array.length-1) because in recursion
                                                compiler made first inner process.So we can ensure that finding min and max is successful*/

            ArrayList<Integer> temp = new ArrayList<>();
            temp.add(min_indice);
            temp.add(max_indice);
            count++;
            min=99999;
            max=-99999;
            return temp;
        }

        return null;
    }

    /**
     *
     * @param array unsorted array
     * @param startPosition indice we want to swap with indice
     * @param indice indice we want to swap with start position
     */
    public static void swap (int[] array,int startPosition,int indice){

        int temp;
        if (indice == min_indice){

            temp=array[startPosition];
            array[startPosition] = array[indice];
            array[indice] = temp;

        }

        else if (indice == max_indice){

            temp=array[startPosition];
            array[startPosition]=array[indice];
            array[indice] = temp;
        }

    }
}