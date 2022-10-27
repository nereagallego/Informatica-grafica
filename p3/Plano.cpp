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