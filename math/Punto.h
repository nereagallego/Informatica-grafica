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
        float _x, _y ,_z;
    public:
    
    /**
     * @brief Construct a new Punto object
     * 
     * @param x_ coordenada x
     * @param y_ coordenada y
     * @param z_ coordenada z
     */
    Punto(float x_, float y_, float z_);  
    /**
     * @brief Construct a new Punto object with coordinates (0,0,0)
     * 
     */
    Punto(): _x(0), _y(0), _z(0) {}; 

    /**
     * 
     * @brief Devuelve el resultado de sumar la dirección d al punto
     * Equivale a mover un punto en la dirección d una distancia |d| 
     * siendo |d| el módulo del vector d
     * 
     * @param d dirección a sumar
     * @return Punto 
     */
    Punto operator +(const Direccion d) const;

    Punto operator  -(const Direccion d) const;

    /**
     * @brief Devuelve la dirección resultante de restar dos puntos
     * 
     * @param p 
     * @return Direccion 
     */
    Direccion operator -(const Punto p) const;

    // pretty stdout
    friend ostream& operator<<(ostream& os, const Punto p);

    float getX() const;
    float getY() const;
    float getZ() const;
    void setX(float a) { _x = a;}
    void setY(float a) { _y = a;}
    void setZ(float a) { _z = a;}

    float operator *(const Direccion d);

    /**
     * @brief Access to component i
     * 
     * @param i index of access
     * @return float
    */
    float operator [](const int i) const{
        if(i == 0) return _x;
        else if(i == 1) return _y;
        else if(i == 2) return _z;
        else throw logic_error("not position point");
    }

};

#endif