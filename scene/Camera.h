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
#include "Light.h"

using namespace std;

class Camera{
private:
    Direccion _L;
    Direccion _U;
    Direccion _F;
    Punto _O;
    int _nPixelsh, _nPixelsw;
    float _altura, _anchura;
    Punto _referenciaPixel;

    vector<shared_ptr<Primitive>> _primitives;
    vector<Light> _lights;

    
    float max(float a, float b, float c, float d) const;

public:
    /**
     * @brief Construct a new Camera object
     * Construye una cámara dados sus tres vectores de dirección el punto de 
     * origen y la cantidad de píxeles que tiene en altura y anchura
     * 
     * @param l vector left de la cámara
     * @param u vector up de la cámara
     * @param f vector forward de la cámara
     * @param o punto de origen de la cámara
     * @param nPixelsh altura en píxeles
     * @param nPixelsw anchura en píxeles
     */
    Camera(Direccion l, Direccion u , Direccion f, Punto o, int nPixelsh, int nPixelsw);

    Direccion getL();
    Direccion getU();
    Direccion getF();
    Punto getO();

    /**
     * @brief Devuelve la imagen con las primitivas que se hayan introducido 
     * previamente
     * 
     * @return Imagen 
     */
    Imagen dibujar();

    /**
     * @brief Añade una nueva primitiva a la imagen
     * 
     * @param p primitiva a añadir
     */
    void addPrimitive(shared_ptr<Primitive> p);

    void addLight(Light l);

    RGB calcularLuz(Direccion direccionRayo, Intersect intersection);
};


#endif