#ifndef DIRECCION_HPP
#define DIRECCION_HPP
#include <stdlib.h>
#include "Punto.h"
#include <cmath>

using namespace std;

// g++ Direccion.cpp -c -sdt=c++11

class Punto;


class Direccion{
    private:
    float x, y ,z;
    public:
    /**
     * @brief Construct a new Direccion object
     * 
     * @param x_ coordenada X
     * @param y_ coordenada y
     * @param z_ coordenada z
     */
    Direccion(float x_, float y_, float z_);
    /**
     * @brief Construct a new Direccion object with coordinates (0,0,0)
     * 
     */
    Direccion(): x(0), y(0), z(0) {};
    /**
     * @brief Devuelve la duma de dos direcciones
     * 
     * @param d2 dirección a sumar
     * @return Direccion 
     */
    Direccion operator +(Direccion d2);

    /**
     * @brief Devuelve la resta de dos direcciones
     * 
     * @param d2 dirección a restar
     * @return Direccion 
     */
    Direccion operator -(Direccion d2);

    /**
     * @brief Devuelve el resultado de escalar la dirección d2 veces (más 
     * grande)
     * 
     * @param d2 coeficiente de escalado
     * @return Direccion 
     */
    Direccion operator *(float d2);

    /**
     * @brief Devuelve el resultado de escalar la dirección d2 veces (más 
     * pequeño)
     * 
     * @param d2 coeficiente de escalado
     * @return Direccion 
     */
    Direccion operator /(float d2);

    /**
     * @brief Devuelve el resultado de sumar la dirección a un punto p
     * 
     * @param p punto desde el que se suma la dirección
     * @return Punto 
     */
    Punto operator +(Punto p);

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
    float operator *(Direccion d);    

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

};

/**
 * @brief Devuelve el producto vectorial de dos vectores
 * 
 * @param d1 primer vector 
 * @param d2 segundo vector
 * @return Direccion 
 */
Direccion crossProduct(Direccion d1, Direccion d2);

#endif