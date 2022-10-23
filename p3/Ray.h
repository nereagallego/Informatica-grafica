#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <iostream>
#include "../p1/Direccion.h"
#include "../p1/Punto.h"
#include "Plano.h"
#include "Esfera.h"


class Ray {
private:
    Direccion _direccion;
    Punto _punto;
public:
    /**
     * @brief Construct a new Ray object
     * 
     * @param d 
     * @param p 
     */
    Ray(const Direccion d, const Punto p);

    /**
     * @brief Devuelve la distancia de intersección de un rayo con un plano
     * 
     * @param p plano con el que se calcula la intersección
     * @return float 
     */
    float intersect(Plano p);

    /**
     * @brief Devuelve la distancia de intersección de un rayo con una esfera
     * 
     * @param e esfera con la que se calcula la intersección
     * @return float 
     */
    float intersect(Esfera e);

    Punto getPunto();
    Direccion getDireccion();    
};

#endif