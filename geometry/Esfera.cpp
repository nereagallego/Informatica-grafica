#include "Esfera.h"
// Esfera::Esfera(Direccion eje, Punto centro, Punto referencia){
//     Direccion rad = centro - referencia;
//     _radio = eje.modulo()/2;
//     if(abs(rad.modulo() - _radio) > 10E-6){
//         cerr << "Parámetros incorrectos " << endl;
//         cerr << "Radio: "  << _radio << " distancia del centro a la ciudad de referencia "  << rad.modulo() << endl;
//     }
//     _centro = centro;
//     _ejeY = eje.normalizar();
//     _referencia = referencia;
//     _ejeZ = rad.normalizar();
//     _ejeX = crossProduct(_ejeY,_ejeZ).normalizar();

// }

Punto Esfera::getCentro(){
    return _centro;
}


float Esfera::getRadio(){
    return _radio;
}

Intersect Esfera::intersect(Ray r){
    Intersect s;
    s._intersect = true;
    Direccion aux = r.getPunto() - _centro;
    float radicando = (r.getDireccion() * aux * 2) * (r.getDireccion() * aux * 2) - 4 * r.getDireccion().modulo() * r.getDireccion().modulo() * (aux.modulo() * aux.modulo() - _radio);
    if (radicando < 0) s._intersect = false;
    float delta = sqrt(radicando);
    float r1 = (-(r.getDireccion() * aux * 2) - delta) / (2 * r.getDireccion().modulo() * r.getDireccion().modulo());
    float r2 = (-(r.getDireccion() * aux * 2) + delta) / (2 * r.getDireccion().modulo() * r.getDireccion().modulo());
    if (r1 > 0 && r2 > 0 && r1 < r2) s._t = r1;
    else if(r2 > 0) s._t = r2;
    else s._intersect = false;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    return s;
}