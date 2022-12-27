#include "Light.h"


Punto Light::getCenter(){
   return _center;
}
    
RGB Light::getPower(){
    return _power;
}

Direccion Light::sample() const{
    double theta = Rand::fRand(-1.0,1.0);
    double phi = Rand::fRand(0.0,1.0);
    double thethaInverse = acos(theta);
    double phiInverse = 2 * M_PI * phi;
    return Direccion(sin(thethaInverse)*cos(phiInverse),sin(thethaInverse)*sin(phiInverse),cos(thethaInverse)).normalizar();
}

Punto Light::samplePoint() const {
    return _center;
}