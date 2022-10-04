#ifndef DIRECCION_HPP
#define DIRECCION_HPP
#include <stdlib.h>
#include "Punto.h"
#include <cmath>

using namespace std;

// g++ Direccion.cpp -c -sdt=c++11


// normalización:
//      |v| = d
//      nomalizado = v/d

class Punto;


class Direccion{
    private:
    
    public:
    float x, y ,z;
    Direccion(float x_, float y_, float z_);   
    Direccion(): x(0), y(0), z(0) {};

    Direccion operator +(Direccion d2);

    Direccion operator -(Direccion d2);

    Direccion operator *(float d2);

    Direccion operator /(float d2);

    Punto operator +(Punto p);

    float modulo();

    Direccion normalizar();
    //DOT PRODUCT
    float operator *(Direccion d);    

    

};

Direccion crossProduct(Direccion d1, Direccion d2);

#endif