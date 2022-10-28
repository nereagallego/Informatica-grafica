#ifndef TRIANGULO_HPP
#define TRIANGULO_HPP

#include "../p1/Punto.h"
#include "Plano.h"
#include "../p1/Direccion.h"
#include "Primitive.h"

class Triangulo : public Primitive{
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
    Triangulo(Punto x, Punto y, Punto z): _x(x), _y(y), _z(z) {
        Direccion d1 = y-x;
        Direccion d2 = z-x;
        Direccion cross = crossProduct(d1,d2);
        _normal = cross / cross.modulo();
        _distancia = -(_normal*x);
    };

    Triangulo(Punto x, Punto y, Punto z, RGB emision): _x(x), _y(y), _z(z), Primitive(emision) {
        Direccion d1 = y-x;
        Direccion d2 = z-x;
        Direccion cross = crossProduct(d1,d2);
        _normal = cross / cross.modulo();
        _distancia = -(_normal*x);
    };


    Direccion getNormal();
    float getDistancia();
    Punto getX();
    Punto getY();
    Punto getZ();
};



#endif