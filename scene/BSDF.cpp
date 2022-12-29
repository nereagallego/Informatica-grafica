#include "BSDF.h"

RGB BSDF::getDifuseCoefficient() const{
    return _diffuseCoefficient;
}

void BSDF::setDifuseCoefficient(RGB emision){
    _diffuseCoefficient = emision;
}

RGB BSDF::getSpecularCoefficient() const{
    return _specularCoefficient;
}

void BSDF::setSpecularCoefficient(RGB emision){
    _specularCoefficient = emision;
}

RGB BSDF::getRefractCoefficient() const{
    return _refractCoefficient;
}

void BSDF::setRefractCoefficient(RGB emision){
    _refractCoefficient = emision;
}

double BSDF::getRefractIndex() const{
    return _refractIndex;
}

void BSDF::setRefractIndex(double a){
    _refractIndex = a;
}

RGB BSDF::eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal, const double u, const double v){
    Direccion refract = refractionEval(x,omegai,normal);
    RGB diffuse = _probDiffuse > 0.00005 ? _diffuseCoefficient / _probDiffuse : RGB();
    RGB specular = _probSpecular > 0.00005 ? _specularCoefficient * delta(omega0,omegai) / _probSpecular : RGB();
    RGB refraction = _probRefract > 0.00005 ? _refractCoefficient * delta(omegai, omega0) /_probRefract : RGB();
    return diffuse + specular + refraction;
}

tuple<Direccion, RGB> BSDF::sample(const Direccion omega0, const Punto x, const Direccion normal, const double u, const double v){
    Direccion sample;
    BSDFType f = roussianRoulete();

    if(f == DIFFUSE){
        sample = diffuseEval(x,omega0,normal);
    } else if(f == SPECULAR){
        sample = specularEval(x, omega0, normal);
    } else if(f == REFRACTION){
        sample = refractionEval(x,omega0,normal);//refractionEval(x, omega0, normal);
    } else {
        return {Direccion(), RGB()};
    }
    return {sample, eval(x,sample,omega0, normal,u,v)};
}

Direccion BSDF::diffuseEval(Punto x, Direccion omega0, Direccion normal){
    double theta = Rand::fRand(0.0,1.0);
    double phi = Rand::fRand(0.0,1.0);
    double thethaInverse = acos(sqrt(1-theta));
    double phiInverse = 2 * M_PI * phi;

    Direccion omegai = Direccion(sin(thethaInverse)*cos(phiInverse),sin(thethaInverse)*sin(phiInverse),cos(thethaInverse)).normalizar();

    Direccion perp = perpendicular(normal);
    Matrix4 local(perp,normal,crossProduct(perp,normal),x);

    Matrix4 inv = local.inversa();

    CoordenadasHomogeneas omegai2(omegai);

    Direccion newOmegai = omegai2.cambioBase(inv).direccion();

    return newOmegai;
}

Direccion BSDF::specularEval(Punto x, Direccion omega0, Direccion normal){
    return omega0 - normal * 2 * (omega0 * normal) ;
}

BSDFType BSDF::roussianRoulete() const {
    double prob = Rand::fRand(0.0,1.0);
    if(prob < _probDiffuse) return DIFFUSE;
    else if(prob < _probDiffuse + _probSpecular) return SPECULAR;
    else if(prob < _probDiffuse + _probSpecular + _probRefract) return REFRACTION;
    else return ABSORTION;
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
Direccion BSDF::refractionEval(Punto x, Direccion omega0, Direccion normal){
    float cosi = omega0.normalizar() * normal < -1 ? -1 : 1 <  omega0.normalizar() * normal? 1: omega0.normalizar() * normal; 
    Direccion n = normal;
    float etai = 1, etat = _refractIndex; 
    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= normal*-1; } 
    float eta = etai / etat; 
    float k = 1 - eta * eta * (1 - cosi * cosi); 
    return k < 0 ? omega0 : omega0.normalizar() *  eta +  n * (eta * cosi - sqrtf(k)); 
}