#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "Light.h"
#include "../geometry/Plano.h"

class AreaLight : public Light, public Plano {
    Punto _p1, _p2, _p3, _p4;
public:
    AreaLight(Direccion normal,float d,Punto center, RGB power, Punto p1, Punto p2, Punto p3, Punto p4): _p1(p1), _p2(p2), _p3(p3), _p4(p4), Plano(normal,d), Light(center,power) {}

    Intersect intersect(Ray r) {
        Intersect s;
        s._emision = this->getEmision();
        float denominador = r.getDireccion() * this->getNormal();
        if(denominador == 0){ s._intersect = false; return s;}
        else s._intersect = true;
        s._t = -(this->getDistancia() + this->getNormal() * r.getPunto())/denominador;
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
};

#endif