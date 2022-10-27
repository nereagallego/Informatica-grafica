#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../p1/Direccion.h"
#include "../p2/RGB.h"
#include "Primitive.h"
#include "Ray.h"

#include <vector>

using namespace std;
const int nPixels = 1080;
class Camera{
private:
    Direccion _L;
    Direccion _U;
    Direccion _F;
    Punto _O;
    RGB cuadricula[nPixels][nPixels];
    float _altura, _anchura;
    Punto _referenciaPixel;
    

public:
    Camera(Direccion l, Direccion u , Direccion f, Punto o);

    Direccion getL();
    Direccion getU();
    Direccion getF();
    Punto getO();

    void dibujar(vector<Primitive> vector);
};


#endif