#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../p2/RGB.h"

using namespace std;

class Primitive{
    RGB _emision;
public:
    Primitive(RGB emision): _emision(emision){};
    Primitive(): _emision(RGB(0,0,0)) {}
    virtual ~Primitive() = default;

    void setEmision(RGB emision) {
        _emision = emision;
    }

    RGB getEmision(){
        return _emision;
    }
};

#endif