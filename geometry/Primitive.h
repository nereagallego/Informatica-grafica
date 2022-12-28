#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../scene/BSDF.h"
#include "Ray.h"
#include "Intersect.h"

using namespace std;

// abstract class 
class Primitive{
    // color del objeto
    BSDF _emision;
   
public:
    /**
     * @brief Construct a new Primitive object
     * 
     * @param emision color del objeto
     */
    Primitive(BSDF emision): _emision(emision){};


    /**
     * @brief Construct a new Primitive object
     * Se le asigna color negro por defecto
     * 
     */
    Primitive(): _emision(BSDF()){}

    /**
     * @brief Destroy the Primitive object
     * 
     */
    ~Primitive() = default;

    void setEmision(BSDF emision) {
        _emision = emision;
    }

    BSDF getEmision(){
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