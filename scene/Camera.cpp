#include "Camera.h"

Camera::Camera(Direccion l, Direccion u, Direccion f, Punto o){
    _L = l;
    _U = u;
    _F = f;
    _O = o;
    _altura = 2*_U.modulo()/nPixels;
    _anchura = 2* _L.modulo() / nPixels;
    _referenciaPixel = _O + _F + _L + _U;
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
    for(int i = 0; i < nPixels; i ++){
        for(int j = 0; j < nPixels; j ++){
            Punto centro(_referenciaPixel.getX()+_anchura/2+_anchura*j,_referenciaPixel.getY()-_altura/2-_altura*i,_referenciaPixel.getZ());
            cout << centro << endl;
            Ray rayo(centro-_O,_O);
            //cout << rayo.getDireccion() << endl;
        
            float t = INFINITY;
            Intersect intersect;
            Punto inter;
            RGB emision;
            bool corta = false;
            for(auto p : _primitives){
                cout << p->getEmision();
                intersect = p->intersect(rayo);
                cout << " " << intersect._intersect << " " << intersect._t << endl; 
                if(intersect._intersect && intersect._t < t && intersect._t > 0){
                    corta = true;
                    t = intersect._t;
                    inter = intersect._punto;
                    emision = p->getEmision();
                }
                
            }
            cout << endl;
            if(corta){
                cuadricula[i][j] = emision; 
            } else {
                cuadricula[i][j] = RGB(1,1,1);
            }
            
        }
    }
}

void Camera::save() const{
    Imagen img("P3","#MAX=1","#prueba.ppm",to_string(nPixels) + " " + to_string(nPixels),"255",255,255);
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

