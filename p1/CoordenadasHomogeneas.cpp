#include "CoordenadasHomogeneas.h"

CoordenadasHomogeneas::CoordenadasHomogeneas(const Punto p){
    _coord[0] = p.getX();
    _coord[1] = p.getY();
    _coord[2] = p.getZ();
    _coord[3] = 1;
}

CoordenadasHomogeneas::CoordenadasHomogeneas(const Direccion d){
    _coord[0] = d.getX();
    _coord[1] = d.getY();
    _coord[2] = d.getZ();
    _coord[3] = 0;
}

CoordenadasHomogeneas::CoordenadasHomogeneas(const float x, const float y, const float z, const float w){
    _coord[0] = x;
    _coord[1] = y;
    _coord[2] = z;
    _coord[3] = w;
}

CoordenadasHomogeneas CoordenadasHomogeneas::translacion(const float x, const float y, const float z) {

    return CoordenadasHomogeneas(_coord[0]+_coord[3]*x,_coord[1]+_coord[3]*y,_coord[2]+_coord[3]*z,_coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::escala(const float x, const float y, const float z){
    return CoordenadasHomogeneas(_coord[0]*x,_coord[1]*y,_coord[2]*z,_coord[3]);
}


CoordenadasHomogeneas CoordenadasHomogeneas::rotacionX(const float rad){
    return CoordenadasHomogeneas(_coord[0],_coord[1]*cos(rad)-_coord[2]*sin(rad),_coord[1]*sin(rad)+_coord[2]*cos(rad),_coord[3]);
}
    
CoordenadasHomogeneas CoordenadasHomogeneas::rotacionY(const float rad){
    return CoordenadasHomogeneas(_coord[0]*cos(rad)+_coord[2]*sin(rad),_coord[1],-_coord[0]*sin(rad)+_coord[2]*cos(rad),_coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::rotacionZ(const float rad){
    return CoordenadasHomogeneas(_coord[0]*cos(rad)-_coord[1]*sin(rad),_coord[0]*sin(rad)+_coord[1]*cos(rad),_coord[2],_coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::cambioBase(Matrix4 m){
    vector<float> result = m*_coord; 
    return CoordenadasHomogeneas(result[0],result[1],result[2],result[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::combinaciones(Matrix4 m){
    vector<float> result = m*_coord;
    return CoordenadasHomogeneas(result[0],result[1],result[2],result[3]);
}

Punto CoordenadasHomogeneas::punto(){
    if(_coord[3]!=1) throw new logic_error("No es un punto");
    return Punto(_coord[0],_coord[1],_coord[2]);
}

Direccion CoordenadasHomogeneas::direccion(){
    if(_coord[3]!=1) throw new logic_error("No es un vector");
    return Direccion(_coord[0], _coord[1],_coord[2]);
}

// Pretty stdout
ostream& operator<<(ostream& os, const CoordenadasHomogeneas c) {
    os << "(" << c._coord[0]  << ", " << c._coord[1] << ", " << c._coord[2] << ", " << c._coord[3] << ")" ;
    return os;
}