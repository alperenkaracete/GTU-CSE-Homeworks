#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int humanTurn (int humanTotalScore);
int computerTurn (int computerTotalScore);
int rollDice (int diceValue);

int main(){

    srand (time(NULL));

    int humanTotalScore=0,
    computerTotalScore=0;

    while (humanTotalScore<100 && computerTotalScore<100){
        humanTotalScore=humanTurn(humanTotalScore);
        if (humanTotalScore<100){
            computerTotalScore=computerTurn(computerTotalScore);
        }
        cout << "Total Human Score:" <<humanTotalScore << endl;
        cout << "Total Computer Score "<<computerTotalScore <<endl;
        }

    if (computerTotalScore>100){

        cout << "Computer win!" << endl;
    } 

    else {

        cout << "Human win!" << endl;
    }

}

int rollDice (int diceValue){

    int dice;
    dice=rand()%6+1;

    return dice;

}

int humanTurn (int humanTotalScore){

    int dice,
    turnScore=0;

    char again;

    do
    {
        dice=rollDice(dice);

        if (dice!=1){
            cout << "Player diced: " <<dice << endl;
            turnScore+=dice;
            if (turnScore+humanTotalScore<100){
                cout << "For ROLL AGAIN press r, for HOLD press h" << endl;
                cin >> again;
            }
            if (again!='h' || again!='r'){

                while (again!='h' && again!='r'){
                    cout << "Wrong input try again!" << endl;    
                    cin >>again;
                }    
            }
        }

        else {

            cout << "Player diced: " <<dice << endl;
            cout << "End Turn" <<endl;
            turnScore=0;
        }


    } while (dice!=1 && again=='r' && turnScore+humanTotalScore<100);

    humanTotalScore+=turnScore;

    if (again=='h'){

        cout << "Player hold turn ended" << endl;
    }
    
    return humanTotalScore;
    
}

int computerTurn (int computerTotalScore){

    int dice,
    turnScore=0;

    bool again=1;

    do
    {
        dice=rollDice(dice);
        if (dice!=1){
            cout << "Computer diced " << dice << endl;
            turnScore+=dice;

        }

        else {

            cout << "Computer diced " << dice << endl;
            cout << "End Turn" << endl;
            turnScore=0;
        }


    } while (dice!=1 && turnScore<20 && turnScore+computerTotalScore<100);

    computerTotalScore+=turnScore;
    
    return computerTotalScore;

}