#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>
#include <iostream>
#include "../p1/Direccion.h"
#include "../p1/Punto.h"
#include "Plano.h"


class Ray {
private:
    Direccion _direccion;
    Punto _punto;
public:
    
    Ray(const Direccion d, const Punto p);

    Punto intersect(Plano p);
    Punto intersect(Esfera e);

    
};

#endif