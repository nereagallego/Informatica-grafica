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
    Direccion ejeY,ejeX,ejeZ;
    Punto centro;
    Punto referencia;
    float radio;
public:
    /**
     * @brief Construct a new Esfera object
     * 
     * @param _eje eje de la esfera
     * @param _centro centro de la esfera
     * @param _referencia punto de referencia de la esfera
     */
    Esfera(Direccion _eje, Punto _centro, Punto _referencia);

    /**
     * @brief devuelve el punto dado su azimuth y su inclinación
     * 
     * @param incl inclinación (en radianes)
     * @param azim azimuth (en radianes)
     * @return Punto 
     */
    Punto pointDefinition(float incl, float azim);
};

#endif