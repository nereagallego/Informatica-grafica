#include "Triangulo.h"

Triangulo::Triangulo(Punto x, Punto y, Punto z, float distancia){
    Direccion d1 = y-x;
    Direccion d2 = z-x;
    Direccion cross = crossProduct(d1,d2);
    _normal = cross / cross.modulo();
    _distancia = -(_normal*x);
    _x = x;
    _y = y;
    _z = z;
}

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