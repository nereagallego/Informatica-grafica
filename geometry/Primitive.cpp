#include "Primitive.h"

void Primitive::setEmision(BSDF emision) {
    _emision = emision;
}

BSDF Primitive::getEmision(){
    return _emision;
}