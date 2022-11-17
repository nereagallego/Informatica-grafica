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
    RGB _difuseCoefficient;
public:
    BSDF(RGB emision): _difuseCoefficient(emision) {}
    RGB getDifuseCoefficient() const;
    void setDifuseCoefficient(RGB emision);

    /**
     * @brief evalua el coeficiente difuso
     * 
     * @return RGB 
     */
    // creo que habrá que añadirle más parámetros
    RGB eval(Punto x, Direccion omegai, Direccion omega0);

    tuple<Direccion, RGB> sample(const Direccion omega0, const Punto x, const Direccion normal);
};

#endif