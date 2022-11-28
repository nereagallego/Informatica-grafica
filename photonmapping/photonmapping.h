#pragma once

#include "../scene/Camera.h"
class PhotonMapping{
    Camera _cam;
    int _numPhotons;
public:
    PhotonMapping(Camera cam, int n): _cam(cam), _numPhotons(n) {}

    Imagen photonMapping();

    vector<Photon> ScatterPhotons(Light l, int n);
};