#include "Plano.h"


// Plano::Plano(Direccion n, float d){
//     _normal = n;
//     _distancia = d;
// }

float Plano::getDistancia(){
    return _distancia;
}

Direccion Plano::getNormal(){
    return _normal;
}

float Plano::intersect(Ray r) {
    float denominador = r.getDireccion() * _normal;
    if(denominador == 0) return -1;
    return -(_distancia + _normal * r.getPunto())/denominador;
}