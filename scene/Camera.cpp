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
    for(int i = 0; i < _nPixelsh; i ++){
        for(int j = 0; j < _nPixelsw; j ++){
            float r1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_anchura));
            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/_altura));
            //Punto centro(_referenciaPixel.getX()+r1+_anchura*j,_referenciaPixel.getY()-r2/2-_altura*i,_referenciaPixel.getZ());
            Punto centro(_referenciaPixel.getX()+_anchura/2+_anchura*j,_referenciaPixel.getY()-_altura/2-_altura*i,_referenciaPixel.getZ());
            //cout << centro << endl;
            Ray rayo(centro-_O,_O);
        
            Intersect cercano;
            cercano._intersect = false;
            cercano._emision = RGB(1,1,1);
            cercano._t = INFINITY;
            for(auto p : _primitives){
                Intersect intersect = p->intersect(rayo); 
                if(intersect._intersect && intersect._t < cercano._t && intersect._t > 0){
                    cercano = intersect;

                }
                
            }
            if(cercano._intersect){
                img._imagenHDR[i][j] = nextEventEstimation(rayo.getDireccion(),cercano); 
            } else {
                img._imagenHDR[i][j] = RGB(1,1,1);
            }
            
        }
    }
    return img;
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
        //Direccion normal = crossProduct(rayoLuzDirection,direccionRayo);
        double contribucionGeometrica = abs(intersection._normal* rayoLuzDirection.normalizar());
    //    cout << contribucionGeometrica << endl;
        BSDF bsdf(intersection._emision);
        RGB contribucionMaterial = bsdf.eval();
    //    cout << contribucionMaterial << endl;
        RGB first = l.getPower() / (rayoLuz.getDireccion() * rayoLuz.getDireccion());
    //    cout << first << endl;

        RGB contribucionLuz = first * contribucionMaterial * contribucionGeometrica;
//        cout << contribucionLuz << endl;
        if (!cercano._intersect)
        {
            contribucion = contribucion + contribucionLuz;
        } 
    }
    return contribucion;
}