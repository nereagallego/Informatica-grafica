#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../math/Punto.h"
#include "../color/RGB.h"

using namespace std;

class Light
{
private:
    Punto _center;
    RGB _power;
public:
    Light(Punto center, RGB power): _center(center), _power(power) {};
    Punto getCenter();
    RGB getPower();
};





#endif