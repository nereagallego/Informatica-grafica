#include "BSDF.h"

RGB BSDF::getDifuseCoefficient() const{
    return _difuseCoefficient;
}

void BSDF::setDifuseCoefficient(RGB emision){
    _difuseCoefficient = emision;
}

RGB BSDF::eval() const{
    return _difuseCoefficient / M_PI;
}