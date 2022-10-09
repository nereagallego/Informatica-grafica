#include "Punto.h"

Punto::Punto(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

Punto Punto::operator +(const Direccion d) const{
    return Punto(x+d.getX(), y + d.getY(), z + d.getZ());
}

Direccion Punto::operator -(const Punto p) const{
    return Direccion(x - p.x , y - p.y, z - p.z);
}

// Pretty stdout
ostream& operator<<(ostream& os, const Punto p) {
    os << "point: (" << p.x  << ", " << p.y << ", " << p.z << ")" ;
    return os;
}

float Punto::getX() const{
    return x;
}

float Punto::getY() const{
    return y;
}

float Punto::getZ() const{
    return z;
}