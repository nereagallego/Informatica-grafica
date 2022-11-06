#include "Ray.h"

Ray::Ray(const Direccion d, const Punto p){
    _direccion = d;
    _punto = p;
}

Punto Ray::getPunto(){
    return _punto;
}

Direccion Ray::getDireccion(){
    return _direccion;
}

void Ray::setPunto(Punto p){
    _punto = p;
}

void Ray::setDireccion(Direccion d){
    _direccion = d;
} 