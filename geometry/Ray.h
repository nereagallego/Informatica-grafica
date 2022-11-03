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

    // /**
    //  * @brief Devuelve la distancia de intersección de un rayo con un plano
    //  * 
    //  * @param p plano con el que se calcula la intersección
    //  * @return float 
    //  */
    // float intersectPlano(Plano p);

    // /**
    //  * @brief Devuelve la distancia de intersección de un rayo con una esfera
    //  * 
    //  * @param e esfera con la que se calcula la intersección
    //  * @return float 
    //  */
    // float intersectEsfera(Esfera e);

    // /**
    //  * @brief Devuelve la distancia de interseccion de un rayo con un triangulo
    //  * 
    //  * @param t triangulo con el que se calculala intersección
    //  * @return float 
    //  */
    // float intersectTriangulo(Triangulo t);
public:
    /**
     * @brief Construct a new Ray object
     * 
     * @param d 
     * @param p 
     */
    Ray(const Direccion d, const Punto p);

    // float intersect(Primitive *p);

    Punto getPunto();
    Direccion getDireccion();  
    void setPunto(Punto p);
    void setDireccion(Direccion d);  
};

#endif