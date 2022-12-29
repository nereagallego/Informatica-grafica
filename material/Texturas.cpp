#include "Texturas.h"

RGB Textura::eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal, const double u, const double v) {
        
    RGB diffuse = _probDiffuse > 0.00005 ? muestrea(u,v, x) / _probDiffuse : RGB();
    RGB specular = _probSpecular > 0.00005 ? _specularCoefficient * delta(omega0,omegai) / _probSpecular : RGB();
    RGB refraction = _probRefract > 0.00005 ? _refractCoefficient * delta(omegai, omega0) /_probRefract : RGB();
    return diffuse + specular + refraction;
}



RGB Textura::muestrea(const double u, const double v, const Punto p){
    return RGB(_texture(u,v,0,0),_texture(u,v,0,1),_texture(u,v,0,2));
}