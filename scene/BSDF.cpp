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

RGB BSDF::eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal){
    RGB diffuse = _probDiffuse > 0 ? _diffuseCoefficient * _probDiffuse / M_PI : RGB();
    RGB specular = _probSpecular > 0 ? _specularCoefficient * delta(omega0,omegai) * _probSpecular / (normal * omegai) : RGB();
//   RGB refraction = _probRefract > 0 ? _refractionCoefficient * delta(omegai, omega0) / (normal * omegai) /_probRefract: RGB();
    return diffuse ;
}

double fRand(double fMin,double fMax){
   std::uniform_real_distribution<double> unif(fMin,fMax);
   std::default_random_engine re;
   re.seed(rand()%10000);
   double a_random_double = unif(re);
   return a_random_double;
}

tuple<Direccion, RGB> BSDF::sample(const Direccion omega0, const Punto x, const Direccion normal){
    Direccion sample;
    BSDFType f = roussianRoulete();

    if(f == DIFFUSE){
        sample = diffuseEval(x,omega0,normal);
    } else if(f == SPECULAR){
        sample = specularEval(x, omega0, normal);
    } else if(f == REFRACTION){
        sample = Direccion();//refractionEval(x, omega0, normal);
    } else {
        return {Direccion(), RGB()};
    }
    return {sample, eval(x,sample,omega0, normal)};
}

Direccion BSDF::diffuseEval(Punto x, Direccion omega0, Direccion normal){
    double theta = fRand(0.0,1.0);
    double phi = fRand(0.0,1.0);
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
    double prob = fRand(0.0,1.0);
    if(prob < _probDiffuse) return DIFFUSE;
    else if(prob < _probDiffuse + _probSpecular) return SPECULAR;
    else if(prob < _probDiffuse + _probSpecular + _probRefract) return REFRACTION;
    else return ABSORTION;
}