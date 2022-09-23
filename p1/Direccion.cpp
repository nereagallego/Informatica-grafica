#include "Direccion.h"


Direccion::Direccion(float x_, float y_, float z_){
    x = x_;
    y = y_;
    z = z_;
}

Direccion Direccion::operator +(Direccion d2){
    return Direccion(x + d2.x, y + d2.y, z + d2.z);
   
}

Direccion Direccion::operator -(Direccion d2){
    return  Direccion(x-d2.x, y - d2.y, z - d2.z);
}
Direccion Direccion::operator *(float d2){
    return Direccion(x*d2, y*d2 ,z*d2);
}
Direccion Direccion::operator /(float d2){
    return Direccion(x/d2, y/d2 ,z/d2);
}

Punto Direccion::operator +(Punto p){
    return Punto(x+p.x, y + p.y, z +p.z);
}


float Direccion::modulo(){
    return sqrt(x*x+y*y+z*z);
}

Direccion Direccion::normalizar(){
    float modulo = this->modulo();
    return Direccion(x/modulo,y/modulo,z/modulo);
}
