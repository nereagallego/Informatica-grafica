#ifndef PLANO_HPP
#define PLANO_HPP

#include <cmath>
#include <iostream>
#include "../p1/Direccion.h"


class Plano {
private:
    Direccion _normal;
    float _distancia;
public:

    Plano(Direccion normal,float d);

    float getDistancia();
    Direccion getNormal();

    
};

#endif