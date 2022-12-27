#ifndef BSDF_HPP
#define BSDF_HPP

#include "../color/RGB.h"
#include "../math/Direccion.h"
#include "../math/Punto.h"
#include <cmath>
#include "../math/rand.h"
#include <tuple>
#include "../math/Matrix4.h"
#include "../math/CoordenadasHomogeneas.h"
#include <assert.h>
#include <algorithm>
#include "../math/rand.h"

using namespace std;

enum BSDFType { DIFFUSE, SPECULAR, REFRACTION, ABSORTION, EMITER};

class BSDF{
    RGB _diffuseCoefficient, _specularCoefficient, _refractCoefficient;
    RGB _emision;

    double _refractIndex;
    double _probDiffuse, _probSpecular, _probRefract;
    bool _emiter;

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
    _emiter(false),
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
    _emiter(false),
    _probDiffuse(max(_diffuseCoefficient.getRed(),max(_diffuseCoefficient.getGreen(), _diffuseCoefficient.getBlue()))), 
    _probSpecular(max(_specularCoefficient.getRed(),max(_specularCoefficient.getGreen(), _specularCoefficient.getBlue()))), 
    _probRefract(max(_refractCoefficient.getRed(),max(_refractCoefficient.getGreen(), _refractCoefficient.getBlue()))) 
        {
            assert((_probDiffuse + _probRefract + _probSpecular)<=1);
        }

    BSDF(RGB emision): _emiter(true), _emision(emision) {}
    
    BSDF():
    _diffuseCoefficient(RGB()),
    _specularCoefficient(RGB()),
    _refractCoefficient(RGB()),
    _refractIndex(1),
    _probDiffuse(0),
    _probRefract(0),
    _probSpecular(0),
    _emiter(false)
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
     * @param x punto de intersección donde se evalua
     * @param omegai direccion de salida donde se evalua
     * @param omega0 dirección de entrada donde se evalua
     * @param normal normal a la superficie
     * @return RGB 
     */
    RGB eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal);

    /**
     * @brief samplea una muestra dada la dirección de entrada, el punto de 
     *        entrada y la dirección normal a la superficie. 
     *        Devuelve la dirección de salida, el color de salida y el tipo de 
     *        material que es
     * 
     * @param omega0 dirección de entrada
     * @param x punto de sampleo
     * @param normal dirección normal a la superficie
     */
    tuple<Direccion, RGB, BSDFType> sample(const Direccion omega0, const Punto x, const Direccion normal);

    
};

#endif