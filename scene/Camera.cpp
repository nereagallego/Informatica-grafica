#include "Camera.h"

Camera::Camera(Direccion l, Direccion u, Direccion f, Punto o){
    _L = l;
    _U = u;
    _F = f;
    _O = o;
    _altura = 2*_U.modulo()/nPixels;
    _anchura = 2* _L.modulo() / nPixels;
    _referenciaPixel = _O + _F + _L + _U;
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
    Matrix4 cambioBase1(_L,_U,_F,_O);
    Matrix4 cambioBase = cambioBase1.inversa();
    for(int i = 0; i < nPixels; i ++){
        for(int j = 0; j < nPixels; j ++){
            Punto centro(_referenciaPixel.getX()+_anchura/2*i,_referenciaPixel.getY()+_altura/2*j,_referenciaPixel.getZ());
            Ray rayo(centro-_O,_O);
            
            CoordenadasHomogeneas dir(rayo.getDireccion());
            CoordenadasHomogeneas punto(rayo.getPunto());
            rayo.setDireccion(dir.cambioBase(cambioBase).direccion());
            rayo.setPunto(punto.cambioBase(cambioBase).punto());
            float t = 0.0;
            Intersect intersect;
            Punto inter;
            RGB emision;
            bool corta = false;
            for(auto p : _primitives){
                intersect = p->intersect(rayo);
                if(intersect._intersect && intersect._t < t){
                    corta = true;
                    cout << "corta" << endl;
                    t = intersect._t;
                    inter = intersect._punto;
                    emision = p->getEmision();
                    cout << emision << endl;
                }
            }
            if(corta){
                cuadricula[i][j] = emision;
                cout << "guardo la emisión" << endl; 
            } else {
                cuadricula[i][j] = RGB(1,1,1);
            }
            
        }
    }
}

void Camera::save() const{
    Imagen img("P3","255","",to_string(nPixels) + " " + to_string(nPixels),"255",255,255);
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

