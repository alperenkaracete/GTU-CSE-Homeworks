#include <iostream>

using namespace std;

class Fraction{

    public:

    double turn_double ();
    void set_numerator(int numerator);
    void set_denominator (int denominator);
    void output_func();

    private:

    int number1;
    int number2;
    int gcd();
};

double Fraction::turn_double(){

    return (static_cast<double>(number1)/number2);
}

void Fraction::output_func(){

    int g;

    g=gcd();
    cout << number1/g << "/" << number2/g << endl;

}

void Fraction::set_numerator(int numerator){

    number1=numerator;
}

void Fraction::set_denominator(int denominator){

    number2=denominator;
}

int Fraction::gcd(){

    int divisor;

    if (number1>number2){

        divisor=number2;
    }

    else {

        divisor=number1;
    }

    while (divisor>1){

        if (number1%divisor==0 && number2%divisor==0){

            return divisor;
        }
        divisor--;
    }
    return 1;
}

int main(){

    Fraction f1,f2;

    f1.set_numerator(10);
    f1.set_denominator(20);
    cout << f1.turn_double() << endl;
    f1.output_func();
    cout << endl;

    f2.set_numerator(18);
    f2.set_denominator(6);
    cout << f2.turn_double() << endl;
    f2.output_func();    
}