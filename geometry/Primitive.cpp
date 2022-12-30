#include "Primitive.h"

void Primitive::setEmision(shared_ptr<BSDF> emision) {
    _emision = emision;
}

shared_ptr<BSDF> Primitive::getEmision(){
    return _emision;
}