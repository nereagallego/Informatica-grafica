
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
#include "photonmapping/photonmapping.h"
#include "scene/AreaLight.h"



using namespace std;

int main(int argc, char *argv[]){
  if(argc < 2) cout << "uso: ./main <nombre_fichero>" << endl;
  else{
    string filename = argv[1];

  cout << "Empezando render..." << endl;
  /*-------------------------------------PRUEBA PHOTON MAPPING---------------------------------*/
  
  //Esta escena es una Cornel Box con 2 esferas

    Camera cam(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 259, 518);
    
    auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 2);
    leftPlane->setEmision(BSDF(RGB(0.8,0,0), RGB(), RGB()));
    auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 2);
    rightPlane->setEmision(BSDF(RGB(0, 0.8, 0), RGB(), RGB()));
    auto floorPlane = make_shared<Plano>(Direccion(0,1,0), 1);
    floorPlane->setEmision(BSDF(RGB(0.8,0.8,0.8), RGB(), RGB()));
    auto ceilingPlane = make_shared<Plano>(Direccion(0,-1,0),1);
    ceilingPlane->setEmision(BSDF(RGB(0.8,0.8,0.8), RGB(), RGB()));
    auto backPlane = make_shared<Plano>(Direccion(0,0,-1),1);
    backPlane->setEmision(BSDF(RGB(0.8,0.8,0.8), RGB(), RGB()));

    auto leftSphere = make_shared<Esfera>(Punto(-0.8,-0.7,0.25),0.3);
    leftSphere->setEmision(BSDF(RGB(), RGB(1,1,1), RGB()));

    auto rightSphere = make_shared<Esfera>(Punto(0.8,-0.7,-0.25),0.3);
    rightSphere->setEmision(BSDF(RGB(), RGB(), RGB(1,1,1),1.5));
    
    auto areaLight = make_shared<SquareLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(1,1,1),Punto(-0.5,1,-0.5),Punto(-0.5,1,0.5),Punto(0.5,1,0.5),Punto(0.5,1,-0.5));

    cam.addLight(areaLight);

    cam.addPrimitive(leftPlane);
    cam.addPrimitive(rightPlane);
    cam.addPrimitive(floorPlane);
    cam.addPrimitive(ceilingPlane);
    cam.addPrimitive(backPlane);
    cam.addPrimitive(leftSphere);
    cam.addPrimitive(rightSphere);

    PhotonMapping photonMap(cam,50000);
    Imagen gen = photonMap.photonMapping();

    Imagen res = ToneMapping::gammaCurve(gen,8.8);

    res.exportFile(filename);

  }
    return 0;
  
}