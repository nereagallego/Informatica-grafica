#include "Texturas.h"

RGB Textura::eval(Punto x, Direccion omegai, Direccion omega0, Direccion normal, const double u, const double v) {
        
    RGB diffuse = _probDiffuse > 0.00005 ? muestrea(u,v, x) / _probDiffuse : RGB();
    RGB specular = _probSpecular > 0.00005 ? _specularCoefficient * delta(omega0,omegai) / _probSpecular : RGB();
    RGB refraction = _probRefract > 0.00005 ? _refractCoefficient * delta(omegai, omega0) /_probRefract : RGB();
    return diffuse + specular + refraction;
}



RGB Textura::muestrea(const double u, const double v, const Punto p){
    int auxU = u*_texture.height();
    int auxV = v*_texture.width();
    //cout << "Los valores de aux son " << u<< "  " << v << endl;
    if(auxV > 0 && auxU > 0 && auxU <= _texture.height() && auxV <= _texture.width()){
        cout << "Los valores de aux son " << u<< "  " << v << endl;
        cout << " y el RGB es " << RGB();
        return RGB(_texture(auxU,auxV,0,0),_texture(auxU,auxV,0,1),_texture(auxU,auxV,0,2));
    }else{
        return RGB();
    }
}

tuple<Direccion, RGB> Textura::sample(const Direccion omega0, const Punto x, const Direccion normal, const double u, const double v){
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