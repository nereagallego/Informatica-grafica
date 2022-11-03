#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../color/RGB.h"
#include "Ray.h"
#include "Intersect.h"

using namespace std;

class Primitive{
    RGB _emision;
public:
    Primitive(RGB emision): _emision(emision){};
    Primitive(): _emision(RGB(0,0,0)) {}
    ~Primitive() = default;

    void setEmision(RGB emision) {
        _emision = emision;
    }

    RGB getEmision(){
        return _emision;
    }

    virtual Intersect intersect(Ray r) = 0;
};

#endif