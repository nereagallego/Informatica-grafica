#include "Direccion.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){

    Direccion d1(1,2,3);
    Punto d2(1,2,3);

    Punto d3 = d1 + d2;

    cout << d3.x << " " << d3.y << " " << d3.z << endl;

    Punto p2(1,2,3);

    Direccion p3 = d2 - p2;


    cout << p3.x << " " << p3.y << " " << p3.z << endl;

    return 0;
}