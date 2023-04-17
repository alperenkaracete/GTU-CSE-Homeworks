#include <iostream>

using namespace std;

int main(){

    int i=3,
    j=2,
    MAX=100;

    bool control=true;

    for (i;i<=MAX;i++){

        for (j=2;j<i;j++){

            if (i%j==0){

                control=false;

            }

        }

        if (control==true){

            cout << i << " ";
        }
        control=true;
    }

    return 0;
}
