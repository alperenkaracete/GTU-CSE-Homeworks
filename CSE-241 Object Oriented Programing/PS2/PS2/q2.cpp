#include <iostream>
#include <cstdlib>

const int INT_MAX=20; /*Max digit number*/

int turning_number_int (char c_number[INT_MAX+1],int number[INT_MAX]); /*Turn char number to integer and gets its digit, If value not integer returns error*/
int addition (int num1[INT_MAX],int num1_digit,int num2[INT_MAX],int num2_digit,int sum[INT_MAX],int &sum_digit); /*Calculates sum of numbers */ 

using namespace std;

int main(){

    char c_first_number[INT_MAX+1], /*First char number*/
    c_second_number[INT_MAX+1]; /*Second char number*/

    int first_number[INT_MAX],/*First int number*/
    second_number[INT_MAX],/*Secon int number*/
    sum_number[INT_MAX], /*Sum number*/
    i=0, /*For loops*/
    j=0, /*For loops*/
    first_num_digit, /*First numbers digit*/
    second_num_digit, /*Second numbers digit*/
    sum_digit, /*Sum numbers digit*/
    overflow, /*If there is an overflow controls*/
    control=1; /*For loop if control 1 continues working*/

    do { /*First takes two number converts them to int and sum them.Then takes one number add it to sum until user enters 2 or wrong input*/

        cout << "Please enter a number" << endl;
        cin >> c_first_number; /*Takes first number*/
        first_num_digit=turning_number_int (c_first_number,first_number); /*Controls and converts first number to integer*/
        if (first_num_digit==21){ /*If entry not integer prints error code*/

            cout << "Wrong entry!" << endl;
            control=2; /*For succesfully exit makes control 2*/
        }

        if (control!=2){ /*If second number still not entered takes second number, then never takes second number again*/
        
            if (first_num_digit!=21) {
                cout << "Please enter second number" << endl;
                cin >> c_second_number; /*Takes second number*/
                second_num_digit=turning_number_int(c_second_number,second_number); /*Takes second number and controls*/

            }

            if (second_num_digit==21){ /*If value not integer prints error */

                cout << "Wrong entry!" << endl;
                control=2; /*For end the loop if there is something wrong*/
            }

            else if (second_num_digit!=21 && first_num_digit!=21){ /*Make addition dirst and second number if two values are true and controls if there is a overflow*/
                if (first_num_digit>second_num_digit){ /*If first digit is bigger than second calls function with that values*/
                    overflow=addition (first_number,first_num_digit,second_number,second_num_digit,sum_number,sum_digit);
                }

                else { /*Else calls function like that*/
                    overflow=addition (second_number,second_num_digit,first_number,first_num_digit,sum_number,sum_digit);           
                }
            }
        }
        if (overflow==1 && first_num_digit!=21 && second_num_digit!=21){ /*If there is an overflow prints that*/

            cout << "Integer overflow" << endl;
            control=2; /*Exit loop if there is overflow*/
        }

        else if ((overflow==0 && first_num_digit!=21 && second_num_digit!=21) || sum_digit==1){ /*If there is not overflow and entries are true, prints sum value*/
            cout << "Result: ";
            for (i=sum_digit-1;i>=0;i--){
                cout << sum_number[i] ;
            }
            cout << endl;        
        }
        if (control!=2) { /*Controls is user want to continue or not*/
            cout << "Do you want to continue press 1 for exit press 2" << endl;
            cin >> control;

        }
       
    }while (control==1); /*Continues loop until user enter 2 or wrong entry*/
    
    if (control!=2){  /* If user enter not enter 1 or 2 prints error message*/

        cout << "Wrong input" << endl;
    }
}

int turning_number_int (char c_number[INT_MAX+1],int number[INT_MAX]){ /*Takes number and makes them integer, if they are not integer returns 21*/

    int i=0, /*For loops*/
    j=0, /* For loops*/
    digit=0, /* Digit number*/
    control,
    count=0; /* Controls if number digit or not*/

    char temp;

    while (c_number[i]!='\0' && i<=INT_MAX){ /*Calculates number digit and controls if entry is number or not*/
    
        if (c_number[i+1]=='\0'){

            count++;
        }

        temp=c_number[i];
        control=isdigit (temp);
        if (control==0){

            return 21;
        }
        i++;
    }

    if (count!=0){
        digit=i; /*Digit number*/
        for (i=digit-1;i>=0;i--){ /*Inverse the number*/
            number[j]=c_number[i]-'0'; /*Turns char to int*/
            j++;
        }
    }

    else if (count==0) {

        digit=21;
    }
    return digit;

}

int addition (int num1[INT_MAX],int num1_digit,int num2[INT_MAX],int num2_digit,int sum[INT_MAX],int &sum_digit){ /*Addition part*/

    int temp_sum, /*Temp sum value for control if sum greater or equal to 10*/
    count=0, /*If sum is greater or equal to 10 increases count, if count bigger than zero add i+1's sum value one for addition operation*/
    i=0; /*For loop*/

    if (num1_digit>num2_digit){ /*Makes sum operation*/

        for (i=0;i<num1_digit;i++){

            if (i<num2_digit && count==0){ /*Starts from first digit and add values, if sum is not bigger than or equal to 10 direct add them, else increases count */

                temp_sum=num1[i]+num2[i];

                if (temp_sum>=10){

                    sum[i]=temp_sum%10;
                    count++;
                }

                else {

                    sum[i]=temp_sum;
                    count=0;
                }
            }

            else if (i<num2_digit && count!=0){ /*If count not zero add value to 1*/

                temp_sum=num1[i]+num2[i]+1;

                if (temp_sum>=10){

                    sum[i]=temp_sum%10;
                    count++;
                }

                else {

                    sum[i]=temp_sum;
                    count=0;
                }
            }

            else if (i<num1_digit && i>=num2_digit){ /*If num2 is not longer enough num1 if there is not count don't changes anything, but if there is count increments num1's other digits one*/
                if (count!=0){

                    temp_sum=num1[i]+1;
                    count=0;
                }

                else {

                    temp_sum=num1[i];
                    count=0;
                }

                if (temp_sum>=10){

                    sum[i]=temp_sum%10;
                    count++;
                }

                else {

                    sum[i]=temp_sum;
                }

                if (i==num1_digit-1 && count!=0 && num1[i]==9){ /*If number is for example 999 and count isn't zero, ads this number 1 and makes it 1000 its digit increment one*/

                    sum_digit=num1_digit+1;
                    sum[i+1]=1;
                }

                else {

                    sum_digit=num1_digit;
                }
            }
        }
    }

    else { /*If numbers are equal enter this part*/
        for (i=0;i<num1_digit;i++){

            if (count!=0){ /*If count not zero add sum value 1*/

                temp_sum=num1[i]+num2[i]+1;
                if (temp_sum>=10){ /*If sum value bigger or equal to 10 increment count*/

                    sum[i]=temp_sum%10;
                    count++;
                }

                else {

                    sum[i]=temp_sum;
                    count=0;     
                }

            }

            else {

                temp_sum=num1[i]+num2[i];
                
                if (temp_sum>=10){

                    sum[i]=temp_sum%10;
                    count++;
                }

                else {

                    sum[i]=temp_sum;
                    count=0;
                }
            }
            if (i==num1_digit-1 && count!=0){

                sum[i+1]=1;
                sum_digit=num1_digit+1;
            }

            else {

                sum_digit=num1_digit;
            }
        }
    }
    if (sum_digit>INT_MAX){ /*If there is overflow returns 1*/

        return 1;
    }

    else { /* Else return 0*/

        return 0;
    }
}