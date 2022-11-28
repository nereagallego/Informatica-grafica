#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../math/Punto.h"
#include "../color/RGB.h"
#include "../math/rand.hpp"

using namespace std;

class Light
{
private:
    Punto _center;
    RGB _power;
public:

    /**
     * @brief Construct a new Light object
     * 
     * @param center 
     * @param power 
     */
    Light(Punto center, RGB power): _center(center), _power(power) {};

    Punto getCenter();
    RGB getPower();

    double getLuminance(){ return _power.getRed() + _power.getGreen() + _power.getBlue();}
    Direccion sample()const;

    // int getPhotons();
    // void setPhotons(int photons);
};





#endif