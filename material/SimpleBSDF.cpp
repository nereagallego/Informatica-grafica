#include "SimpleBSDF.h"

RGB SimpleBSDF::eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal, const double u, const double v){
    Direccion refract = refractionEval(x,omegai,normal);
    RGB diffuse = _probDiffuse > 0.00005 ? _diffuseCoefficient / _probDiffuse : RGB();
    RGB specular = _probSpecular > 0.00005 ? _specularCoefficient * delta(omega0,omegai) / _probSpecular : RGB();
    RGB refraction = _probRefract > 0.00005 ? _refractCoefficient * delta(omegai, omega0) /_probRefract : RGB();
    return diffuse + specular + refraction;
}

tuple<Direccion, RGB> SimpleBSDF::sample(const Direccion omega0, const Punto x, const Direccion normal, const double u, const double v){
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