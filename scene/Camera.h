#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/Direccion.h"
#include "../color/RGB.h"
#include "../geometry/Primitive.h"
#include "../geometry/Ray.h"
#include "../image/Imagen.h"
#include "../math/Matrix4.h"
#include "../math/CoordenadasHomogeneas.h"
#include <memory>
#include <time.h>
#include <vector>

using namespace std;
const static int nPixels = 16;
class Camera{
private:
    Direccion _L;
    Direccion _U;
    Direccion _F;
    Punto _O;
    RGB cuadricula[nPixels][nPixels];
    float _altura, _anchura;
    Punto _referenciaPixel;

    vector<shared_ptr<Primitive>> _primitives;
    
    float max(float a, float b, float c, float d) const;

public:
    Camera(Direccion l, Direccion u , Direccion f, Punto o);

    Direccion getL();
    Direccion getU();
    Direccion getF();
    Punto getO();
    void getCuadricula(RGB vector[nPixels][nPixels]);

    void dibujar();

    void save() const;

    void addPrimitive(shared_ptr<Primitive> p);
};


#endif