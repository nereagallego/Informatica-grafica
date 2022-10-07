#include "Punto.h"

// Constructor de un punto dadas sus coordenadas
Punto::Punto(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

// Suma de un punto con una dirección resulta un punto
// Equivale a mover un punto en la dirección d una distancia |d|
// siendo |d| el módulo del vector d
Punto Punto::operator +(const Direccion d) const{
    return Punto(x+d.x, y + d.y, z + d.y);
}

// Resta de dos puntos
// Devuelve la dirección resultante de ir desde el punto p hasta este punto
Direccion Punto::operator -(const Punto p) const{
    return Direccion(x - p.x , y - p.y, z - p.z);
}

// Pretty stdout
ostream& operator<<(ostream& os, const Punto p) {
    os << "point: (" << p.x  << ", " << p.y << ", " << p.z << ")" ;
    return os;
}

// Devuelve la coordenada x del punto
float Punto::getX() const{
    return x;
}

// Devuelve la coordenada y del punto
float Punto::getY() const{
    return y;
}

// Devuelve la coordenada z del punto
float Punto::getZ() const{
    return z;
}