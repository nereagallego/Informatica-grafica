#ifndef INTERSECT_HPP
#define INTERSECT


#include "../math/Punto.h"
using namespace std;

struct Intersect{
    float _t;
    bool _intersect;
    Punto _punto;
    RGB _emision;
    Direccion _normal;
};

#endif