#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "Light.h"
#include "../geometry/Plano.h"

class AreaLight : public Light{
    Punto _p1, _p2, _p3, _p4;
    Plano _p;
public:
    AreaLight(Direccion normal,float d,Punto center, RGB power, Punto p1, Punto p2, Punto p3, Punto p4): _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p(Plano(normal,d)), Light(center,power) {
        if(normal * center + d != 0) throw logic_error("el centro no pertenece al plano de la luz de area");
        if(normal * p1 + d != 0) throw logic_error("el punto p1 no pertenece al plano de la luz de area");
        if(normal * p2 + d != 0) throw logic_error("el punto p2 no pertenece al plano de la luz de area"); 
        if(normal * p3 + d != 0) throw logic_error("el punto p3 no pertenece al plano de la luz de area");
        if(normal * p4 + d != 0) throw logic_error("el punto p4 no pertenece al plano de la luz de area");
    }

    virtual ~AreaLight() { /* whatever goes here, or nothing... */ }

    Intersect intersect(Ray r) {
        Intersect s;
        s._emision = _p.getEmision();
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
};

#endif