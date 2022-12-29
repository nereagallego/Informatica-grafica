#ifndef INTERSECT_HPP
#define INTERSECT_HPP


#include "../math/Punto.h"
#include "Primitive.h"
#include "../image/CImg.h"
#include "../scene/BSDF.h"
#include <memory>

using namespace std;

class BSDF;

struct Intersect{
    float _t;
    bool _intersect;
    Punto _punto;
    BSDF _emision;
    Direccion _normal; 
    double _u, _v;

    friend ostream& operator<<(ostream& os, const Intersect& it);
};


#endif