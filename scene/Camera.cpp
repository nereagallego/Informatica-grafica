#include "Camera.h"

Camera::Camera(Direccion l, Direccion u, Direccion f, Punto o, int nPixelsh, int nPixelsw){
    _L = l;
    cout << "L: " << _L << " mod: " << _L.modulo() << endl;
    _U = u;
    cout << "U: " << _U << " mod: " << _U.modulo() << endl;
    _F = f;
    _O = o;
    _altura = _U.modulo() * 2/nPixelsh;
    _anchura = _L.modulo() * 2 / nPixelsw;
    cout << _altura << " "  << _anchura << endl;
    _referenciaPixel = _O + _F + _L + _U;
    cout << _referenciaPixel << endl;
    _nPixelsh = nPixelsh;
    _nPixelsw = nPixelsw;
}

Camera::Camera(Direccion l, Direccion u, Direccion f, Punto o, int nPixelsh, int nPixelsw, double numberPhotons){
    _L = l;
    cout << "L: " << _L << " mod: " << _L.modulo() << endl;
    _U = u;
    cout << "U: " << _U << " mod: " << _U.modulo() << endl;
    _F = f;
    _O = o;
    _altura = _U.modulo() * 2/nPixelsh;
    _anchura = _L.modulo() * 2 / nPixelsw;
    cout << _altura << " "  << _anchura << endl;
    _referenciaPixel = _O + _F + _L + _U;
    cout << _referenciaPixel << endl;
    _nPixelsh = nPixelsh;
    _nPixelsw = nPixelsw;
    _numberPhotons = numberPhotons;
}

Punto Camera::getO(){
    return _O;
}

Direccion Camera::getL(){
    return _L;
}

Direccion Camera::getU(){
    return _U;
}

Direccion Camera::getF(){
    return _F;
}

Imagen Camera::dibujar(){
    Imagen img(_nPixelsh, _nPixelsw,255,255);
    cout << _nPixelsw << " "  << _nPixelsh << endl;
    srand (time(NULL));
    ConcurrentQueue<pair<int,int>> jobs;
    ConcurrentQueue<Pixel> result;

    for(int i = 0; i < _nPixelsh; i ++){
        for(int j = 0; j < _nPixelsw; j ++){
            jobs.push(make_pair(i, j));
        }
    }

    for(int i = 0; i<NTHREADS; i++) {
        jobs.push(make_pair(-1,-1));
    }
    
    vector<thread> threads;  
    for (int i = 0; i<NTHREADS; i++) {
        // threads.push_back(std::thread(&Camera::worker,std::ref(jobs),std::ref(result),std::ref(scene),nRays));
        threads.push_back(std::thread([&](ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays){ work(jobs,result,numRays); }, std::ref(jobs),std::ref(result),numRays));
    }
    //Wait for end
    for (auto &th : threads) {
        th.join();
    }

    queue<Pixel> qresult = result.getQueue();
    while (!qresult.empty())
    {
        Pixel a = qresult.front();

        img._imagenHDR[a.x][a.y] = a.contribution;
        qresult.pop();

    }
    return img;
}

void Camera::work(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays)
{
    pair<int, int> n;
    n = jobs.pop();
    while (n.first >= 0 && n.second >= 0) //A value less than 0 marks the end of the list
    {
        RGB suma;
        for(int i = 0; i < nRays; i++){
            float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_anchura));
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_altura));
            Punto centro(_referenciaPixel.getX()+r1+_anchura*n.second,_referenciaPixel.getY()-r2/2-_altura*n.first,_referenciaPixel.getZ());
            Ray rayo(centro-_O,_O);
            suma = suma + pathTracing(rayo,0,15);
        }
        
                //cout << "El r1 es " << r1 << " y el r2 " << r2 << endl;
        Pixel calculated = {n.first,n.second,suma/nRays};
        result.push(calculated);
        n = jobs.pop();
    }
    return;
}



void Camera::addPrimitive(shared_ptr<Primitive> p){
    _primitives.push_back(p);
}


float Camera::max(const float a, const float b, const float c, const float d) const{
    if(a >= b && a >= c && a >= d){
        return a;
    } else if(b >= a && b >= c && b >= d){
        return b;
    } else if(c >= a && c >= b && c >= d){
        return c;
    } else {
        return d;
    }
}

void Camera::addLight(Light l){
    _lights.push_back(l);
    cout << "cantidad de luces " << _lights.size() << endl;
}

RGB Camera::nextEventEstimation(Direccion direccionRayo, Intersect intersection){
    RGB contribucion;
    for(auto l : _lights){
        //cout << "calculo la contribucion de luz" << endl;
        Direccion dir = l.getCenter() - intersection._punto;
        Direccion rayoLuzDirection = dir.normalizar();
        Ray rayoLuz(rayoLuzDirection, intersection._punto);

        Intersect cercano;
        cercano._intersect = false;
        cercano._t = rayoLuzDirection.modulo();

        for (auto p : _primitives)
        {

            Intersect inter = p->intersect(rayoLuz);
            if (inter._intersect && inter._t < cercano._t && inter._t > 0)
            {
                //cout << "intersecta" << endl;
                cercano = inter;
            }
        }
        
        double contribucionGeometrica = abs(intersection._normal* rayoLuzDirection.normalizar());

        RGB contribucionMaterial = intersection._emision.eval(intersection._punto,direccionRayo,rayoLuzDirection,intersection._normal);

        RGB first = l.getPower() / (rayoLuz.getDireccion() * rayoLuz.getDireccion());

        RGB contribucionLuz = first * contribucionMaterial * contribucionGeometrica;

        if (!cercano._intersect)
        {
            contribucion = contribucion + contribucionLuz;
        } 
    }
    return contribucion;
}



RGB Camera::pathTracing(Ray r, int n,const int i){
    if(n > i) return RGB();
    RGB contribucion;
    Intersect cercano;
    cercano._intersect = false;
    cercano._t = INFINITY;

    for(auto p : _primitives){
        Intersect intersect = p->intersect(r); 
        if(intersect._intersect && intersect._t < cercano._t && intersect._t > 0){
            cercano = intersect;

        }
        
    }

    if( cercano._intersect ) {
        //Se traza la luz directa y se obtiene su contribucion
        contribucion = contribucion + nextEventEstimation(r.getDireccion(), cercano);
    } else return RGB();

    tuple<Direccion,RGB> tupla = cercano._emision.sample(r.getDireccion(), cercano._punto,cercano._normal);
    Direccion dirRay = get<0>(tupla);
    RGB color_BSDF = get<1>(tupla); 
    if(color_BSDF.getRed() == 0 && color_BSDF.getGreen() == 0 && color_BSDF.getBlue() == 0) return RGB();
    
  //  contribucion = contribucion + color_BSDF * pathTracing(Ray(dirRay,cercano._punto),n++,i);
    contribucion = contribucion + color_BSDF *pathTracing(Ray(dirRay,cercano._punto),n++,i);
    return contribucion;
}

RGB Camera::photonMapping(){
    //Recorrer las fuentes de luz y asignarles la cantidad de fotones
    RGB total_lights(0,0,0);
    for(Light l: _lights){
        total_lights = total_lights + l.getPower();
    }

    double modulo_total = (total_lights.getRed()+total_lights.getGreen()+total_lights.getBlue());

    // N*(p1/(p1+p2))
    for(Light l: _lights){
        double modulo_aux =(l.getPower().getRed()+l.getPower().getGreen()+l.getPower().getBlue());
     //   l.setPhotons((modulo_aux/modulo_total)*_numberPhotons);
        int numberPhotons = (modulo_aux/modulo_total)*_numberPhotons;
        //Empezar el recorrido aleatorio de cada foton. Se lanza una rayo aleatorio en la esfera

        // ESTO SERIA PARA UN SOLO FOTON, QUEDARIAN N-1
        for(int i = 0; i < numberPhotons; i ++){
            double theta = Rand::fRand(0.0,1.0);
            double phi = Rand::fRand(0.0,1.0);
            double thethaInverse = acos(sqrt(2*theta-1));
            double phiInverse = 2 * M_PI * phi;
            Direccion omegai = Direccion(sin(thethaInverse)*cos(phiInverse),sin(thethaInverse)*sin(phiInverse),cos(thethaInverse)).normalizar();
            
            Ray rayo(omegai,l.getCenter());
        }
        
    }


}