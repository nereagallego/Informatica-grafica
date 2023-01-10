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
    Direccion _normal, _ejeU, _ejeV;
    float _distancia;
public:
    /**
     * @brief Construct a new Plano object
     * 
     * @param normal direccioón normal al plano
     * @param d disancia del plano al origen
     */
    Plano(Direccion normal,float d): 
        _normal(normal.normalizar()), 
        _distancia(d),
        _ejeU(perpendicular(normal).normalizar()),
        _ejeV(crossProduct(_normal, _ejeU)) 
        {
        };

    /**
     * @brief Construct a new Plano object
     * 
     * @param normal direccioón normal al plano
     * @param d disancia del plano al origen
     * @param emision coluor del plano
     */
    Plano(Direccion normal, float d, shared_ptr<BSDF> emision): 
        _normal(normal.normalizar()), 
        _distancia(d), 
        Primitive(emision),
        _ejeU(perpendicular(normal).normalizar()),
        _ejeV(crossProduct(_normal, _ejeU))
        {
        };

    float getDistancia();
    Direccion getNormal();

    /**
     * @brief Intersección de un rayo con el plano
     * 
     * @param r 
     * @return float 
     */
    Intersect intersect(Ray r) override;

    tuple<double,double> getUV(Punto p);
};

#endif