#ifndef TRIANGULO_HPP
#define TRIANGULO_HPP

#include "../p1/Punto.h"
#include "Plano.h"
#include "../p1/Direccion.h"

class Triangulo{
private:
    Punto _x, _y, _z;
    Direccion _normal;
    float _distancia;
public:
    Triangulo(Punto x, Punto y, Punto z, float distancia);

    Direccion getNormal();
    float getDistancia();
    Punto getX();
    Punto getY();
    Punto getZ();
};



#endif