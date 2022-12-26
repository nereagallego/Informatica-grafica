#include "Plano.h"

float Plano::getDistancia(){
    return _distancia;
}

Direccion Plano::getNormal(){
    return _normal;
}

Intersect Plano::intersect(Ray r) {
    Intersect s;
    s._emision = this->getEmision();
    s._texture = this->getTexture();
    float denominador = r.getDireccion() * _normal;
    if(denominador == 0){ s._intersect = false; return s;}
    else s._intersect = true;
    s._t = -(_distancia + _normal * r.getPunto())/denominador;
    if(s._t <= 0.00001) s._intersect = false;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    if(r.getDireccion().angulo(this->getNormal()) < M_PI / 2)
    s._normal = this->getNormal().normalizar();
    else 
    {
        s._normal = this->getNormal().normalizar() *-1;
      //  cout << "desde dentro";
    }
    return s;
}