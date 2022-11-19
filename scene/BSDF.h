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

using namespace std;

class BSDF{
    RGB _difuseCoefficient, _specularCoefficient, _refractionCoefficient;

    double _refractionIndex;
public:
    BSDF(RGB kd = RGB(), RGB ks = RGB(), RGB kt = RGB(), const double ni = 1): _difuseCoefficient(kd), _specularCoefficient(ks), _refractionCoefficient(kt), _refractionIndex(ni) {}
    RGB getDifuseCoefficient() const;
    void setDifuseCoefficient(RGB emision);
    RGB getSpecularCoefficient() const;
    void setSpecularCoefficient(RGB ks);
    RGB getRefractionCoefficient() const;
    void setRefractionCoefficient(RGB kt);
    double getRefractionIndex() const;
    void setRefractionIndex(double ni);

    /**
     * @brief evalua el coeficiente difuso
     * 
     * @return RGB 
     */
    // creo que habrá que añadirle más parámetros
    RGB eval(Punto x, Direccion omegai, Direccion omega0);

    tuple<Direccion, RGB> sample(const Direccion omega0, const Punto x, const Direccion normal);

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
    Direccion refractionEval(Punto x, Direccion omega0, Direccion normal, double index0);

};

#endif