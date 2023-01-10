#include "Triangulo.h"

Direccion Triangulo::getNormal(){
    return _normal;
}

float Triangulo::getDistancia(){
    return _distancia;
}

Punto Triangulo::getX(){
    return _x;
}

Punto Triangulo::getY(){
    return _y;
}

Punto Triangulo::getZ(){
    return _z;
}

Intersect Triangulo::intersect(Ray r) {
    Intersect s;
    s._emision = this->getEmision();
    s._intersect = true;
    Direccion d1 = _y - _x;
    Direccion d2 = _z - _x;
    Direccion h = crossProduct(r.getDireccion(),d2);
    float a = d1*h; // determinante

    if (a > -0.00001 && a < 0.00001){
        s._intersect = false;
        return s;
    }
    

    Direccion s1 = r.getPunto() - _x;

    float u = (s1 * h);

    if ((a > 0.00001 && (u < 0.0 || u > a)) || (a < -0.00001 && (u > 0.0 || u < a))){
        s._intersect = false;
        return s;
    }

    Direccion q = crossProduct(s1, d1);

    float v = r.getDireccion() * q;

    if ((a > 0.00001 && (v < 0.0 || u + v > a)) || a < -0.00001 && (v > 0.0 || u + v < a)){
        s._intersect = false;
        return s;
    }
    
    float tt = (d2 * q)/a;
    if(tt < 0.0001){
        s._intersect = false;
        return s;
    }else{
        
    }
    s._t = tt;
    s._punto = r.getPunto() + r.getDireccion() * s._t;
    s._normal = this->getNormal();

    tuple<double,double> x = getUV(s._punto);
    s._u = get<0>(x);
    s._v = get<1>(x);
    return s;
}

//Rota en el eje X el triangulo. Para ello rota los 3 puntos que lo componen y lo vuelve a hacer
Triangulo Triangulo::rotateX(float rad){
    CoordenadasHomogeneas aux1(getX());
    CoordenadasHomogeneas aux2(getY());
    CoordenadasHomogeneas aux3(getZ());

    aux1 = aux1.rotacionX(rad);
    aux2 = aux2.rotacionX(rad);
    aux3 = aux3.rotacionX(rad);

    return Triangulo(aux1.punto(),aux2.punto(),aux3.punto());


}

//Rota en el eje Y el triangulo. Para ello rota los 3 puntos que lo componen y lo vuelve a hacer
Triangulo Triangulo::rotateY(float rad){
    CoordenadasHomogeneas aux1(getX());
    CoordenadasHomogeneas aux2(getY());
    CoordenadasHomogeneas aux3(getZ());

    aux1 = aux1.rotacionY(rad);
    aux2 = aux2.rotacionY(rad);
    aux3 = aux3.rotacionY(rad);

    return Triangulo(aux1.punto(),aux2.punto(),aux3.punto());


}

//Rota en el eje Z el triangulo. Para ello rota los 3 puntos que lo componen y lo vuelve a hacer
Triangulo Triangulo::rotateZ(float rad){
    CoordenadasHomogeneas aux1(getX());
    CoordenadasHomogeneas aux2(getY());
    CoordenadasHomogeneas aux3(getZ());

    aux1 = aux1.rotacionZ(rad);
    aux2 = aux2.rotacionZ(rad);
    aux3 = aux3.rotacionZ(rad);

    return Triangulo(aux1.punto(),aux2.punto(),aux3.punto());


}

tuple<double,double> Triangulo::getUV(Punto p){
    return {_ejeU * p, _ejeV * p};
}
