#include "photonmapping.h"

//Esta función lanza un foton, lo dispersa por la imagen y devuelve la lista de fotones
vector<Photon> PhotonMapping::ScatterPhotons(Light l, int nPhotons){
   
    int i = 0;
    vector<Photon> photons;
    //Para cada foton...
    int shots;
    while ( i < nPhotons){
        Direccion dirAleatoria = l.sample();

        Ray r(dirAleatoria,l.getCenter());
     // lanzo rayo
     // hago x rebotes max n - i
        Intersect cercano;
        cercano._intersect = false;
        cercano._t = INFINITY;

        //Se mira con que intersecta el fotón
        for(auto p : _cam.getPrimitives()){
            Intersect intersect = p->intersect(r); 
            if(intersect._intersect && intersect._t < cercano._t && intersect._t > 0){
                cercano = intersect;
            }
        }

        if( cercano._intersect ) {

            Photon p(cercano._punto, r.getDireccion(),l.getLuminance(),cercano._normal);
            photons.push_back(p);
        }
        shots ++;
    }

    for(Photon p : photons){
        p.setFlux(4*M_PI*p.getFlux()/shots);
    }

}


Imagen PhotonMapping::photonMapping(){
    int n = 0;
    double total_lights = 0.0;
    for(Light l: _cam.getLights()){
        total_lights = total_lights + l.getLuminance();
    }

    for(Light l : _cam.getLights()){
        int numberPhotons = (l.getLuminance()/total_lights)*_numPhotons;
        
    }
}