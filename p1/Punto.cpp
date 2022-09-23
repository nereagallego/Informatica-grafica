#include "Punto.h"


Punto::Punto(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

Punto Punto::operator +(Direccion d){
    return Punto(x+d.x, y + d.y, z + d.y);
}

Direccion Punto::operator -(Punto p){
    return Direccion(x - p.x , y - p.y, z - p.z);
}
