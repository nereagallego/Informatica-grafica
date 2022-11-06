#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <iostream>
#include "../math/Direccion.h"
#include "../math/Punto.h"
#include <memory>

using namespace std;

class Ray {
private:
    Direccion _direccion;
    Punto _punto;

public:
    /**
     * @brief Construct a new Ray object
     * 
     * @param d dirección del rayo
     * @param p punto de origen del rayo
     */
    Ray(const Direccion d, const Punto p);

    Punto getPunto();
    Direccion getDireccion();  
    void setPunto(Punto p);
    void setDireccion(Direccion d);  
};

#endif