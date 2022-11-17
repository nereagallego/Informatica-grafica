#include "BSDF.h"

RGB BSDF::getDifuseCoefficient() const{
    return _difuseCoefficient;
}

void BSDF::setDifuseCoefficient(RGB emision){
    _difuseCoefficient = emision;
}

RGB BSDF::eval(Punto x, Direccion omegai, Direccion omega0){
    return _difuseCoefficient / M_PI;
}

double fRand(double fMin,double fMax){
   std::uniform_real_distribution<double> unif(fMin,fMax);
   std::default_random_engine re;
   re.seed(rand()%10000);
   double a_random_double = unif(re);
   return a_random_double;
}

tuple<Direccion, RGB> BSDF::sample(const Direccion omega0, const Punto x){
    double theta = fRand(0.0,1.0);
    double phi = fRand(0.0,1.0);
    double thethaInverse = acos(sqrt(1-theta));
    double phiInverse = 2 * M_PI * phi;

    Direccion omegai = Direccion(sin(thethaInverse)*cos(phiInverse),sin(thethaInverse)*sin(phiInverse),cos(thethaInverse)).normalizar();

    return {omegai, eval(x,omegai,omega0)};
}
