#include "Plano.h"

float Plano::getDistancia(){
    return _distancia;
}

Direccion Plano::getNormal(){
    return _normal;
}

Intersect Plano::intersect(Ray r) {
    Intersect s;
    float denominador = r.getDireccion() * _normal;
    if(denominador == 0){ s._intersect = false; return s;}
    else s._intersect = true;
    s._t = -(_distancia + _normal * r.getPunto())/denominador;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    s._emision = this->getEmision();
    return s;
}