#pragma once

#include "../scene/Camera.h"
#include <list>
#include "kdtree.h"
#include <mutex>

struct PhotonAxisPosition {
    float operator()(const Photon& p, std::size_t i) const noexcept{
        return p.position(i);
    }
};

class PhotonMapping{
    Camera _cam;
    int _numPhotons; // numero shots(numero de fotones que se quiere lanzar)

    uint32_t threads;
     nn::KDTree<Photon,3,PhotonAxisPosition> fotonmap;
     mutex mtx;
    float radius; 
public:
    PhotonMapping(Camera cam, int n): _cam(cam), _numPhotons(n), radius(0.08f) {}

    Imagen photonMapping();

    vector<Photon> ScatterPhotons(shared_ptr<Light> l, int n);

    //Guarda los rebotes dado un foton
    vector<Photon> siguientesRebotes(RGB energia, Punto origen, Direccion dirRayo);

    void work(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays, int x);

    RGB rayTracing(Ray r);

    RGB photonDensityStim(Intersect cercano, Ray rayo, const vector<const Photon*>& v);
};