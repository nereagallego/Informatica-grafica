#ifndef TRIANGULO_HPP
#define TRIANGULO_HPP

#include "../p1/Punto.h"
#include "Plano.h"
#include "../p1/Direccion.h"

class Triangulo{
private:
    Punto _x, _y, _z;
    Direccion _normal;
    float _distancia;
public:
    /**
     * @brief Construct a new Triangulo object
     * Construye un triángulo dados tres puntos
     * 
     * @param x punto x
     * @param y punto y
     * @param z punto z
     */
    Triangulo(Punto x, Punto y, Punto z);

    Direccion getNormal();
    float getDistancia();
    Punto getX();
    Punto getY();
    Punto getZ();
};



#endif