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
#include "BSDF.h"
#include <random>
#include <thread>
#include <mutex>
#include "../accelerator/PoolThreads.h"

using namespace std;

const int NTHREADS = 24;

struct Pixel {
    int x, y;
    RGB contribution;
};

class Camera{
private:
    Direccion _L;
    Direccion _U;
    Direccion _F;
    Punto _O;
    int _nPixelsh, _nPixelsw;
    float _altura, _anchura;
    Punto _referenciaPixel;
    int numRays = 128;
    mutex mtx;

    uint32_t threads;

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

    /**
     * @brief Añadir una luz a la escena
     * 
     * @param l 
     */
    void addLight(Light l);

    /**
     * @brief Calcular la luz directa
     * 
     * @param direccionRayo 
     * @param intersection 
     * @return RGB 
     */
    RGB nextEventEstimation(Direccion direccionRayo, Intersect intersection);

    /**
     * @brief calcula el path tracing para una cantidad n de rebotes
     * 
     * @param r 
     * @param n 
     * @return RGB 
     */
    RGB pathTracing(Ray r);

    void work(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays);
};


#endif