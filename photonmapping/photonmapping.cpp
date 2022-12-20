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
            if(cercano._emision.getSpecularCoefficient().getRed() > 0){
              //  cout << "aqui" << endl;
            }
            tuple<Direccion,RGB, BSDFType> tupla = cercano._emision.sample(r.getDireccion(), cercano._punto,cercano._normal);
            Direccion dirRay = get<0>(tupla);
            RGB color_BSDF = get<1>(tupla);
            BSDFType type = get<2>(tupla);
            //Se le pasa el flujo computado con el BSDF
            if(type == DIFFUSE)
                photons.push_back(p);
            _energy = color_BSDF * _energy;
            _direction = dirRay;
            _origin = cercano._punto;

        } else return photons;
    }
    return photons;
}

//Esta función lanza un foton, lo dispersa por la imagen y devuelve la lista de fotones
vector<Photon> PhotonMapping::ScatterPhotons(shared_ptr<Light> l, int nPhotons){
   
    int i = 0;
    vector<Photon> photons;
    //Para cada foton...
    while ( i < nPhotons){
        Direccion dirAleatoria = l->sample();

        Ray r(dirAleatoria,l->getCenter());
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

        if( cercano._intersect) {
            Photon p(cercano._punto, r.getDireccion(),l->getPower()*4*M_PI/nPhotons,cercano._normal);
            photons.push_back(p);
            tuple<Direccion,RGB, BSDFType> tupla = cercano._emision.sample(r.getDireccion(), cercano._punto,cercano._normal);
            Direccion dirRay = get<0>(tupla);
            RGB color_BSDF = get<1>(tupla);
            BSDFType type = get<2>(tupla);
            //Se le pasa el flujo computado con el BSDF
            
            vector<Photon> rebotes = siguientesRebotes(color_BSDF*p.getFlux(),cercano._punto, dirRay);
            if(type == DIFFUSE){
                rebotes.push_back(p);
            }
            for(Photon ph : rebotes){
                photons.push_back(ph);
            }
            i++;
            
            
        }
        
    }
    return photons;
}

using PhotonMap = nn::KDTree<Photon,3,PhotonAxisPosition>;

/*
    Example function to generate the photon map with the given photons
*/
nn::KDTree<Photon,3,PhotonAxisPosition> generation_photon_map(list<Photon> givenPhotons){
    std::list<Photon> photons = givenPhotons;        // Create a list of photons
    auto map = PhotonMap(photons, PhotonAxisPosition());
    return map;
}

Imagen PhotonMapping::photonMapping(){
    Imagen img(_cam.getNPixelsH(), _cam.getHPixelsW(),255,255);
    int n = 0;
    double total_lights = 0.0;
    list<Photon> photons;
    for(shared_ptr<Light> l: _cam.getLights()){
        total_lights = total_lights + l->getLuminance();
    }

    for(shared_ptr<Light> l : _cam.getLights()){
        int numberPhotons = (l->getLuminance()/total_lights)*_numPhotons;
        vector<Photon> p = ScatterPhotons(l,numberPhotons);
        for(Photon ph : p){
            photons.push_back(ph);
        }
        cout << photons.size() << endl;
        
        
    }

    // añadir los fotones al kdtree
    nn::KDTree<Photon,3,PhotonAxisPosition> fotonmap= generation_photon_map(photons);

    /*********************************POST**********************/
    
   
    cout << "[" ;
    cout.flush();
    
    float bar = 5 * _cam.getNPixelsH() * _cam.getHPixelsW() / 100;
    float progress = bar;
    for(int i = 0; i < _cam.getNPixelsH(); i ++){
        for(int j = 0; j < _cam.getHPixelsW(); j ++){
            img._imagenHDR[i][j] = RGB(0,0,0);
            for(int k = 0; k < _cam.getNumRays(); k++){
                //Se crea un rayo aleatorio por pixel de la imagen
                float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_cam.getAnchura()));
                float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_cam.getAltura()));
                Punto centro(_cam.getReferencia().getX()+r1+_cam.getAnchura()*j,_cam.getReferencia().getY()-r2/2-_cam.getAltura()*i,_cam.getReferencia().getZ());
                Direccion dirRayo = centro-_cam.getO();
                Ray rayo(dirRayo,_cam.getO());
                RGB contribucion;
                bool breakW = false;
                while(!breakW){
                    Intersect cercano;
                    cercano._intersect = false;
                    cercano._t = INFINITY;

                    for(shared_ptr<Light> l : _cam.getLights()){
                        shared_ptr<AreaLight> aL = dynamic_pointer_cast<AreaLight>(l);
                        if(aL != nullptr){
                            Intersect inter  = aL->intersect(rayo);
                            if(inter._intersect){
                            // cout << "Intersecta con el area Light" << endl;
                               img._imagenHDR[i][j] = img._imagenHDR[i][j] + aL->getPower();
                               breakW = true;
                            }
                            
                            
                        }
                    }

                    for(auto p : _cam.getPrimitives()){
                        Intersect intersect = p->intersect(rayo); 
                        if(intersect._intersect && intersect._t < cercano._t && intersect._t > 0){
                            cercano = intersect;

                        }
                        
                    }
                    
                    if( cercano._intersect ) {
                        tuple<Direccion,RGB, BSDFType> tupla = cercano._emision.sample(rayo.getDireccion(),cercano._punto,cercano._normal);
                        Direccion dirRay = get<0>(tupla);
                        RGB color_BSDF = get<1>(tupla);
                        BSDFType type = get<2>(tupla);
                        
                        if(type == DIFFUSE){
                            auto v = fotonmap.nearest_neighbors(cercano._punto,INFINITY,radius);
                            
                            contribucion = contribucion + photonDensityStim(cercano,rayo, v);
                            img._imagenHDR[i][j] = img._imagenHDR[i][j] + contribucion;
                            breakW = true;
                            
                        } else if(type == SPECULAR || type == REFRACTION){
                        //  img._imagenHDR[i][j] = img._imagenHDR[i][j] + nextEventEstimation(rayo.getDireccion(),cercano);
                            rayo = Ray(dirRay,cercano._punto);
                        //  contribucion = contribucion + _cam.pathTracing(rayo);
                        }
                    } 
                }
                
                if(i*_cam.getHPixelsW() + j >= progress) {
                    cout << "=";
                    cout.flush();
                    progress +=bar;
                }
            }
            img._imagenHDR[i][j] = img._imagenHDR[i][j] / _cam.getNumRays();
        }
    }
    cout << "]"<< endl;


    return img;
}

RGB PhotonMapping::photonDensityStim(Intersect cercano, Ray rayo, const vector<const Photon*>& v ){
    RGB contribucion;
    //auto v = fotonmap.nearest_neighbors(cercano._punto,INFINITY,radius);
    //Utiliza box-kernel para la estimación
    for(auto photon : v){
        RGB contribucionMaterial = cercano._emision.eval(cercano._punto,rayo.getDireccion(),photon->getIncidentDirection(),cercano._normal) / M_PI;
        
        // gaussian kernel ?
        Direccion dist = cercano._punto - photon->getPosition();
        float alpha = 0.918, beta = 1.953;
        float gaussianKernel = alpha * (1 - ((1 - exp(-beta*dist.modulo()*dist.modulo()/(2 * radius* radius)))/(1-exp(-beta))));
        contribucion = contribucion + contribucionMaterial * photon->getFlux() / (M_PI * radius * radius);
    }
    return contribucion;
}