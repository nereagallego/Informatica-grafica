#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "Light.h"
#include "../geometry/Plano.h"
#include "../scene/BSDF.h"
#include "../math/Matrix4.h"
#include "../math/CoordenadasHomogeneas.h"

class AreaLight : public Light{
protected:    
    Plano _p;
public:
    AreaLight(Direccion normal,float d,Punto center, RGB power):  _p(Plano(normal,d)), Light(center,power) {
        if(normal * center + d != 0) throw logic_error("el centro no pertenece al plano de la luz de area");
        
    }

    virtual ~AreaLight() { /* whatever goes here, or nothing... */ }
    Direccion getNormal() { return _p.getNormal();}
    float getDistancia() { return _p.getDistancia();}
    shared_ptr<BSDF> getEmission() { return _p.getEmision();}

    virtual Intersect intersect(Ray r) = 0;
};


class SquareLight : public AreaLight {
    Punto _p1, _p2, _p3, _p4;
public:
    SquareLight(Direccion normal,float d,Punto center, RGB power, Punto p1, Punto p2, Punto p3, Punto p4): _p1(p1), _p2(p2), _p3(p3), _p4(p4), AreaLight(normal, d, center, power) {
        if(normal * p1 + d != 0) throw logic_error("el punto p1 no pertenece al plano de la luz de area");
        if(normal * p2 + d != 0) throw logic_error("el punto p2 no pertenece al plano de la luz de area"); 
        if(normal * p3 + d != 0) throw logic_error("el punto p3 no pertenece al plano de la luz de area");
        if(normal * p4 + d != 0) throw logic_error("el punto p4 no pertenece al plano de la luz de area");
    }

    Intersect intersect(Ray r) override {
        Intersect s;

        s._emision = this->getEmission();
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
        }
        s._intersect = s._intersect && s._punto.getX() >= _p1.getX() && s._punto.getX() <= _p3.getX() && s._punto.getY() >= _p1.getY() && s._punto.getY() <= _p3.getY() && s._punto.getZ() >= _p1.getZ() && s._punto.getZ() <= _p3.getZ();
       
        return s;
    }

    Punto samplePoint() override {
        Direccion dd1 = _p1 - _p2, dd2 = _p2 - _p3;
        float d1 = dd1.modulo()/2 , d2 = dd2.modulo()/2;
        float f1 = Rand::fRand(-d1,d1), f2 = Rand::fRand(-d2,d2);
        return this->_center + dd1.normalizar() * f1 + dd2.normalizar() * f2;
    }
};

class CircleLight : public AreaLight {
    double _radius;
public:
    CircleLight(Direccion normal,float d,Punto center, RGB power, double radius): _radius(radius), AreaLight(normal.normalizar(), d, center, power) {}

    Intersect intersect(Ray r) override {
        Intersect s;
        s._emision = this->getEmission();
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
        }
        Direccion d = s._punto - this->getCenter();
        s._intersect = s._intersect && d.modulo() <= _radius;
        return s;
    }

    Punto samplePoint()override {
        
        float rad = Rand::fRand(0,_radius);
        float theta = Rand::fRand(0,1) * 2 * M_PI;
        Punto point(rad*sin(M_PI/2)*cos(theta), rad*sin(M_PI/2)*sin(theta), rad*cos(M_PI/2));
        Direccion ejeX = perpendicular(this->getNormal()).normalizar();
        Direccion ejeY = crossProduct(ejeX,this->getNormal());
        Direccion ejeZ = this->getNormal();

        float v[4][4] = {{ejeX.getX(),ejeY.getX(),ejeZ.getX(),_center.getX()},{ejeX.getY(),ejeY.getY(),ejeZ.getY(),_center.getY()},{ejeX.getZ(),ejeY.getZ(),ejeZ.getZ(),_center.getZ()},{0,0,0,1}};
        Matrix4 T(v);

        CoordenadasHomogeneas w(point);

        return w.cambioBase(T).punto();
    }
};
#endif