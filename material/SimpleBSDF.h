#pragma once

#include "../scene/BSDF.h"

class SimpleBSDF : public BSDF{
private:
    
public:

    SimpleBSDF(RGB emision, RGB ks, RGB kt): BSDF(emision, ks, kt){}

    SimpleBSDF(RGB emision, RGB ks, RGB kt, double nf): BSDF(emision, ks, kt, nf) {}

    SimpleBSDF(): BSDF() {}

    RGB eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal, const double u, const double v) override; 

    tuple<Direccion, RGB> sample(const Direccion omega0, const Punto x, const Direccion normal, const double u, const double v) override;
};