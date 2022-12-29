#pragma once

#include "../scene/BSDF.h"
#include "../image/CImg.h"

class Textura : public BSDF {

cimg_library::CImg<unsigned char> _texture;

    Textura(RGB emision, RGB ks, RGB kt, cimg_library::CImg<unsigned char> img): 
    BSDF(emision, ks, kt),
    _texture(img)
    {   }


    Textura(RGB emision, RGB ks, RGB kt, double nf,cimg_library::CImg<unsigned char> img): 
    BSDF(emision, ks, kt, nf),
    _texture(img)
        {}

     /**
     * @brief evalua el coeficiente difuso
     * 
     * @return RGB 
     */
    // creo que habrá que añadirle más parámetros
    RGB eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal, const double u, const double v) override;

    RGB muestrea(const double u, const double v, const Punto p);
};