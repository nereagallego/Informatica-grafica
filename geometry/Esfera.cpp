#include "Esfera.h"

Punto Esfera::getCentro(){
    return _centro;
}


float Esfera::getRadio(){
    return _radio;
}

Intersect Esfera::intersect(Ray r){
    Intersect s;
    s._intersect = true;
    Direccion aux = r.getPunto() - _centro;
    float a = r.getDireccion() * r.getDireccion();
    float b = r.getDireccion() * aux * 2;
    float c = aux * aux - _radio * _radio;
    float radicando = b * b - 4 * a * c;
    if (radicando < 0) s._intersect = false;
    float delta = sqrt(radicando);
    float r1 = (- b - delta) / (2 * a);
    float r2 = (- b + delta) / (2 * a);
    if (r1 > 0.0001 && r2 > 0 && r1 < r2) s._t = r1;
    else if(r2 > 0.0001) s._t = r2;
    else s._intersect = false;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    s._emision = this->getEmision();
    Direccion d = s._punto - _centro;
    s._normal = d.normalizar();
    return s;
}