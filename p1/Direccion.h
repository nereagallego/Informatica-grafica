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
    // Constructor de un vector dadas sus coordenadas
    Direccion(float x_, float y_, float z_);   
    // Constructor vacío de un vector
    // Le sasigna las coordenadas (0,0,0)
    Direccion(): x(0), y(0), z(0) {};

    // Suma de dos direcciones
    // Devuelve la dirección resultante
    Direccion operator +(Direccion d2);

    // Resta de dos direcciones
    // Devuelve la dirección resultante
    Direccion operator -(Direccion d2);

    // Multiplicación de una dirección por un número real
    // Devuelve el resultado de escalar ese vector (se hace d2 veces más grande)
    Direccion operator *(float d2);

    // División de un vector por un real
    // Devuelve el resultado de escalar ese vector (se hace d2 veces más pequeño)
    Direccion operator /(float d2);

    // Suma de una dirección con un punto
    // Devuelve el punto resultante de mover el punto p en la dirección dada una distancia de |d|
    // Siendo |d| el módulo del vector d
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