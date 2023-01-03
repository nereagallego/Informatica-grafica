#pragma once

#include "Primitive.h"
#include "OBJ_Loader.h"
#include "../scene/BSDF.h"
#include "Triangulo.h"

class Obj : public Primitive {
private:
    objl::Loader _loader;
    Punto _centro;
    Direccion _ejeX, _ejeY, _ejeZ;
public:

    Obj(string lod, Direccion ejeX, Direccion ejeY, Direccion ejeZ, Punto p, shared_ptr<BSDF> emision): Primitive(emision), _centro(p), _ejeX(ejeX), _ejeY(ejeY), _ejeZ(ejeZ) 
    {
        _loader.LoadFile(lod);
    }

    Obj(string lod, Direccion ejeX, Direccion ejeY, Direccion ejeZ, Punto p):  _centro(p), _ejeX(ejeX), _ejeY(ejeY), _ejeZ(ejeZ) 
    {
        _loader.LoadFile(lod);
    }

    /**
     * @brief Intersección de un rayo con el triangulo
     * 
     * @param r rayo con el que se quiere calcular la intersección
     * @return float 
     */
    Intersect intersect(Ray r);

};