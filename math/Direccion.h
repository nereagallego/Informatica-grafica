#ifndef DIRECCION_HPP
#define DIRECCION_HPP
#include <stdlib.h>
#include "Punto.h"
#include <cmath>
#include <iostream>

using namespace std;

// g++ Direccion.cpp -c -sdt=c++11

class Punto;


class Direccion{
    private:
    float _x, _y ,_z;
    public:
    /**
     * @brief Construct a new Direccion object
     * 
     * @param x coordenada X
     * @param y coordenada y
     * @param z coordenada z
     */
    Direccion(float x, float y, float z);
    /**
     * @brief Construct a new Direccion object with coordinates (0,0,0)
     * 
     */
    Direccion(): _x(0), _y(0), _z(0) {};

    /**
     * @brief Devuelve la suma de dos direcciones
     * 
     * @param d2 dirección a sumar
     * @return Direccion 
     */
    Direccion operator +(const Direccion d2);

    /**
     * @brief Devuelve la resta de dos direcciones
     * 
     * @param d2 dirección a restar
     * @return Direccion 
     */
    Direccion operator -(const Direccion d2);

    /**
     * @brief Devuelve el resultado de escalar la dirección d2 veces (más 
     * grande)
     * 
     * @param d2 coeficiente de escalado
     * @return Direccion 
     */
    Direccion operator *(const float d2);

    /**
     * @brief Devuelve el resultado de escalar la dirección d2 veces (más 
     * pequeño)
     * 
     * @param d2 coeficiente de escalado
     * @return Direccion 
     */
    Direccion operator /(const float d2);

    /**
     * @brief Devuelve el resultado de sumar la dirección a un punto p
     * Equivale a mover un punto en la dirección d una distancia |d| 
     * siendo |d| el módulo del vector d 
     * 
     * @param p punto desde el que se suma la dirección
     * @return Punto 
     */
    Punto operator +(const Punto p);

    /**
     * @brief Devuelve el módulo del vector
     * 
     * @return float 
     */
    float modulo();

    /**
     * @brief Normaliza el vector
     * 
     * @return Direccion 
     */
    Direccion normalizar();
    
    /**
     * @brief Devuelve el producto escalar de dos vectores
     * 
     * @param d segundo vector con el que se va a calcular el producto escalar
     * @return float 
     */
    float operator *(const Direccion d);

    /**
     * @brief Devuelve el producto escalar de un punto y un vector
     * 
     * @param p punto con el que se va a calcular el producto escalar
     * @return float 
     */
    float operator *(const Punto p);    

    /**
     * @brief Devuelve la coordenada X del vector
     * 
     * @return float 
     */
    float getX() const;

    /**
     * @brief Devuelve la coordenada Y del vector
     * 
     * @return float 
     */
    float getY() const;

    /**
     * @brief Devuelve la coordenada Z del vector
     * 
     * @return float 
     */
    float getZ() const;

    /**
     * @brief Dirección entre dos vectores
     * 
     * @param d 
     * @return double 
     */
    double angulo(Direccion d);

    // pretty stdout
    friend ostream& operator<<(ostream& os, const Direccion p);

};

/**
 * @brief Devuelve el producto vectorial de dos vectores
 * 
 * @param d1 primer vector 
 * @param d2 segundo vector
 * @return Direccion 
 */
Direccion crossProduct(Direccion d1, Direccion d2);

/**
 * @brief Devuelve el vector perpenticular a un vector dado
 * 
 * @param d 
 * @return Direccion 
 */
Direccion perpendicular(const Direccion d);

/**
 * @brief Función delta de dos direcciones
 * 
 * @param d 
 * @param f 
 * @return true 
 * @return false 
 */
double delta(Direccion d, Direccion f);

#endif