#ifndef ESFERA_HPP
#define ESFERA_HPP


#include "Direccion.h"
#include <cmath>
#include <iostream>
#include "CoordenadasHomogeneas.h"

class Punto;
class Direccion;

class Esfera {
private:
    Direccion _ejeY,_ejeX,_ejeZ;
    Punto _centro;
    Punto _referencia;
    float _radio;
public:
    /**
     * @brief Construct a new Esfera object
     * 
     * @param eje eje de la esfera
     * @param centro centro de la esfera
     * @param referencia punto de referencia de la esfera
     */
    Esfera(Direccion eje, Punto centro, Punto referencia);

    /**
     * @brief devuelve el punto dado su azimuth y su inclinación
     * 
     * @param incl inclinación (en radianes)
     * @param azim azimuth (en radianes)
     * @return Punto 
     */
    Punto pointDefinition(float incl, float azim);

    Direccion getEjeY();
    Direccion getEjeX();
    Direccion getEjeZ();
    Punto getCentro();
    Punto getReferencia();
    float getRadio();
};

#endif