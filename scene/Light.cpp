#include "Light.h"


Punto Light::getCenter(){
   return _center;
}
    
RGB Light::getPower(){
    return _power;
}

int Light::getPhotons(){
    return _numberPhotons;
}

void Light::setPhotons(int photons){
    _numberPhotons = photons;
}