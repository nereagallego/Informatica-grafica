#include "Plano.h"

float Plano::getDistancia(){
    return _distancia;
}

Direccion Plano::getNormal(){
    return _normal;
}

Intersect Plano::intersect(Ray r) {
    Intersect s;
   // s._emision = make_shared<BSDF>(this->getEmision());
    s._emision = this->getEmision();
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

    tuple<double,double> x = getUV(s._punto);
    s._u = get<0>(x);
    s._v = get<1>(x);
    return s;
}

tuple<double,double> Plano::getUV(Punto p){
    return {_ejeU * p, _ejeV * p};
}