#pragma once

#include "../scene/Camera.h"
#include <list>
#include "kdtree.h"

class PhotonMapping{
    Camera _cam;
    int _numPhotons; // numero shots(numero de fotones que se quiere lanzar)
public:
    PhotonMapping(Camera cam, int n): _cam(cam), _numPhotons(n) {}

    Imagen photonMapping();

    vector<Photon> ScatterPhotons(shared_ptr<Light> l, int n);

    //Guarda los rebotes dado un foton
    vector<Photon> siguientesRebotes(RGB energia, Punto origen, Direccion dirRayo);
};