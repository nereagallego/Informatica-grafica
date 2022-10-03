#ifndef CORDENADAS_HOMOGENEAS_HPP
#define CORDENADAS_HOMOGENEAS_HPP

#include <stdlib.h>
#include "Punto.h"
#include "Direccion.h"
#include "Matrix4.h"
#include "vector"

class CoordenadasHomogeneas
{
private:
    
    CoordenadasHomogeneas(float x, float y, float z, float w);
public:
    float coord[4];
    CoordenadasHomogeneas(Punto p);
    CoordenadasHomogeneas(Direccion d);

    CoordenadasHomogeneas translacion(float x, float y, float z);

    CoordenadasHomogeneas escala(float x, float y, float z);

    CoordenadasHomogeneas rotacionX(float rad);
    
    CoordenadasHomogeneas rotacionY(float rad);

    CoordenadasHomogeneas rotacionZ(float rad);

    CoordenadasHomogeneas cambioBase(Matrix4 m);

    CoordenadasHomogeneas combinaciones(Matrix4 m);
};





#endif