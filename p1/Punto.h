#ifndef PUNTO_HPP
#define PUNTO_HPP
#include <stdlib.h>
#include "Direccion.h"
#include <iostream>

using namespace std;

// g++ Punto.cpp -c -std=c++11

class Direccion;

// Clase Punto
class Punto{
    protected:
        float x, y ,z;
    public:
    
    // Constructor de un punto dadas sus coordenadas
    Punto(float x_, float y_, float z_);  
    // Constructor de un punto en las coordenadas (0,0,0)
    Punto(): x(0), y(0), z(0) {}; 

    // Suma de un punto con una dirección resulta un punto
    // Equivale a mover un punto en la dirección d una distancia |d|
    // siendo |d| el módulo del vector d
    Punto operator +(const Direccion d) const;

    // Resta de dos puntos
    // Devuelve la dirección resultante de ir desde el punto p hasta este punto
    Direccion operator -(const Punto p) const;

    // pretty stdout
    friend ostream& operator<<(ostream& os, const Punto p);

    // Devuelve la coordenada x del punto
    float getX() const;

    // Devuelve la coordenada y del punto
    float getY() const;

    // Devuelve la coordenada z del punto
    float getZ() const;
    
};

#endif