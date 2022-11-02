#ifndef PLANO_HPP
#define PLANO_HPP

#include <cmath>
#include <iostream>
#include "../math/Direccion.h"
#include "Primitive.h"

class Ray;


class Plano : public Primitive {
private:
    Direccion _normal;
    float _distancia;
public:
    /**
     * @brief Construct a new Plano object
     * 
     * @param normal direccioón normal al plano
     * @param d disancia del plano al origen
     */
    Plano(Direccion normal,float d): _normal(normal), _distancia(d) {};

    /**
     * @brief Construct a new Plano object
     * 
     * @param normal direccioón normal al plano
     * @param d disancia del plano al origen
     * @param emision emisión del plano
     */
    Plano(Direccion normal, float d, RGB emision): _normal(normal), _distancia(d), Primitive(emision) {};

    float getDistancia();
    Direccion getNormal();

    /**
     * @brief Intersección de un rayo con el plano
     * 
     * @param r 
     * @return float 
     */
    float intersect(Ray r) override;
};

#endif