#include "Esfera.h"

Esfera::Esfera(Direccion _eje, Punto _centro, Punto _referencia){
    Direccion rad = _centro - _referencia;
    if(rad.modulo() != _eje.modulo()/2){
        cerr << "Parámetros incorrectos " << endl;
    }
    centro = _centro;
    eje = _eje;
    referencia = _referencia;
}