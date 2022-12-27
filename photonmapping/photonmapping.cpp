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

        Ray r(dirAleatoria,l->samplePoint());
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
    Imagen img(_cam.getNPixelsH(), _cam.getNPixelsW(),255,255);
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
  //  nn::KDTree<Photon,3,PhotonAxisPosition> 
    fotonmap= generation_photon_map(photons);

    /*********************************POST**********************/
    
    srand (time(NULL));
    ConcurrentQueue<pair<int,int>> jobs;
    ConcurrentQueue<Pixel> result;
    int x = 5*_cam.getNPixelsH() * _cam.getNPixelsW() / 100;
    cout << "[" ;
    cout.flush();
    for(int i = 0; i < _cam.getNPixelsH(); i ++){
        for(int j = 0; j < _cam.getNPixelsW(); j ++){
            jobs.push(make_pair(i, j));
        }
    }

    for(int i = 0; i<NTHREADS; i++) {
        jobs.push(make_pair(-1,-1));
    }
    
    vector<thread> threads;  
    for (int i = 0; i<NTHREADS; i++) {
        threads.push_back(std::thread([&](ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays, int x, nn::KDTree<Photon,3,PhotonAxisPosition>& fotonmap){ work(jobs,result,_cam.getNumRays(), x, fotonmap); }, std::ref(jobs),std::ref(result),_cam.getNumRays(),x, std::ref(fotonmap)));
    }

    //Wait for end
    for (auto &th : threads) {
        th.join();
    }

    cout << "]" << endl;
    cout.flush();

    queue<Pixel> qresult = result.getQueue();
    while (!qresult.empty())
    {
        Pixel a = qresult.front();

        img._imagenHDR[a.x][a.y] = a.contribution;
        qresult.pop();

    }
    return img;
}

RGB PhotonMapping::photonDensityStim(Intersect cercano, Ray rayo, const vector<const Photon*>& v ){
    RGB contribucion;
    //Utiliza box-kernel para la estimación
    for(auto photon : v){
        RGB contribucionMaterial = cercano._emision.eval(cercano._punto,rayo.getDireccion(),photon->getIncidentDirection(),cercano._normal);
        
        // gaussian kernel ?
        Direccion dist = cercano._punto - photon->getPosition();
        if(dist.modulo() > radius) throw logic_error("Distancia mayor que el radio");
        float alpha = 0.918, beta = 1.953;
        float gaussianKernel = alpha * (1 - ((1 - 1/exp(beta*dist.modulo()*dist.modulo()/(2 * radius* radius)))/(1-1/exp(beta))));
        float k = 2;
        float wr = 1 - dist.modulo() / (radius * k);
       // contribucion = contribucion + contribucionMaterial * photon->getFlux() / (M_PI * radius * radius);
        // contribucion = contribucion + contribucionMaterial * photon->getFlux() * wr / ((1 - 2 / (3*k)) * M_PI * radius * radius);
        contribucion = contribucion + contribucionMaterial * photon->getFlux() * gaussianKernel;
    }
    return contribucion;
}

void PhotonMapping::work(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays, int x, nn::KDTree<Photon,3,PhotonAxisPosition>& fotonmap){
    pair<int, int> n;
    n = jobs.pop();
    int acum = x;
    while (n.first >= 0 && n.second >= 0) //A value less than 0 marks the end of the list
    {
        RGB suma;
        for(int i = 0; i < nRays; i++){
           //Se crea un rayo aleatorio por pixel de la imagen
            float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_cam.getAnchura()));
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_cam.getAltura()));
            Punto centro(_cam.getReferencia().getX()+r1+_cam.getAnchura()*n.second,_cam.getReferencia().getY()-r2/2-_cam.getAltura()*n.first,_cam.getReferencia().getZ());
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
                            suma = suma + aL->getPower();
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
                        mtx.lock();
                        auto v = fotonmap.nearest_neighbors(cercano._punto,INFINITY,radius);
                        mtx.unlock();
                        //  contribucion = contribucion + photonDensityStim(cercano,rayo, v);
                        suma = suma +  photonDensityStim(cercano,rayo, v);
                        breakW = true;
                        
                    } else if(type == SPECULAR || type == REFRACTION){
                        rayo = Ray(dirRay,cercano._punto);
                    } else {
                        breakW = true;
                    }
                }  else {
                    breakW = true;
                }
            }
        }
        
                //cout << "El r1 es " << r1 << " y el r2 " << r2 << endl;
        Pixel calculated = {n.first,n.second,suma/nRays*(1-0.1*0.1)+(0.1*0.1*0.1)};
        result.push(calculated);
        if(n.first*_cam.getNPixelsW() + n.second == acum - 1){ cout << "="; cout.flush(); }
        else if(n.first*_cam.getNPixelsW() + n.second > acum - 1) acum = acum + x;
        n = jobs.pop();
    }
    return;
}