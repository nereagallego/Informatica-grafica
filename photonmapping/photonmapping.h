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
    
    /**
     * @brief reparte los fotones por la escena dada una cantidad de luces y un 
     * número máximo de lanzamientos
     * 
     * @param l vector de luces
     * @param n cantidad de lanzamientos de fotones
     * @return vector<Photon>
    */
    vector<Photon> ScatterPhotons(shared_ptr<Light> l, int n);

    /**
     * @brief guarda los rebotes del lanzamiento de un fotón
     * 
     * @param energía energía con la que entra el fotón 
     * @param origen origen del anterior rebote
     * @param dirRayo dirección con la que entra el fotón
     * @return vector<Photon>
    */
    vector<Photon> siguientesRebotes(RGB energia, Punto origen, Direccion dirRayo);


    /**
     * @brief Función auxliair para el cómputo del color de cada pixel
     * 
    */
    void work(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays, int x, nn::KDTree<Photon,3,PhotonAxisPosition>& fotonmap);

    /**
     * @brief estimación de densidad de fotones en un punto dado
     * 
     * @param cercano intersección en la que se calcula la estimación de 
     *                densidad
     * @param rayo rayo entrante en la intersección
     * @param v vector de fotones cercanos a la intersección
    */
    RGB photonDensityStim(Intersect cercano, Ray rayo, const vector<const Photon*>& v);
public:

    /**
     * @brief contruye un photonmapper dada una cámara y el número de fotones
     * 
     * @param cam parámetros de la cámara
     * @param n numero de fotones
    */
    PhotonMapping(Camera cam, int n): _cam(cam), _numPhotons(n), radius(0.08f) {}

    /**
     * @brief return a image computed with photon mapping
     * 
     * @return Imagen
    */
    Imagen photonMapping();

    

    

    
};