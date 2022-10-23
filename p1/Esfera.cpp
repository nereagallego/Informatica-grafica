#include "Esfera.h"

Esfera::Esfera(Direccion eje, Punto centro, Punto referencia){
    
    Direccion rad = centro - referencia;
    _radio = eje.modulo()/2;
    if(abs(rad.modulo() - _radio) > 10E-6){
        cerr << "Parámetros incorrectos " << endl;
        cerr << "Radio: "  << _radio << " distancia del centro a la ciudad de referencia "  << rad.modulo() << endl;
    }
    _centro = centro;
    _ejeY = eje.normalizar();
    _referencia = referencia;
    _ejeZ = rad.normalizar();
    _ejeX = crossProduct(_ejeY,_ejeZ).normalizar();

}

Punto Esfera::pointDefinition(float incl, float azim){
    if(incl < 0 or incl > M_PI or azim < - M_PI or azim > M_PI){
        cout << "Parametros no válidos." << endl;
    }
    Punto point(_radio*sin(incl)*cos(azim), _radio*sin(incl)*sin(azim), _radio * cos(incl));
    // Se obtiene la normal a la superficie restando la ciudad de la referencia - centro
    float v[4][4] = {{_ejeX.getX(),_ejeY.getX(),_ejeZ.getX(),_centro.getX()},{_ejeX.getY(),_ejeY.getY(),_ejeZ.getY(),_centro.getY()},{_ejeX.getZ(),_ejeY.getZ(),_ejeZ.getZ(),_centro.getZ()},{0,0,0,1}};
    Matrix4 T(v);

    CoordenadasHomogeneas w(point);
    
    return w.cambioBase(T).punto();
}

Direccion Esfera::getEjeY(){
    return _ejeY;
}

Direccion Esfera::getEjeX(){
    return _ejeX;
}

Direccion Esfera::getEjeZ(){
    return _ejeZ;
}

Punto Esfera::getCentro(){
    return _centro;
}

Punto Esfera::getReferencia(){
    return _referencia;
}

float Esfera::getRadio(){
    return _radio;
}