#ifndef PUNTO_HPP
#define PUNTO_HPP
#include <stdlib.h>
#include "Direccion.h"

using namespace std;

// g++ Punto.cpp -c -std=c++11

class Direccion;

class Punto{
    private:
    
    public:
    float x, y ,z;
    Punto(float x_, float y_, float z_);   

    Punto operator +(Direccion d);

    Direccion operator -(Punto p);
};

#endif