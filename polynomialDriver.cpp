//
// Created by marcela gomez on 2019-06-28.
//
#include <iostream>
using namespace std;

#include "polynomial.h"

int main(){

    Polynomial p1;
    cout << "p1 = " << p1 << endl;

    p1.changeCoefficient(3, 8);
    p1.changeCoefficient(2, 3);
    p1.changeCoefficient(-2, 4);

    cout << "p1 = " << p1 << endl;

    p1.changeCoefficient(0,8);
    cout << "p1 = " << p1 << endl;

    p1.degree( );


    Polynomial p2;

    cout << "p2 = " << p2 << endl;

    p1.changeCoefficient(4, 7);
    p1.changeCoefficient(5, 4);
    p1.changeCoefficient(6, 5);

    cout << "p1 = " << p1 << endl;

    p1.changeCoefficient(0, 5);
    cout << "p1 = " << p1 << endl;

    Polynomial p3;
    p3 = p1 + p2;
    cout << "p3 = " << p3 << endl;

    Polynomial p4;
    p4 = p1 - p2;
    cout << "p4 = " << p4 << endl;

}

