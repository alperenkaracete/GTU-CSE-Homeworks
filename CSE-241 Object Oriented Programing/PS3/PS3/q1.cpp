#include <iostream>

using namespace std;

class Coordinates {

    public:

    void set_func (double x_coordinate,double y_coordinate);
    void move_func (double x_coordinate,double y_coordinate);
    void rotate();
    double x_coordinate();
    double y_coordinate();

    private:

    double x;
    double y;
};

double Coordinates::x_coordinate(){

    return x;
}

double Coordinates::y_coordinate(){

    return y;
}

void Coordinates::set_func (double x_coordinate,double y_coordinate){

    x=x_coordinate;
    y=y_coordinate;
}

void Coordinates::move_func (double x_coordinate,double y_coordinate){

    x=x + x_coordinate;
    y=y + y_coordinate;
}

void Coordinates::rotate(){

    double temp;

    temp=x;
    x=-y;
    y=temp;
}

int main(){

    Coordinates j,k,l;
    j.set_func(1,2);
    cout << j.x_coordinate() << ", " << j.y_coordinate() << endl;
    j.rotate();
    cout << j.x_coordinate() << ", " << j.y_coordinate() << endl;
    j.rotate();
    cout << j.x_coordinate() << ", " << j.y_coordinate() << endl;
    j.rotate();
    cout << j.x_coordinate() << ", " << j.y_coordinate() << endl;
    j.rotate();
    cout << j.x_coordinate() << ", " << j.y_coordinate() << endl;

    k.set_func(2,3);
    cout << k.x_coordinate() << ", " << k.y_coordinate() << endl;
    k.move_func(1,1); 
    cout << k.x_coordinate() << ", " << k.y_coordinate() << endl;

    l.set_func(5,-4);
    cout << l.x_coordinate() << ", " << l.y_coordinate() << endl;              

    l.move_func(-5,4);
    cout << l.x_coordinate() << ", " << l.y_coordinate() << endl;

}

