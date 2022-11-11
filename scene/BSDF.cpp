#include "BSDF.h"

RGB BSDF::getDifuseCoefficient() const{
    return _difuseCoefficient;
}

void BSDF::setDifuseCoefficient(RGB emision){
    _difuseCoefficient = emision;
}

RGB BSDF::eval(Punto x, Direccion omegai, Direccion omega0){
    return _difuseCoefficient / M_PI;
}

tuple<Direccion, RGB> BSDF::sample(const float theta, const float phi, const Direccion omega0, const Punto x){
    double thethaInverse = acos(1-theta);
    double phiInverse = 2 * M_PI * phi;

    Direccion omegai = Direccion(sin(thethaInverse)*cos(phiInverse),sin(thethaInverse)*sin(phiInverse),cos(thethaInverse)).normalizar();

    return {omegai, eval(x,omegai,omega0)};
}