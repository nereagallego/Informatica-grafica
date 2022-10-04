#include "Esfera.h"

Esfera::Esfera(Direccion _eje, Punto _centro, Punto _referencia){
    
    Direccion rad = _centro - _referencia;
    if(abs(rad.modulo() - _eje.modulo()/2) < 0.000006){
        cerr << "Parámetros incorrectos " << endl;
    }
    centro = _centro;
    eje = _eje;
    referencia = _referencia;
}

Punto Esfera::pointDefinition(float incl, float azim){
    if(incl < 0 or incl > M_PI or azim < - M_PI or azim > M_PI){
        cout << "Parametros no válidos." << endl;
    }
    float r = eje.modulo()/2;
    return Punto(r*sin(incl)*cos(azim), r*sin(incl)*sin(azim), r * cos(incl));
}