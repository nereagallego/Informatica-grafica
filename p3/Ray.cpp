#include "Ray.h"

Ray::Ray(const Direccion d, const Punto p){
    _direccion = d;
    _punto = p;
}

float Ray::intersect(Plano p){
    float denominador = _direccion*p.getNormal();
    if (denominador == 0) return -1;
    return -(p.getDistancia() + p.getNormal()*_punto)/(denominador); 
}

float Ray::intersect(Esfera e){
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


float Ray::intersect(Triangulo t){
    Plano p = Plano(t.getNormal(), t.getDistancia());
    float dist = intersect(p);
    if(dist == -1) return -1;
    else{
        Direccion d1 = t.getY()-t.getX();
        Direccion d2 = t.getZ()-t.getX(); 
        
        
    }
    
}

Punto Ray::getPunto(){
    return _punto;
}

Direccion Ray::getDireccion(){
    return _direccion;
}