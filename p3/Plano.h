#ifndef PLANO_HPP
#define PLANO_HPP

#include <cmath>
#include <iostream>
#include "../p1/Direccion.h"
#include "Primitive.h"


class Plano : public Primitive {
private:
    Direccion _normal;
    float _distancia;
public:

    Plano(Direccion normal,float d): _normal(normal), _distancia(d) {};
    Plano(Direccion normal, float d, RGB emision): _normal(normal), _distancia(d), Primitive(emision) {};

    float getDistancia();
    Direccion getNormal();

    
};

#endif