#include "photonmapping.h"



vector<Photon> PhotonMapping::siguientesRebotes(RGB energia, Punto origen, Direccion dirRayo){
    vector<Photon> photons;
    //Si la energía es 0, absorbe
    if(energia.getRed() == 0 && energia.getBlue() == 0 && energia.getGreen() == 0) return photons;
    RGB _energy = energia;
    Punto _origin = origen;
    Direccion _direction = dirRayo;
    while(_energy.getRed() != 0 ||_energy.getGreen() != 0 || _energy.getBlue() != 0){
        Ray r(_direction,_origin);

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
            Photon p(cercano._punto, r.getDireccion(),_energy,cercano._normal);
            photons.push_back(p);
            tuple<Direccion,RGB> tupla = cercano._emision.sample(r.getDireccion(), cercano._punto,cercano._normal);
            Direccion dirRay = get<0>(tupla);
            RGB color_BSDF = get<1>(tupla);
            //Se le pasa el flujo computado con el BSDF
            photons.push_back(p);
            _energy = color_BSDF * _energy;
            _direction = dirRay;
            _origin = cercano._punto;

        } else return photons;
    }
    return photons;
}

//Esta función lanza un foton, lo dispersa por la imagen y devuelve la lista de fotones
vector<Photon> PhotonMapping::ScatterPhotons(Light l, int nPhotons){
   
    int i = 0;
    vector<Photon> photons;
    //Para cada foton...
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
            Photon p(cercano._punto, r.getDireccion(),l.getPower()*4*M_PI/nPhotons,cercano._normal);
            photons.push_back(p);
            tuple<Direccion,RGB> tupla = cercano._emision.sample(r.getDireccion(), cercano._punto,cercano._normal);
            Direccion dirRay = get<0>(tupla);
            RGB color_BSDF = get<1>(tupla);
            //Se le pasa el flujo computado con el BSDF
            vector<Photon> rebotes = siguientesRebotes(color_BSDF*p.getFlux(),cercano._punto, dirRay);
            for(Photon ph : rebotes){
                photons.push_back(ph);
            }
        }
        i++;
    }
    return photons;
}


struct PhotonAxisPosition {
    float operator()(const Photon& p, std::size_t i) const noexcept{
        return p.position(i);
    }
};

using PhotonMap = nn::KDTree<Photon,3,PhotonAxisPosition>;

/*
    Example function to generate the photon map with the given photons
*/
PhotonMap generation_photon_map(list<Photon> givenPhotons){
    std::list<Photon> photons = givenPhotons;        // Create a list of photons
    auto map = PhotonMap(photons, PhotonAxisPosition());
    return map;
}

Imagen PhotonMapping::photonMapping(){
    Imagen img(_cam.getNPixelsH(), _cam.getHPixelsW(),255,255);
    int n = 0;
    double total_lights = 0.0;
    list<Photon> photons;
    for(Light l: _cam.getLights()){
        total_lights = total_lights + l.getLuminance();
    }

    for(Light l : _cam.getLights()){
        int numberPhotons = (l.getLuminance()/total_lights)*_numPhotons;
        vector<Photon> p = ScatterPhotons(l,numberPhotons);
        for(Photon ph : p){
            photons.push_back(ph);
        }
        cout << photons.size() << endl;
        
        
    }

    // añadir los fotones al kdtree
    PhotonMap fotonmap= generation_photon_map(photons);

    /*********************************POST**********************/
    float progress = 0.0;
    std::cout << "[";
    float bar = 10 * _cam.getNPixelsH() * _cam.getHPixelsW() / 10;
    for(int i = 0; i < _cam.getNPixelsH(); i ++){
        for(int j = 0; j < _cam.getHPixelsW(); j ++){
            //Se crea un rayo aleatorio por pixel de la imagen
            float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_cam.getAnchura()));
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_cam.getAltura()));
            Punto centro(_cam.getReferencia().getX()+r1+_cam.getAnchura()*j,_cam.getReferencia().getY()-r2/2-_cam.getAltura()*i,_cam.getReferencia().getZ());
            Ray rayo(centro-_cam.getO(),_cam.getO());
            RGB contribucion;
            Intersect cercano;
            cercano._intersect = false;
            cercano._t = INFINITY;

            for(auto p : _cam.getPrimitives()){
                Intersect intersect = p->intersect(rayo); 
                if(intersect._intersect && intersect._t < cercano._t && intersect._t > 0){
                    cercano = intersect;

                }
                
            }
            float radius = 0.01;
            if( cercano._intersect ) {
                auto v = fotonmap.nearest_neighbors(cercano._punto,INFINITY,radius);
                RGB contribucion;
                //Utiliza box-kernel para la estimación
                for(auto photon : v){
                    RGB contribucionMaterial = cercano._emision.eval(cercano._punto,rayo.getDireccion(),photon->getIncidentDirection(),cercano._normal);
                    contribucion = contribucion + contribucionMaterial * photon->getFlux() / (M_PI *radius);
                }
                img._imagenHDR[i][j] = contribucion;
            } else {
                img._imagenHDR[i][j] = RGB();
            }
           // if(i*)
        }
    }


    return img;
}
