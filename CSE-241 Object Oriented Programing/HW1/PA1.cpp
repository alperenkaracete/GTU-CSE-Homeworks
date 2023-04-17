#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N=9, /*Biggest digit number*/
MAX_NUMBER=987654321; /*Biggest number for game*/

void generate_number (int digit_number,int number[N]); /*Generate random number function*/
int divide_number (char user_number[N],int number[N],int digit_number); /*Converting char number to integer number and stock in integer array*/
int game (char user_number[N],int divided_user_number[N],int digit_number,int number[N],int& gamecount_1); /*Game function*/

int main(int argc,char** argv){

    srand (time(NULL)); 

    int number[N], /*Secret number*/
    digit_number, /*Takes digit number for -r part*/
    i=0, /*For loops*/
    j=0, /*For loops*/
    k=0, /*For loops*/
    divided_user_number[N], /*Stores players number in integer array*/
    control=1, /*Control variable for output parts*/
    u_number, /*Stores -u's secret number as integer*/
    temp, /*Temporary variable for -u parts secret number*/
    count=0, /* Takes -u's secret number digits*/
    gamecount_1=0, /*Calculate total turns*/
    gamecount_2=0, /*First count*/
    gamecount_3=0; /*Second count*/
    
    bool control3=1; /*Controls if after -u there is a repeating number*/

    char user_number[N]; /*Takes players number*/

    if (argc!=3){ /*If parameter not three gives error*/

        cout << "E0" << endl;
    }

    else if (argv[1][0]=='-' && argv[1][1]=='r' && argv[1][2]=='\0' && argv[2][0]<='N'&& argv[2][1]=='\0' && argc==3){ /*For -r part of the game*/

        digit_number=argv[2][0]-'0'; /*Turns digit number from char to integer*/
        generate_number (digit_number,number);  /*Generates random number*/
        control=game (user_number,divided_user_number,digit_number,number,gamecount_1); /*Takes value for console outputs*/

        if (control==2){ /*If entry not an integer gives error*/

            cout << "E2" << endl;  
        }
    }

    else if (argv[1][0]=='-' && argv[1][1]=='u' && argv[1][2]=='\0' && argc==3 && argv[2][0]!='0'){ /* For -u part of the game*/
        
        u_number=atoi(argv[2]); /*Turns char entry to integer number*/
        temp=u_number; /*Copy number to temporary value for finding digit of number*/
        while (temp>10){ /*Find digit of secret number*/

            temp=temp/10;
            count++; /*Takes digit number*/
            }
   
        count++;    

        for (i=0;i<count;i++){ /*Controls is there a reepeating number in -r's secret number*/

            for (j=i+1;j<count;j++){

                if (argv[2][i]==argv[2][j]){

                    control3=0; /*If there is a repeating number then false*/
                }
            }
        } 

        if (control3!=0){ /*If there isn't any repeating number than takes secret number*/

            control=divide_number (argv[2],divided_user_number,count);

            if (control==2 ){ /* If secret entry not integer gives error*/

                cout << "E0" << endl;
            }

            else if (u_number<=MAX_NUMBER && u_number>0 ){ /*Controls if number lower than biggest number and bigger than 0*/

                divide_number (argv[2],number,count); /*Turns char number to integer and stores in number variable*/
                control=game (user_number,divided_user_number,count,number,gamecount_1);/*Sends variables to game function*/
                if (control==2){ /*If entered value not an integer giver error*/

                    cout << "E2" << endl;
                }           
            }
        }    

    }

    if (control==0 && argc==3){ /*If there is a repeating number in entered value gives error*/

        cout << "E1" << endl;
    }

    else if (control==5 && argv[2][0]!='0'){ /*If player wins prints in how many round he/she beated the game*/

        cout << "FOUND" << " " <<gamecount_1 << endl;
    }    

    else if (control==2){ /*For not integer values I printed errors on top side for program dont run else case i put this else if.That error printing on top*/

    }

    else if (gamecount_1==100){ /*If player cannot found number in 100 tries then he/she fails*/

        cout << "FAILED" << endl;
    }    

    else { /*For al other errors*/

        if (argc==3){
            cout << "E0" << endl;
        }
    }

}

void generate_number (int digit_number,int number[N]){ /*Generates random number*/

    int i=0, /*For loops*/
    j=0, /*For loops*/
    temp; /*For calculating entered numbers digits*/

    bool control=1; /*Controls if there is repeat entered number*/

    while (i<digit_number){ /*Creates number until get a unique number*/

        temp=rand()%10;
        if (i==0 && temp==0){

            while (temp==0){

                temp=rand()%10; /*Gets first number*/
            }
        }

        if (i==0){

            number[i]=temp; /*Copies first number to number array*/
        }

        for (j=0;j<i;j++){

            if (number[j]==temp){ /*Controls if there is a repeat in numbers digits.If there is a repeat makes control 0*/

                control=0;
                j=i;
            }

            else { /* If there is no repeat copies that digit to number*/

                number[i]=temp;
                control=1;
            }
        }

        if (control==1){ /*If there is no repeat digit succesfully copied to number array so increment i and get new digit*/

            i++;
        }
    }
}

int divide_number (char user_number[N],int divided_user_number[N],int digit_number){ /*Takes char array and converts it integer array.Divides it it's digits and save them in divided_user_number array*/

    int i=0, /*For loops*/
    j=0, /*For loops*/
    count=0,/*Finds entered values digits*/
    temp, /*Stores entered value as integer with atoi function*/
    temp2, /*Controls digit if its integer*/
    control,
    warning=0;/*If value not integer gives warning for output*/

    temp=atoi(user_number);

    while (user_number[i]!='\0'){

        temp2=isdigit(user_number[i]); /*Controls if value is digit or not*/
        i++;
        count++;
        if (temp2==0){ /*COntrols value integer or nor*/

            warning=1;
        }
    }

    if (count==digit_number && warning==0){ /*If secret numbers digit same as entered value and the value is integer copies that number to divided_user_number array*/

        for (i=digit_number-1;i>=0;i--){

            divided_user_number[i]=temp%10;
            temp=temp/10;
        }

        for (i=0;i<digit_number;i++){ /*Controls digits if there is a repeating number*/

            for (j=i+1;j<digit_number;j++){

                if (divided_user_number[i]==divided_user_number[j]){ /*If there is a repeat in entered value gives error*/

                    control=0; /*Return 0 for error code*/
                    return control;
                }
            }
        }        

        return 1; /*If all is well return 1*/
    }

    else if (warning==1){ /* If value not integer return 2 for error*/

        return 2;

    }

    else if (control==0){ /*For repeating number control.If there is repeating number return 0 for error*/

        return 0;
    }

}

int game (char user_number[N],int divided_user_number[N],int digit_number,int number[N],int& gamecount_1){ /*Game part*/

    int gamecount_2=0, /* For counting right digits*/
    gamecount_3=0, /*For counting right number but different digits numbers*/
    i=0,/*For loops*/
    j=0,/*For loops*/
    k=0,/*For loops*/
    control=1; /*If everythin is okay control always 1 until printing result*/

    while (control==1 && gamecount_1<100 && gamecount_2!=digit_number){ /*Game loop*/
            
        k=0;
        gamecount_3=0;
        gamecount_2=0;            
        cin >> user_number; /*Takes number from user*/
        control=divide_number (user_number,divided_user_number,digit_number); /*Controls value if is true or not*/
        if (control!=1){ /*If entry is false returns its value and exits*/
            return control;
        }
        gamecount_1++; /*Calculates how many turns player has play*/
        for (i=0;i<digit_number;i++){ /*If entered integer is on right place, increments gamecount_2 value*/
            if (divided_user_number[i]==number[i]){
                gamecount_2++;
            }
            for (j=0;j<digit_number;j++){ /*If entered value is right but its place false increments gamecount_3*/
                if (divided_user_number[i]==number[j] && divided_user_number[i]!=number[i]){ 
                    gamecount_3++;
                }
            }
        }
        if (control==1){ /*If there is no problem prints counts*/
            cout << gamecount_2 << " " <<gamecount_3 << endl;
        }
    }
    if (gamecount_2==digit_number){ /* If player wins the game returns 5 to outpur for winning*/

        control=5;
    }
    return control;
}