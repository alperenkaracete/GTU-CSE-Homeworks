#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX=10000; /*Max Turns*/

int talent_part (int turn); /*Returns if shooter succesfully shoted or not*/

int main(){

    srand (time(NULL)); 

    double aaron_win=0, /*Aaron win count*/
    bob_win=0, /*Bob win count*/
    charlie_win=0; /*Charlie win count*/

    bool aaron_status=1, /*If 1 person lives*/
    bob_status=1, /*If 1 person lives*/
    charlie_status=1, /*If 1 person lives*/
    succes; /*If 1 shoot is succesfull*/

    while (bob_win+aaron_win+charlie_win!=MAX){

        if (aaron_status==1){ /*If Aaron lives his turn*/

            succes=talent_part(1);
            if (succes==1){ /*If shoot succes*/

                if (charlie_status==1){ /*If Charlie alive kill charlie*/

                    charlie_status=0;
                }

                else if (bob_status==1){ /* Else kill Bob if alive*/

                    bob_status=0;
                }
            }
        }

        if (bob_status==1){ /*If Bob lives his turn*/

            succes=talent_part(2);
            if (succes==1){ /*If shoot succes*/

                if (charlie_status==1){ /*If Charlie alive kill charlie*/

                    charlie_status=0;
                }

                else if (aaron_status==1){ /* Else kill Aaron if alive*/

                    aaron_status=0;
                }
            }
        }

        if (charlie_status==1){ /*If Charlie lives his turn*/

            succes=talent_part(3);
            if (succes==1){ /*If shoot succes*/

                if (bob_status==1){ /* IF  Bob is alive kill bob*/

                    bob_status=0;
                }

                else if (aaron_status==1){ /* Else kill Aaron if alive*/

                    aaron_status=0;
                }
            } 
        } 

        if (bob_status==0 && charlie_status==0 && aaron_status==1){ /* If bob and charlie dead and aaron alive aaron wins*/

            aaron_win++;
            bob_status=1;
            charlie_status=1;
        }

        else if (aaron_status==0 && charlie_status==0 && bob_status==1){  /* If aaron and charlie dead and bob alive bob wins*/

            bob_win++;
            aaron_status=1;
            charlie_status=1;
        }

        else if (bob_status==0 && aaron_status==0 && charlie_status==1){ /* If bob and aaron dead and charlie alive charlie wins*/

            charlie_win++;
            aaron_status=1;
            bob_status=1;
        }                       
    }

    cout << "Aaron Won:" << " %" << aaron_win/100 << endl; /*Win percents*/
    cout << "Bob Won:" << " %" << bob_win/100 << endl;
    cout << "Charlie Won:" << " %" << charlie_win/100 << endl;

}

int talent_part (int turn){

    int luck;   

    if (turn==1){ /*If aaron turn calculates his luck*/

        luck=rand()%3;

        if (luck==0){

            return 1; /*If succes return 1*/
        }

        else {

            return 0; /*Else return 0*/
        }
    }

    if (turn==2){ /*If bobs turn calculates his luck*/

        luck=rand()%2;

        if (luck==0){ /*If succes return 1*/

            return 1;
        }

        else { /*Else return 0*/

            return 0;
        }
    }

    if (turn==3){ /*If charlies turn he shots %100*/

        return 1;
    }        

}
