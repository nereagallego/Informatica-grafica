#include "Triangulo.h"

// Triangulo::Triangulo(Punto x, Punto y, Punto z){
//     Direccion d1 = y-x;
//     Direccion d2 = z-x;
//     Direccion cross = crossProduct(d1,d2);
//     _normal = cross / cross.modulo();
//     _distancia = -(_normal*x);
//     _x = x;
//     _y = y;
//     _z = z;
// }

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

float Triangulo::intersect(Ray r) {
    Direccion d1 = _y - _x;
    Direccion d2 = _z - _x;
    Direccion h = crossProduct(r.getDireccion(),d2);
    float a = d1*h; // determinante

    if (a > -0.00001 && a < 0.00001)
    return(-1);

    Direccion s = r.getPunto() - _x;

    float u = (s * h);

    if ((a > 0.00001 && (u < 0.0 || u > a)) || (a < -0.00001 && (u > 0.0 || u < a)))
    return -1;

    Direccion q = crossProduct(s, d1);

    float v = r.getDireccion() * q;

    if ((a > 0.00001 && (v < 0.0 || u + v > a)) || a < -0.00001 && (v > 0.0 || u + v < a))
    return -1;
    
    float tt = (d2 * q)/a;
    return tt;
}