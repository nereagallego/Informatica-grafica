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

    /**
     * @brief Devuelve la coordenada X del punto
     * 
     * @return float 
     */
    float getX() const;

    /**
     * @brief Devuelve la coordenada Y del punto
     * 
     * @return float 
     */
    float getY() const;

    /**
     * @brief Devuelve la coordenada Z del punto
     * 
     * @return float 
     */
    float getZ() const;

    float operator *(const Direccion d);

};

#endif