#ifndef PLANO_HPP
#define PLANO_HPP

#include <cmath>
#include <iostream>
#include "../math/Direccion.h"
#include "Primitive.h"

#include "../image/CImg.h"


using namespace std;

class Ray;

class Plano : public Primitive {
private:
    Direccion _normal;
    float _distancia;
public:
    /**
     * @brief Construct a new Plano object
     * 
     * @param normal direccioón normal al plano
     * @param d disancia del plano al origen
     */
    Plano(Direccion normal,float d): _normal(normal), _distancia(d){};

    //Plano(Direccion normal,float d, cimg_library::CImg<float> texture): _normal(normal), _distancia(d), Primitive(texture){};

    /**
     * @brief Construct a new Plano object
     * 
     * @param normal direccioón normal al plano
     * @param d disancia del plano al origen
     * @param emision color del plano
     */
    Plano(Direccion normal, float d, BSDF emision): _normal(normal), _distancia(d), Primitive(emision) {};

    //Plano(Direccion normal, float d, BSDF emision, cimg_library::CImg<float> texture): _normal(normal), _distancia(d), Primitive(emision,texture){};

    float getDistancia();
    Direccion getNormal();

    /**
     * @brief Intersección de un rayo con el plano
     * 
     * @param r 
     * @return float 
     */
    Intersect intersect(Ray r) override;
};

#endif