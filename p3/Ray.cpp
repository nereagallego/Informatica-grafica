#include "Ray.h"

Ray::Ray(const Direccion d, const Punto p){
    _direccion = d;
    _punto = p;
}

float Ray::intersectPlano(Plano p){
    float denominador = _direccion*p.getNormal();
    if (denominador == 0) return -1;
    return -(p.getDistancia() + p.getNormal()*_punto)/(denominador); 
}

float Ray::intersectEsfera(Esfera e){
    Direccion aux = _punto - e.getCentro();
    float radicando = (_direccion * aux * 2) * (_direccion * aux * 2) - 4 * _direccion.modulo() * _direccion.modulo() * (aux.modulo() * aux.modulo() - e.getRadio());
    if (radicando < 0) return -1;
    float delta = sqrt(radicando);
    float r1 = (-(_direccion * aux * 2) - delta) / (2 * _direccion.modulo() * _direccion.modulo());
    float r2 = (-(_direccion * aux * 2) + delta) / (2 * _direccion.modulo() * _direccion.modulo());
    if (r1 > 0 && r2 > 0 && r1 < r2) return r1;
    else if(r2 > 0) return r2;
    else return -1;
}


float Ray::intersectTriangulo(Triangulo t){

    Direccion d1 = t.getY()-t.getX();
    Direccion d2 = t.getZ()-t.getX(); 
    Direccion h = crossProduct(_direccion, d2);
    float a = d1*h; // determinante

    if (a > -0.00001 && a < 0.00001)
    return(-1);

    // distancia del vértice al origen
    Direccion s = _punto - t.getX();

    float u = (s * h);

    if ((a > 0.00001 && (u < 0.0 || u > a)) || (a < -0.00001 && (u > 0.0 || u < a)))
    return -1;

    Direccion q = crossProduct(s, d1);

    float v = (_direccion * q);

    if ((a > 0.00001 && (v < 0.0 || u + v > a)) || a < -0.00001 && (v > 0.0 || u + v < a))
    return -1;
    
    float tt = (d2 * q)/a;
    return tt;
    
}

float Ray::intersect(Primitive *p){

    Plano* plane = dynamic_cast<Plano*>(p);
    if(plane != nullptr){ // es un plano
        return intersectPlano(*plane);
    } else {
        Esfera* esfera = dynamic_cast<Esfera*>(p);
        if(esfera != nullptr) {
            return intersectEsfera(*esfera);
        } else {
             Triangulo* triangulo = dynamic_cast<Triangulo*>(p);
             if(triangulo!=nullptr){
                 return intersectTriangulo(*triangulo);
             } else {
                return -1;
            }
        }
    }

}

Punto Ray::getPunto(){
    return _punto;
}

Direccion Ray::getDireccion(){
    return _direccion;
}