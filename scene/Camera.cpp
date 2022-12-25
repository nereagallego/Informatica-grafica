#include "Camera.h"

Camera::Camera(Direccion l, Direccion u, Direccion f, Punto o, int nPixelsh, int nPixelsw){
    _L = l;
    _U = u;
    _F = f;
    _O = o;
    _altura = _U.modulo() * 2/nPixelsh;
    _anchura = _L.modulo() * 2 / nPixelsw;
    _referenciaPixel = _O + _F + _L + _U;
    _nPixelsh = nPixelsh;
    _nPixelsw = nPixelsw;
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
    srand (time(NULL));
    ConcurrentQueue<pair<int,int>> jobs;
    ConcurrentQueue<Pixel> result;
    int x = 10*_nPixelsh * _nPixelsw / 100;
    cout << "[" ;
    cout.flush();
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
        threads.push_back(std::thread([&](ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays, int x){ work(jobs,result,numRays, x); }, std::ref(jobs),std::ref(result),numRays,x));
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

void Camera::work(ConcurrentQueue<pair<int,int>> &jobs, ConcurrentQueue<Pixel> &result, unsigned int nRays, int x)
{
    pair<int, int> n;
    n = jobs.pop();
    int acum = x;
    while (n.first >= 0 && n.second >= 0) //A value less than 0 marks the end of the list
    {
        RGB suma;
        for(int i = 0; i < nRays; i++){
            float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_anchura));
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_altura));
            Punto centro(_referenciaPixel.getX()+r1+_anchura*n.second,_referenciaPixel.getY()-r2/2-_altura*n.first,_referenciaPixel.getZ());
            Ray rayo(centro-_O,_O);
            suma = suma + pathTracing(rayo);
        }
        
                //cout << "El r1 es " << r1 << " y el r2 " << r2 << endl;
        Pixel calculated = {n.first,n.second,suma/nRays};
        result.push(calculated);
        if(n.first*_nPixelsw + n.second == acum - 1){ cout << "="; cout.flush(); }
        else if(n.first*_nPixelsw + n.second > acum - 1) acum = acum + x;
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

void Camera::addLight(shared_ptr<Light> l){
    _lights.push_back(l);
    cout << "cantidad de luces " << _lights.size() << endl;
}

RGB Camera::nextEventEstimation(Direccion direccionRayo, Intersect intersection){
    RGB contribucion;
    for(shared_ptr<Light> l : _lights){
        shared_ptr<AreaLight> aL = dynamic_pointer_cast<AreaLight>(l);
        
       // if(aL != nullptr) cout << "Es un area Light" << endl;
        //else cout << "No es un area light" << endl;
        //cout << "calculo la contribucion de luz" << endl;
        Direccion dir = l->getCenter() - intersection._punto;
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
                cercano = inter;
            }
        }
        RGB contribucionLuz;
        
        

        if (!cercano._intersect)
        {
            if(aL != nullptr){
            //    Direccion f = aL->getCenter() - intersection._punto;
                RGB first = l->getPower() / (rayoLuz.getDireccion() * rayoLuz.getDireccion());;
                RGB contribucionMaterial = intersection._emision.eval(intersection._punto,direccionRayo,rayoLuzDirection,intersection._normal);

            //    double contribucionGeometrica1 = abs(intersection._normal* f.normalizar());
            //    Direccion d = intersection._punto - aL->getCenter();
                double contribucionGeometrica = abs(intersection._normal* rayoLuzDirection.normalizar()) * abs(aL->getNormal() * rayoLuzDirection.normalizar()*-1);
                contribucionLuz = first * contribucionMaterial * contribucionGeometrica;

           } else {
                double contribucionGeometrica = abs(intersection._normal* rayoLuzDirection.normalizar());

                RGB contribucionMaterial = intersection._emision.eval(intersection._punto,direccionRayo,rayoLuzDirection,intersection._normal);

                RGB first = l->getPower() / (rayoLuz.getDireccion() * rayoLuz.getDireccion());

                contribucionLuz = first * contribucionMaterial * contribucionGeometrica;
            }
            contribucion = contribucion + contribucionLuz;
        } 
    }
    return contribucion;
}


RGB Camera::pathTracing(Ray r){
  //  if(n > i) return RGB();
    RGB contribucion;
    Intersect cercano;
    cercano._intersect = false;
    cercano._t = INFINITY;
    for(shared_ptr<Light> l : _lights){
        shared_ptr<AreaLight> aL = dynamic_pointer_cast<AreaLight>(l);
        if(aL != nullptr){
            Intersect inter  = aL->intersect(r);
            if(inter._intersect){
               // cout << "Intersecta con el area Light" << endl;
                return aL->getPower();
            }
            
            
        }
    }
    
    
    for(auto p : _primitives){
        Intersect intersect = p->intersect(r);
        if(intersect._intersect && intersect._t < cercano._t && intersect._t > 0){
            cercano = intersect;
        }
        
    }

    if( cercano._intersect ) {
        //Mirar si hay que cargar la textura
        /*if(cercano._texture() != nullptr){
            
        }*/

        //Se traza la luz directa y se obtiene su contribucion
        contribucion = contribucion + nextEventEstimation(r.getDireccion(), cercano);
    } else return RGB();

    tuple<Direccion,RGB> tupla = cercano._emision.sample(r.getDireccion(), cercano._punto,cercano._normal);
    Direccion dirRay = get<0>(tupla);
    RGB color_BSDF = get<1>(tupla); 
    if(color_BSDF.getRed() == 0 && color_BSDF.getGreen() == 0 && color_BSDF.getBlue() == 0) return RGB();
    
    contribucion = contribucion + color_BSDF *pathTracing(Ray(dirRay,cercano._punto));
    return contribucion;
}