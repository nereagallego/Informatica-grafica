#pragma once

#include "../geometry/Plano.h"
#include "Primitive.h"

using namespace std;

class Cuadrado : public Primitive{
private:
    Punto _p1, _p2, _p3, _p4;
    Plano _p;
public:
    Cuadrado(Direccion normal, float d, Punto center, Punto p1, Punto p2, Punto p3, Punto p4):  _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p(Plano(normal,d)) 
        {
            if(normal * p1 + d != 0) throw logic_error("el punto p1 no pertenece al plano de la luz de area");
            if(normal * p2 + d != 0) throw logic_error("el punto p2 no pertenece al plano de la luz de area"); 
            if(normal * p3 + d != 0) throw logic_error("el punto p3 no pertenece al plano de la luz de area");
            if(normal * p4 + d != 0) throw logic_error("el punto p4 no pertenece al plano de la luz de area");
        }

    Cuadrado(Direccion normal, float d, Punto center, Punto p1, Punto p2, Punto p3, Punto p4, shared_ptr<BSDF> emission):  _p1(p1), _p2(p2), _p3(p3), _p4(p4), _p(Plano(normal,d)), Primitive(emission) 
        {
            if(normal * p1 + d != 0) throw logic_error("el punto p1 no pertenece al plano de la luz de area");
            if(normal * p2 + d != 0) throw logic_error("el punto p2 no pertenece al plano de la luz de area"); 
            if(normal * p3 + d != 0) throw logic_error("el punto p3 no pertenece al plano de la luz de area");
            if(normal * p4 + d != 0) throw logic_error("el punto p4 no pertenece al plano de la luz de area");
        }

    Intersect intersect(Ray r) override;
};