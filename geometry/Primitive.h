#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "../scene/BSDF.h"
#include "Ray.h"
#include "Intersect.h"
#include <memory>
#include "../material/SimpleBSDF.h"

using namespace std;

// abstract class 
class Primitive{
    // color del objeto
    shared_ptr<BSDF> _emision;
   
public:
    /**
     * @brief Construct a new Primitive object
     * 
     * @param emision color del objeto
     */
    Primitive(shared_ptr<BSDF> emision): _emision(emision){};


    /**
     * @brief Construct a new Primitive object
     * Se le asigna color negro por defecto
     * 
     */
    Primitive(): _emision(make_shared<SimpleBSDF>(RGB(0,0,0),RGB(0,0,0),RGB(0,0,0))){}

    /**
     * @brief Destroy the Primitive object
     * 
     */
    ~Primitive() = default;

    void setEmision(shared_ptr<BSDF> emision) ;

    shared_ptr<BSDF> getEmision();


    /**
     * @brief virtual intersect function with a ray
     * 
     * @param r rayo con el que intersecta
     * @return Intersect 
     */
    virtual struct Intersect intersect(Ray r) = 0;
};

#endif