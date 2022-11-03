#ifndef ESFERA_HPP
#define ESFERA_HPP


#include "../math/Direccion.h"
#include <cmath>
#include <iostream>
#include "../math/CoordenadasHomogeneas.h"
#include "Ray.h"
#include "../math/Direccion.h"
#include "Primitive.h"

using namespace std;

class Ray;

class Esfera : public Primitive {
private:

    Punto _centro;
    float _radio;
public:
    /**
     * @brief Construct a new Esfera object
     * 
     * @param eje eje de la esfera
     * @param centro centro de la esfera
     * @param referencia punto de referencia de la esfera
     */
    Esfera(Punto centro, float radio): _radio(radio), _centro(centro) 
    {};

    Esfera(Punto centro, float radio, RGB emision): Primitive(emision), _radio(radio),  _centro(centro) {}

    Punto getCentro();
    float getRadio();

    Intersect intersect(Ray r) override;
};

#endif