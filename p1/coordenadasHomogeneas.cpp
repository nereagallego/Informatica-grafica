#include "coordenadasHomogeneas.h"

CoordenadasHomogeneas::CoordenadasHomogeneas(Punto p){
    coord[0] = p.x;
    coord[1] = p.y;
    coord[2] = p.z;
    coord[3] = 1;
}

CoordenadasHomogeneas::CoordenadasHomogeneas(Direccion d){
    coord[0] = d.x;
    coord[1] = d.y;
    coord[2] = d.z;
    coord[3] = 0;
}

CoordenadasHomogeneas::CoordenadasHomogeneas(float x, float y, float z, float w){
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
    coord[3] = w;
}

CoordenadasHomogeneas CoordenadasHomogeneas::translacion(float x, float y, float z){
    return CoordenadasHomogeneas(coord[0]+coord[3]*x,coord[1]+coord[3]*y,coord[2]+coord[3]*z,coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::escala(float x, float y, float z){
    return CoordenadasHomogeneas(coord[0]*x,coord[1]*y,coord[2]*z,coord[3]);
}


CoordenadasHomogeneas CoordenadasHomogeneas::rotacionX(float rad){
    return CoordenadasHomogeneas(coord[0],coord[1]*cos(rad)-coord[2]*sin(rad),coord[1]*sin(rad)+coord[2]*cos(rad),coord[3]);
}
    
CoordenadasHomogeneas CoordenadasHomogeneas::rotacionY(float rad){
    return CoordenadasHomogeneas(coord[0]*cos(rad)+coord[2]*sin(rad),coord[1],-coord[0]*sin(rad)+coord[2]*cos(rad),coord[3]);
}

CoordenadasHomogeneas CoordenadasHomogeneas::rotacionZ(float rad){
    return CoordenadasHomogeneas(coord[0]*cos(rad)-coord[1]*sin(rad),coord[0]*sin(rad)+coord[1]*cos(rad),coord[2],coord[3]);
}