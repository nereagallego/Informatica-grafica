/*
Description :   This is an example of usage of the KDTree class. It does not
                compile, but should give you the idea of how to integrate the
                KDTree in your code
*/


#include "kdtree.h"
#include "../math/Punto.h"
#include "Photon.h"

/* 
    An additional struct that allows the KD-Tree to access your photon position
*/
struct PhotonAxisPosition {
    float operator()(const Photon& p, std::size_t i) const noexcept{
        return p.position(i);
    }
};

/* 
    The KD-Tree ready to work in 3 dimensions, with YourPhoton s, under a 
    brand-new name: YourPhotonMap 
*/
using PhotonMap = nn::KDTree<Photon,3,PhotonAxisPosition>;


/*
    Example function to generate the photon map with the given photons
*/
PhotonMap generation_of_photon_map(list<Photon> givenPhotons){
    std::list<Photon> photons = givenPhotons;        // Create a list of photons
    auto map = PhotonMap(photons, PhotonAxisPosition());
    return map;
}

/*
    Example method to search for the nearest neighbors of the photon map
*/
void search_nearest(PhotonMap map,Punto position, float radius, unsigned long nPhotons){
    // Position to look for the nearest photons
    Punto query_position = position;    

    // Maximum number of photons to look for
    unsigned long nphotons_estimate = nPhotons;

    // Maximum distance to look for photons
    float radius_estimate = radius;

    // nearest is the nearest photons returned by the KDTree
    auto nearest = map.nearest_neighbors(position,
                                         nphotons_estimate,
                                         radius_estimate);
}



