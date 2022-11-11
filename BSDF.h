#ifndef BSDF_HPP
#define BSDF_HPP

#include "../color/RGB.h"
#include <cmath>

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
    RGB eval() const;
};

#endif