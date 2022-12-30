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
     * @param centro centro de la esfera
     * @param radio radio de la esfera
     */
    Esfera(Punto centro, float radio): _radio(radio), _centro(centro) 
    {};

    /**
     * @brief Construct a new Esfera object
     * 
     * @param centro centro de la esfera
     * @param radio radio de la esfera
     * @param emision color de la esfera
     */
    Esfera(Punto centro, float radio, shared_ptr<BSDF> emision): Primitive(emision), _radio(radio),  _centro(centro) {};

    Punto getCentro();
    float getRadio();

    /**
     * @brief Devuelve la intersección del rayo r con la esfera (si intersecta)
     * Sino, indica que no intersecta
     * 
     * @param r rayo con el que se quiere calcular la intersección
     * @return Intersect 
     */
    Intersect intersect(Ray r) override;

    tuple<double,double> getUV(Punto p);
};

#endif