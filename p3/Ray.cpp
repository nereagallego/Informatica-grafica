#include "Ray.h"

Ray::Ray(const Direccion d, const Punto p){
    _direccion = d;
    _punto = p;
}

Punto Ray::intersect(Plano p){
    float t = -(p.getDistancia() + p.getNormal()*_punto)/(_direccion*p.getNormal()); 
    Punto aux = _punto + _direccion*t;
    return aux;
}

Punto Ray::intersect(Esfera e){
    
}