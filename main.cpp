
#include "math/Direccion.h"
#include "math/Punto.h"
#include "geometry/Plano.h"
#include "geometry/Ray.h"
#include "geometry/Triangulo.h"
#include "scene/Camera.h"
#include "geometry/Esfera.h"
#include "math/Punto.h"
#include "image/ToneMapping.h"
#include "scene/Light.h"


using namespace std;

int main(){
    cout << "entro en main" << endl;
    Camera cam(Direccion(-1,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 256);
    cout << "creo la camara" << endl;
    auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 1);
    leftPlane->setEmision(RGB(255,0,0));
    auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 1);
    rightPlane->setEmision(RGB(0, 255, 0));
    auto floorPlane = make_shared<Plano>(Direccion(0,1,0), 1);
    floorPlane->setEmision(RGB(155,155,155));
    auto ceilingPlane = make_shared<Plano>(Direccion(0,-1,0),1);
    ceilingPlane->setEmision(RGB(155,155,155));
    auto backPlane = make_shared<Plano>(Direccion(0,0,-1),1);
    backPlane->setEmision(RGB(155,155,155));

    auto leftSphere = make_shared<Esfera>(Punto(-0.5,-0.7,0.25),0.3);
    leftSphere->setEmision(RGB(255,0,128));

    auto rightSphere = make_shared<Esfera>(Punto(0.5,-0.7,-0.25),0.3);
    rightSphere->setEmision(RGB(0,0,255));
    
    Light lightPoint(Punto(0,0.5,0),RGB(1,1,1));

    cam.addLight(lightPoint);

    cam.addPrimitive(leftPlane);
    cam.addPrimitive(rightPlane);
    cam.addPrimitive(floorPlane);
    cam.addPrimitive(ceilingPlane);
    cam.addPrimitive(backPlane);
    cam.addPrimitive(leftSphere);
    cam.addPrimitive(rightSphere);
    // cout << "añado primitivas" << endl;
    Imagen gen = cam.dibujar();
    // cout << "dibujo" << endl;
    cout << gen._imagenHDR.size() << " " << gen._imagenHDR[0].size() << endl;
    cout << gen.getWidth() << " " << gen.getHeight() << endl;
  //  gen.exportFile("prueba.ppm");
    Imagen res = ToneMapping::reinhard2(gen,0.2);
    res.exportFile("prueba.ppm");
  
    return 0;
}