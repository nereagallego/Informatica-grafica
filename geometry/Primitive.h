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
    cimg_library::CImg<double> _texture;
public:
    /**
     * @brief Construct a new Primitive object
     * 
     * @param emision color del objeto
     */
    Primitive(BSDF emision): _emision(emision){};

   Primitive(cimg_library::CImg<double> texture): _texture(texture){}; 


    Primitive(BSDF emision, cimg_library::CImg<double> texture): _emision(emision), _texture(texture){};

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

    cimg_library::CImg<unsigned char> getTexture(){
        return _texture;
    }

    void setTexture(cimg_library::CImg<unsigned char> texture){
        _texture = texture;
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