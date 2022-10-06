#ifndef ESFERA_HPP
#define ESFERA_HPP


#include "Direccion.h"
#include <cmath>
#include <iostream>
#include "CoordenadasHomogeneas.h"

class Punto;
class Direccion;

class Esfera {
private:
    Direccion ejeY,ejeX,ejeZ;
    Punto centro;
    Punto referencia;
    float radio;
public:
    Esfera(Direccion _eje, Punto _centro, Punto _referencia);

    Punto pointDefinition(float incl, float azim);
};

#endif