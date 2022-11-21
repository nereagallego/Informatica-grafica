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

using namespace std;

enum BSDFType { DIFFUSE, SPECULAR, REFRACTION, ABSORTION};

class BSDF{
    RGB _diffuseCoefficient, _specularCoefficient, _refractionCoefficient;
    double _probDiffuse, _probSpecular, _probRefract;

    double _refractionIndex;

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
    BSDF(RGB kd = RGB(), RGB ks = RGB(), RGB kt = RGB(), const double nf = 1): _diffuseCoefficient(kd), _specularCoefficient(ks), _refractionCoefficient(kt), _refractionIndex(nf), _probDiffuse(max(_diffuseCoefficient.getRed(),max(_diffuseCoefficient.getGreen(), _diffuseCoefficient.getBlue()))), _probSpecular(max(_specularCoefficient.getRed(),max(_specularCoefficient.getGreen(), _specularCoefficient.getBlue()))), _probRefract(max(_refractionCoefficient.getRed(),max(_refractionCoefficient.getGreen(), _refractionCoefficient.getBlue()))) {assert((_probDiffuse + _probRefract + _probSpecular)<=1);}
    RGB getDiffuseCoefficient() const;
    void setDiffuseCoefficient(RGB emision);
    RGB getSpecularCoefficient() const;
    void setSpecularCoefficient(RGB ks);
    RGB getRefractionCoefficient() const;
    void setRefractionCoefficient(RGB kt);
    double getRefractionIndex() const;
    void setRefractionIndex(const double ni);

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