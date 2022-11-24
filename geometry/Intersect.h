#ifndef INTERSECT_HPP
#define INTERSECT


#include "../math/Punto.h"
#include "Primitive.h"
using namespace std;

struct Intersect{
    float _t;
    bool _intersect;
    Punto _punto;
    BSDF _emision;
    Direccion _normal;
   
};

#endif