#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../color/RGB.h"
#include "Ray.h"
#include "Intersect.h"

using namespace std;

// abstract class 
class Primitive{
    // color del objeto
    RGB _emision;
public:
    /**
     * @brief Construct a new Primitive object
     * 
     * @param emision color del objeto
     */
    Primitive(RGB emision): _emision(emision){};

    /**
     * @brief Construct a new Primitive object
     * Se le asigna color negro por defecto
     * 
     */
    Primitive(): _emision(RGB(0,0,0)) {}

    /**
     * @brief Destroy the Primitive object
     * 
     */
    ~Primitive() = default;

    void setEmision(RGB emision) {
        _emision = emision;
    }

    RGB getEmision(){
        return _emision;
    }

    /**
     * @brief virtual intersect function with a ray
     * 
     * @param r rayo con el que intersecta
     * @return Intersect 
     */
    virtual Intersect intersect(Ray r) = 0;
};

#endif