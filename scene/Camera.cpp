#include "Camera.h"

Camera::Camera(Direccion l, Direccion u, Direccion f, Punto o){
    cout << "1" << endl;
    _L = l;
    cout << "2" << endl;
    _U = u;
    cout << "3" << endl;
    _F = f;
    cout << "4" << endl;
    _O = o;
    cout << "5" << endl;
    _altura = 2*_U.modulo()/nPixels;
    cout << "6" << endl;
    _anchura = 2* _L.modulo() / nPixels;
    cout << "7" << endl;
    _referenciaPixel = _O + _F + _L + _U;
    cout << "8" << endl;
    cout << _referenciaPixel << endl;
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

void Camera::getCuadricula(RGB vector[nPixels][nPixels]){
    vector = cuadricula;
}


void Camera::dibujar(){
    // Matrix4 cambioBase1(_L,_U,_F,_O);
    // Matrix4 cambioBase = cambioBase1.inversa();
    srand (time(NULL));
    for(int i = 0; i < nPixels; i ++){
        for(int j = 0; j < nPixels; j ++){
            float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_anchura));
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_altura));
            Punto centro(_referenciaPixel.getX()+r1+_anchura*j,_referenciaPixel.getY()-r2/2-_altura*i,_referenciaPixel.getZ());
        //    cout << centro << endl;
            Ray rayo(centro-_O,_O);
            //cout << rayo.getDireccion() << endl;
        
            float t = INFINITY;
            Intersect intersect;
            Punto inter;
            RGB emision;
            bool corta = false;
            for(auto p : _primitives){
        //        cout << p->getEmision();
                intersect = p->intersect(rayo);
        //        cout << " " << intersect._intersect << " " << intersect._t << endl; 
                if(intersect._intersect && intersect._t < t && intersect._t > 0){
                    corta = true;
                    t = intersect._t;
                    inter = intersect._punto;
                    emision = p->getEmision();
                }
                
            }
        //    cout << endl;
            if(corta){
                cuadricula[i][j] = emision; 
            } else {
                cuadricula[i][j] = RGB(1,1,1);
            }
            
        }
    }
}

void Camera::save() const{
    Imagen img("P3","#MAX=1","#prueba.ppm",to_string(nPixels) + " " + to_string(nPixels),"255",255,1);
    vector<RGB> vect;
   
    for(int i = 0; i < nPixels; i++){
        for(int j = 0; j < nPixels; j++){
           
            vect.push_back(cuadricula[i][j]);
        }
    }
    img.setImagen(vect);
    img.exportFile("prueba.ppm");
   
}

void Camera::addPrimitive(shared_ptr<Primitive> p){
    _primitives.push_back(p);
}

