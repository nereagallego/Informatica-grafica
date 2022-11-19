#include "Direccion.h"


Direccion::Direccion(float x, float y, float z){
    _x = x;
    _y = y;
    _z = z;
}

Direccion Direccion::operator +(const Direccion d2){
    return Direccion(_x + d2._x, _y + d2._y, _z + d2._z);
   
}

Direccion Direccion::operator -(const Direccion d2){
    return  Direccion(_x-d2._x, _y - d2._y, _z - d2._z);
}

Direccion Direccion::operator *(const float d2){
    return Direccion(_x*d2, _y*d2 ,_z*d2);
}

Direccion Direccion::operator /(const float d2){
    if(d2==0) throw new logic_error("No se puede dividir por 0");
    return Direccion(_x/d2, _y/d2 ,_z/d2);
}

Punto Direccion::operator +(const Punto p){
    return Punto(_x+p.getX(), _y + p.getY(), _z +p.getZ());
}

float Direccion::modulo(){
    return sqrt(_x*_x+_y*_y+_z*_z);
}

Direccion Direccion::normalizar(){
    float modulo = this->modulo();
    return Direccion(_x/modulo,_y/modulo,_z/modulo);
}

float Direccion::operator *(const Direccion d) {
    return _x*d._x+_y*d._y+_z*d._z;
}

float Direccion::operator *(const Punto p){
    return _x*p.getX()+ _y * p.getY() + _z*p.getZ();
}

float Direccion::getX() const{
    return _x;
}

float Direccion::getY() const{
    return _y;
}

float Direccion::getZ() const{
    return _z;
}

Direccion crossProduct(Direccion d1, Direccion d2){
    return Direccion(d1.getY()*d2.getZ()-d1.getZ()*d2.getY(),d1.getZ()*d2.getX()-d1.getX()*d2.getZ(),d1.getX()*d2.getY()-d1.getY()*d2.getX());
}

// Pretty stdout
ostream& operator<<(ostream& os, const Direccion p) {
    os << "direction: (" << p._x  << ", " << p._y << ", " << p._z << ")" ;
    return os;
}

Direccion perpendicular(const Direccion d){
     if ( (d.getZ() != 0) && (-d.getX() != d.getY()) ) {
        return Direccion(d.getZ(), d.getZ(), - d.getX() - d.getY());
    } else {
        return Direccion(d.getY() - d.getZ(), d.getX(), d.getX());
    }
}

double Direccion::angulo(Direccion d) {
    double sin = (_x*d._x+_y*d._y+_z*d._z) / (this->modulo() * d.modulo());
    return asin(sin);
}
