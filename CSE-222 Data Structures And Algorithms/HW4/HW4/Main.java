import java.util.Arrays;

public class Main {

    public static void main(String[] args) {

        driverFunction();
    }

    /**
     *
     * @param longString big string
     * @param shortString small string
     * @param count occurrence
     * @return return ith occurrence if there is else return -1
     */
    public static String recursiveFind(String longString, String shortString, int count) { //find ith occurrence of shortening

        if (longString.length() < shortString.length()) {
            if (count != 0) {
                return "-1";
            }
        } else {
            String temp = longString.substring(0, shortString.length());
            if (temp.equals(shortString)) {
                count--;
            }
            if (count == 0) {
                return longString;
            }
        }
        return recursiveFind(longString.substring(1), shortString, count); //make a copy of array between second element and last element.
    }

    /**
     *
     * @param sortedArray sorted int array
     * @param num1 number1
     * @param num2 number 2
     * @return 1
     */
    public static int findNumbersBetween(int[] sortedArray, int num1, int num2) {

        int arrayLong = sortedArray.length,
                mid = sortedArray[arrayLong / 2]; //evaluate mid value

        if (sortedArray[0] >= num1 && sortedArray[0] >= num2 || sortedArray.length == 1) {

            System.out.println(sortedArray[0]);
            return 1;
        } else if (num1 > mid && num2 > mid) { //looks if numbers bigger than mid value, if it's look bigger side of array

            return findNumbersBetween(Arrays.copyOfRange(sortedArray, arrayLong / 2+1, arrayLong), num1, num2);

        } else if (num1 < mid && num2 < mid) { //looks if numbers smaller than mid value, if it's look small side of array

            return findNumbersBetween(Arrays.copyOfRange(sortedArray, 1, arrayLong / 2+1), num1, num2);
        } else if (sortedArray[0] <= num1 && sortedArray[0] >= num2 || sortedArray[0] >= num1 && sortedArray[0] <= num2) {

            System.out.print(sortedArray[0] + " ");
        }
        return findNumbersBetween(Arrays.copyOfRange(sortedArray, 1, arrayLong), num1, num2); //make copy srcond element to last element
    }

    /**
     *
     * @param unsortedArray unsorted integer array
     * @param tempArray temp array for storing values
     * @param number number for look sum
     * @param i for looking arrays elements
     * @param sum value for store temp
     * @return 1
     */
    public static int findSumNumber(int[] unsortedArray, int[] tempArray, int number, int i, int sum){

        if (unsortedArray.length==0 || i==unsortedArray.length){

            return 1;
        }

        tempArray[i]=unsortedArray[i];
        sum+=tempArray[i];
        if (sum==number){ //if sum == number then subarray is correct

            for (int j=0;j<=i;j++){ //for printing array

                System.out.print(tempArray[j] + " ");
            }
            System.out.print('\n');
        }

        else if (sum>number){ //if sum bigger than number subarray incorrect

            sum=0;
            Arrays.fill(tempArray,0);
            i=0;
            return findSumNumber(Arrays.copyOfRange(unsortedArray, 1, unsortedArray.length),tempArray,number,i,sum);
        }
        return findSumNumber(unsortedArray,tempArray,number,i+1,sum);
    }

    /**
     *
     * @param emptyArray array with fill '-'
     * @param length length start for block
     * @param position takes position in array
     * @param startPosition start position of '*'
     * @return 1
     */
    public static int coloredBlocks1D(char[] emptyArray,int length,int position,int startPosition){

        if (length> emptyArray.length){
            return 1;
        }
        else if (startPosition+length<= emptyArray.length && position<length){

            emptyArray[startPosition + position] = '*'; //print start position to position '*'
            return coloredBlocks1D(emptyArray,length,position+1,startPosition);
        }
        else if (position==length && startPosition+length<=emptyArray.length){

            for (int j=0;j<emptyArray.length;j++){

                System.out.print(emptyArray[j]);
            }
            System.out.print('\n');
            Arrays.fill(emptyArray,'-');
            position=0;
            return coloredBlocks1D(emptyArray,length,0,startPosition+1);
        }

        if (emptyArray.length/length>1 && startPosition== emptyArray.length-length+1 && position<emptyArray.length && length!=emptyArray.length-1){ //this prints for multiple * and spaces

            if (position<length || position>length && position%(length+1)!=length && (position%(length+1)!=0 || position+length<=emptyArray.length)){
                emptyArray[position] = '*';

            }
            else if (position%(length+1)==length){

                emptyArray[position] = '-';
            }
            return coloredBlocks1D(emptyArray,length,position+1,startPosition); //increase position one to place * again
        }
        if (startPosition== emptyArray.length-length+1 && length<=emptyArray.length/2 && emptyArray.length/2>1){
            for (int j=0;j<emptyArray.length;j++){

                System.out.print(emptyArray[j]); //print array
            }
            System.out.print('\n');
        }
        position=0;
        startPosition=0;
        Arrays.fill(emptyArray,'-');
        return coloredBlocks1D(emptyArray,length+1,position,startPosition); //increase length one to try for other lengths
    }

    /**
     * driver function make thins itself.
     */
    public  static void driverFunction(){

        String longString = "abcabacabcaabc", shortString = "abc";
        String value;
        int count = 2;
        value = recursiveFind(longString, shortString, count);
        System.out.println("Program found this string for part1");
        System.out.println(value);

        int[] sortedArray = {1, 3, 4, 5, 7, 9, 11, 12, 13, 14};
        System.out.println("Program found this values for part2");
        findNumbersBetween(sortedArray, 9, 14);

        int[] unsortedArray = {5,6,8,1,4,5,7,9,1,3,0,8,13};
        int[] tempArray = new int[unsortedArray.length];
        System.out.println("Program found this values for part3");
        findSumNumber(unsortedArray,tempArray,13,0,0);

        int length=11;
        char[] emptyArray = new char[length];
        Arrays.fill(emptyArray,'-');
        System.out.println("Program found this values for part5");
        coloredBlocks1D(emptyArray,3,0,0);
    }
}
