#include "CoordenadasHomogeneas.h"

CoordenadasHomogeneas::CoordenadasHomogeneas(const Punto p){
    coord[0] = p.getX();
    coord[1] = p.getY();
    coord[2] = p.getZ();
    coord[3] = 1;
}

CoordenadasHomogeneas::CoordenadasHomogeneas(const Direccion d){
    coord[0] = d.getX();
    coord[1] = d.getY();
    coord[2] = d.getZ();
    coord[3] = 0;
}

CoordenadasHomogeneas::CoordenadasHomogeneas(const float x, const float y, const float z, const float w){
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
    coord[3] = w;
}

CoordenadasHomogeneas CoordenadasHomogeneas::translacion(const float x, const float y, const float z) {

    return CoordenadasHomogeneas(coord[0]+coord[3]*x,coord[1]+coord[3]*y,coord[2]+coord[3]*z,coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::escala(const float x, const float y, const float z){
    return CoordenadasHomogeneas(coord[0]*x,coord[1]*y,coord[2]*z,coord[3]);
}


CoordenadasHomogeneas CoordenadasHomogeneas::rotacionX(const float rad){
    return CoordenadasHomogeneas(coord[0],coord[1]*cos(rad)-coord[2]*sin(rad),coord[1]*sin(rad)+coord[2]*cos(rad),coord[3]);
}
    
CoordenadasHomogeneas CoordenadasHomogeneas::rotacionY(const float rad){
    return CoordenadasHomogeneas(coord[0]*cos(rad)+coord[2]*sin(rad),coord[1],-coord[0]*sin(rad)+coord[2]*cos(rad),coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::rotacionZ(const float rad){
    return CoordenadasHomogeneas(coord[0]*cos(rad)-coord[1]*sin(rad),coord[0]*sin(rad)+coord[1]*cos(rad),coord[2],coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::cambioBase(Matrix4 m){
    vector<float> result = m*coord; 
    return CoordenadasHomogeneas(result[0],result[1],result[2],result[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::combinaciones(Matrix4 m){
    vector<float> result = m*coord;
    return CoordenadasHomogeneas(result[0],result[1],result[2],result[3]);
}

Punto CoordenadasHomogeneas::punto(){
    if(coord[3]!=1) throw new logic_error("No es un punto");
    return Punto(coord[0],coord[1],coord[2]);
}

Direccion CoordenadasHomogeneas::direccion(){
    if(coord[3]!=1) throw new logic_error("No es un vector");
    return Direccion(coord[0], coord[1],coord[2]);
}