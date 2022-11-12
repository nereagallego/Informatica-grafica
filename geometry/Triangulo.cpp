#include "Triangulo.h"

Direccion Triangulo::getNormal(){
    return _normal;
}

float Triangulo::getDistancia(){
    return _distancia;
}

Punto Triangulo::getX(){
    return _x;
}

Punto Triangulo::getY(){
    return _y;
}

Punto Triangulo::getZ(){
    return _z;
}

Intersect Triangulo::intersect(Ray r) {
    Intersect s;
    s._intersect = true;
    Direccion d1 = _y - _x;
    Direccion d2 = _z - _x;
    Direccion h = crossProduct(r.getDireccion(),d2);
    float a = d1*h; // determinante

    if (a > -0.00001 && a < 0.00001){
        s._intersect = false;
        return s;
    }
    

    Direccion s1 = r.getPunto() - _x;

    float u = (s1 * h);

    if ((a > 0.00001 && (u < 0.0 || u > a)) || (a < -0.00001 && (u > 0.0 || u < a))){
        s._intersect = false;
        return s;
    }

    Direccion q = crossProduct(s1, d1);

    float v = r.getDireccion() * q;

    if ((a > 0.00001 && (v < 0.0 || u + v > a)) || a < -0.00001 && (v > 0.0 || u + v < a)){
        s._intersect = false;
        return s;
    }
    
    float tt = (d2 * q)/a;
    if(tt < 0.0001){
        s._intersect = false;
        return s;
    }else{
        
    }
    s._t = tt;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    s._emision = this->getEmision();
    s._normal = this->getNormal();
    return s;
}