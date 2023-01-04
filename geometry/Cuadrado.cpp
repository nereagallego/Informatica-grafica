#include "Cuadrado.h"

Intersect Cuadrado::intersect(Ray r) {
    Intersect s;
    // s._emision = make_shared<BSDF>(this->getEmission());
    s._emision = this->getEmision();
    float denominador = r.getDireccion() * _p.getNormal();
    if(denominador == 0){ s._intersect = false; return s;}
    else s._intersect = true;
    s._t = -(_p.getDistancia() + _p.getNormal() * r.getPunto())/denominador;
    if(s._t <= 0.00001) s._intersect = false;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    
    if(r.getDireccion().angulo(_p.getNormal()) < M_PI / 2)
    s._normal = _p.getNormal().normalizar();
    else 
    {
        s._normal = _p.getNormal().normalizar() *-1;
    //  cout << "desde dentro";
    }
    s._intersect = s._intersect && s._punto.getX() >= _p1.getX() && s._punto.getX() <= _p3.getX() && s._punto.getY() >= _p1.getY() && s._punto.getY() <= _p3.getY() && s._punto.getZ() >= _p1.getZ() && s._punto.getZ() <= _p3.getZ();
    
    return s;
}