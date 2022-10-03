#ifndef ESFERA_HPP
#define ESFERA_HPP

#include "Punto.h"
#include "Direccion.h"

class Esfera {
private:
    Direccion eje;
    Punto centro;
    Punto referencia;
public:
    Esfera(Direccion _eje, Punto _centro, Punto _referencia);
};

#endif