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
    RGB diffuse = _probDiffuse > 0 ? _diffuseCoefficient * _probDiffuse / M_PI : RGB();
    RGB specular = _probSpecular > 0 ? _probSpecular * delta(omega0,omegai) / (normal * omegai) : RGB(0,0,0);
    RGB refraction = _probRefract > 0 ? _probRefract * delta(omegai, omega0) / (normal * omegai) : RGB(0,0,0);
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

    return {newOmegai, eval(x,newOmegai,omega0, normal)};
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
