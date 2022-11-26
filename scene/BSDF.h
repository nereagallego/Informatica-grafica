#ifndef BSDF_HPP
#define BSDF_HPP

#include "../color/RGB.h"
#include "../math/Direccion.h"
#include "../math/Punto.h"
#include <cmath>
#include <random>
#include <tuple>
#include "../math/Matrix4.h"
#include "../math/CoordenadasHomogeneas.h"
#include <assert.h>
#include <algorithm>

using namespace std;

enum BSDFType { DIFFUSE, SPECULAR, REFRACTION, ABSORTION};

class BSDF{
    RGB _diffuseCoefficient, _specularCoefficient, _refractCoefficient;

    double _refractIndex;
    double _probDiffuse, _probSpecular, _probRefract;

    /**
     * @brief Devuelve la dirección de la luz cuando el elemento es difuso
     * 
     * @param x punto de insercción
     * @param omega0 dirección de incidencia
     * @param normal dirección normal
     * @return Direccion 
     */
    Direccion diffuseEval(Punto x, Direccion omega0, Direccion normal);

    /**
     * @brief Devuelve la dirección de la luz cuando el elemento es especular
     * 
     * @param x punto de insercción
     * @param omega0 dirección de incidencia
     * @param normal dirección normal
     * @return Direccion 
     */
    Direccion specularEval(Punto x, Direccion omega0, Direccion normal);

    /**
     * @brief Devuelve la dirección de la luz cuando el elemento refracta
     * 
     * @param x punto de insercción
     * @param omega0 dirección de incidencia
     * @param normal dirección normal
     * @param indexRefraction n0
     * @return Direccion 
     */
    Direccion refractionEval(Punto x, Direccion omega0, Direccion normal);

    BSDFType roussianRoulete() const;
public:
    BSDF(RGB emision, RGB ks, RGB kt): 
    _diffuseCoefficient(emision),
    _specularCoefficient(ks),
    _refractCoefficient(kt),
    _refractIndex(1),
    _probDiffuse(max(_diffuseCoefficient.getRed(),max(_diffuseCoefficient.getGreen(), _diffuseCoefficient.getBlue()))), 
    _probSpecular(max(_specularCoefficient.getRed(),max(_specularCoefficient.getGreen(), _specularCoefficient.getBlue()))), 
    _probRefract(max(_refractCoefficient.getRed(),max(_refractCoefficient.getGreen(), _refractCoefficient.getBlue()))) 
        {
            assert((_probDiffuse + _probRefract + _probSpecular)<=1);
        }
    BSDF(RGB emision, RGB ks, RGB kt, double nf): 
    _diffuseCoefficient(emision),
    _specularCoefficient(ks),
    _refractCoefficient(kt),
    _refractIndex(nf),
    _probDiffuse(max(_diffuseCoefficient.getRed(),max(_diffuseCoefficient.getGreen(), _diffuseCoefficient.getBlue()))), 
    _probSpecular(max(_specularCoefficient.getRed(),max(_specularCoefficient.getGreen(), _specularCoefficient.getBlue()))), 
    _probRefract(max(_refractCoefficient.getRed(),max(_refractCoefficient.getGreen(), _refractCoefficient.getBlue()))) 
        {
            assert((_probDiffuse + _probRefract + _probSpecular)<=1);
        }
    BSDF():
    _diffuseCoefficient(RGB()),
    _specularCoefficient(RGB()),
    _refractCoefficient(RGB()),
    _refractIndex(1),
    _probDiffuse(0),
    _probRefract(0),
    _probSpecular(0)
    {}
    RGB getDifuseCoefficient() const;
    void setDifuseCoefficient(RGB emision);
    RGB getSpecularCoefficient() const;
    void setSpecularCoefficient(RGB emision);
    RGB getRefractCoefficient() const;

    void setRefractCoefficient(RGB emision);
   
    double getRefractIndex() const;
    void setRefractIndex(double a);

    
    /**
     * @brief evalua el coeficiente difuso
     * 
     * @return RGB 
     */
    // creo que habrá que añadirle más parámetros
     RGB eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal);

    tuple<Direccion, RGB> sample(const Direccion omega0, const Punto x, const Direccion normal);

    
};

#endif