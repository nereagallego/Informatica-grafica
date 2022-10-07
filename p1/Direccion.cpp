#include "Direccion.h"


Direccion::Direccion(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

Direccion Direccion::operator +(const Direccion d2){
    return Direccion(x + d2.x, y + d2.y, z + d2.z);
   
}

Direccion Direccion::operator -(const Direccion d2){
    return  Direccion(x-d2.x, y - d2.y, z - d2.z);
}

Direccion Direccion::operator *(const float d2){
    return Direccion(x*d2, y*d2 ,z*d2);
}

Direccion Direccion::operator /(const float d2){
    return Direccion(x/d2, y/d2 ,z/d2);
}

Punto Direccion::operator +(const Punto p){
    return Punto(x+p.getX(), y + p.getY(), z +p.getZ());
}

float Direccion::modulo(){
    return sqrt(x*x+y*y+z*z);
}

Direccion Direccion::normalizar(){
    float modulo = this->modulo();
    return Direccion(x/modulo,y/modulo,z/modulo);
}

float Direccion::operator *(const Direccion d) {
    return x*d.x+y*d.y+z*d.z;
}

float Direccion::getX() const{
    return x;
}

float Direccion::getY() const{
    return y;
}

float Direccion::getZ() const{
    return z;
}

Direccion crossProduct(Direccion d1, Direccion d2){
    return Direccion(d1.getY()*d2.getZ()-d1.getZ()*d2.getY(),d1.getZ()*d2.getX()-d1.getX()*d2.getZ(),d1.getX()*d2.getY()-d1.getY()*d2.getX());
}

// Pretty stdout
ostream& operator<<(ostream& os, const Direccion p) {
    os << "direction: (" << p.x  << ", " << p.y << ", " << p.z << ")" ;
    return os;
}