#include "BSDF.h"

RGB BSDF::getDiffuseCoefficient() const{
    return _diffuseCoefficient;
}

void BSDF::setDiffuseCoefficient(RGB emision){
    _diffuseCoefficient = emision;
}

RGB BSDF::getSpecularCoefficient() const{
    return _specularCoefficient;
}

void BSDF::setSpecularCoefficient(RGB ks){
    _specularCoefficient = ks;
}

RGB BSDF::getRefractionCoefficient() const{
    return _refractionCoefficient;
}

void BSDF::setRefractionCoefficient(RGB kt){
    _refractionCoefficient = kt;
}

double BSDF::getRefractionIndex() const{
    return _refractionIndex;
}

void BSDF::setRefractionIndex(const double ni){
    _refractionIndex = ni;
}

RGB BSDF::eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal){
    cout << "He entrado en eval" << endl;
    RGB diffuse = _probDiffuse > 0 ? _diffuseCoefficient / M_PI / _probDiffuse : RGB();
    RGB specular = _probSpecular > 0 ? _specularCoefficient * delta(omega0,omegai) / (normal * omegai) / _probSpecular : RGB();
    RGB refraction = _probRefract > 0 ? _refractionCoefficient * delta(omegai, omega0) / (normal * omegai) /_probRefract: RGB();
    return diffuse + specular + refraction;
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
        sample = refractionEval(x, omega0, normal,1.0);
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

Direccion BSDF::refractionEval(Punto x, Direccion omega0, Direccion normal, double index0){
    double thetaI = asin(omega0.angulo(normal) * index0 / _refractionIndex);
    Direccion omegai(sin(thetaI),cos(thetaI),0.0);

    Direccion perp = perpendicular(normal);
    Matrix4 local(perp,normal,crossProduct(perp,normal),x);

    Matrix4 inv = local.inversa();

    CoordenadasHomogeneas omegai2(omegai);

    Direccion newOmegai = omegai2.cambioBase(inv).direccion();

    return newOmegai;
}


BSDFType BSDF::roussianRoulete() const {
    double prob = fRand(0.0,1.0);
    if(prob < _probDiffuse) return DIFFUSE;
    else if(prob < _probDiffuse + _probSpecular) return SPECULAR;
    else if(prob < _probDiffuse + _probSpecular + _probRefract) return REFRACTION;
    else return ABSORTION;
}