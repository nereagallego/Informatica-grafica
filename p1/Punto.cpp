#include "Punto.h"

Punto::Punto(float x_, float y_, float z_){
    _x = x_;
    _y = y_;
    _z = z_;
}

Punto Punto::operator +(const Direccion d) const{
    return Punto(_x+d.getX(), _y + d.getY(), _z + d.getZ());
}

Direccion Punto::operator -(const Punto p) const{
    return Direccion(_x - p._x , _y - p._y, _z - p._z);
}

// Pretty stdout
ostream& operator<<(ostream& os, const Punto p) {
    os << "point: (" << p._x  << ", " << p._y << ", " << p._z << ")" ;
    return os;
}

float Punto::getX() const{
    return _x;
}

float Punto::getY() const{
    return _y;
}

float Punto::getZ() const{
    return _z;
}

float Punto::operator *(const Direccion d){
    return _x*d.getX() + _y*d.getY() + _z*d.getZ();
}