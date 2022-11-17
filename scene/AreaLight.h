#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "Light.h"
#include "../geometry/Plano.h"

class AreaLight : public Light, public Plano {
public:
    AreaLight(Direccion normal,float d,Punto center, RGB power): Plano(normal,d,power), Light(center,power) {}
};

#endif