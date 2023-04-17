import java.util.Random;

public class Main {


    public static int hundred = 100,thousand=1000,tenThousand=10000;
    public static int mod=100;

    public static void main(String[] args) {

        driverFunction();
    }

    public static void driverFunction(){

        Random rd = new Random(); // creating Random object
        Integer[][] arrMerg1= new Integer[thousand][hundred];
        Integer[][] arrQuick1= new Integer[thousand][hundred];
        int[][] arrNew1 = new int[thousand][hundred];

        Integer[][] arrMerg2= new Integer[thousand][thousand];
        Integer[][] arrQuick2= new Integer[thousand][thousand];
        int[][] arrNew2 = new int[thousand][thousand];

        Integer[][] arrMerg3= new Integer[thousand][tenThousand];
        Integer[][] arrQuick3= new Integer[thousand][tenThousand];
        int[][] arrNew3 = new int[thousand][tenThousand];


        for (int i = 0; i < thousand; i++) {
            for (int j=0;j<hundred;j++) {
                arrMerg1[i][j] = rd.nextInt() %mod;
                arrQuick1[i][j] = rd.nextInt() %mod;
                arrNew1[i][j] = rd.nextInt()  %mod;
            }
        }
        for (int i = 0; i < thousand; i++) {
            for (int j=0;j<thousand;j++) {
                arrMerg2[i][j] = rd.nextInt() %mod;
                arrQuick2[i][j] = rd.nextInt() %mod;
                arrNew2[i][j] = rd.nextInt() %mod;
            }
        }
        for (int i = 0; i < thousand; i++) {
            for (int j=0;j<tenThousand;j++) {
                arrMerg3[i][j] = rd.nextInt() %mod;
                arrQuick3[i][j] = rd.nextInt() %mod;
                arrNew3[i][j] = rd.nextInt() %mod;
            }
        }

        //hundred
        for (int i = 0; i < thousand; i++) {
            MergeSort.mergeSort(arrMerg1[i],hundred);
        }
        for (int i = 0; i < thousand; i++) {
            QuickSort.quickSort(arrQuick1[i],0,hundred-1);
        }
        for (int i = 0; i < thousand; i++) {
            NewSort.new_sort(arrNew1[i],0,hundred-1);
            NewSort.count=0;

        }

        //thousand

        for (int i = 0; i < thousand; i++) {
            MergeSort.mergeSort(arrMerg2[i],thousand);
        }
        for (int i = 0; i < thousand; i++) {
            QuickSort.quickSort(arrQuick2[i],0,thousand-1);
        }
        for (int i = 0; i < thousand; i++) {
            NewSort.new_sort(arrNew2[i],0,thousand-1);
            NewSort.count=0;

        }

        //ten thousand
        /*for (int i = 0; i < thousand; i++) {
            MergeSort.mergeSort(arrMerg3[i],tenThousand);
        }
        for (int i = 0; i < thousand; i++) {
            QuickSort.quickSort(arrQuick3[i],0,tenThousand-1);
        }
        for (int i = 0; i < thousand; i++) {
            NewSort.new_sort(arrNew3[i],0,tenThousand-1);
            NewSort.count=0;


        }*/


        for (int i = 0; i < thousand; i++) {
            System.out.print(i+1 +"th" + " array: ");
            for (int j=0;j<hundred;j++) {
                System.out.print(arrMerg1[i][j] + " ");
            }
            System.out.print("\n");
        }
    }
}