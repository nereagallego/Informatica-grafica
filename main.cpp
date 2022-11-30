
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
#include "scene/AreaLight.h"


using namespace std;

int main(int argc, char *argv[]){
    if(argc < 2) cout << "uso: ./main <nombre_fichero>" << endl;
    else{
      cout << "entro en main" << endl;
      string filename = argv[1];
      Camera cam(Direccion(-1,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 256);
      cout << "creo la camara" << endl;
      auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 1);
      leftPlane->setEmision(BSDF(RGB(0.7,0,0), RGB(), RGB()));
      auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 1);
      rightPlane->setEmision(BSDF(RGB(0, 0.7, 0), RGB(), RGB()));
      auto floorPlane = make_shared<Plano>(Direccion(0,1,0), 1);
      floorPlane->setEmision(BSDF(RGB(0.6,0.6,0.6), RGB(), RGB()));
      auto ceilingPlane = make_shared<Plano>(Direccion(0,-1,0),1);
      ceilingPlane->setEmision(BSDF(RGB(0.6,0.60,0.6), RGB(), RGB()));
      auto backPlane = make_shared<Plano>(Direccion(0,0,-1),1);
      backPlane->setEmision(BSDF(RGB(0.6,0.6,0.6), RGB(), RGB()));

      auto leftSphere = make_shared<Esfera>(Punto(-0.5,-0.7,0.25),0.3);
      leftSphere->setEmision(BSDF(RGB(0.25,0,0.15), RGB(0.5,0,0.3), RGB()));

      auto rightSphere = make_shared<Esfera>(Punto(0.5,-0.7,-0.25),0.3);
      rightSphere->setEmision(BSDF(RGB(0.1,0.1,0.1), RGB(), RGB(0, 0, 0.7),1.5));
      
     // Light lightPoint(Punto(0,0.5,0),RGB(0.3,0.3,0.3));
     auto lightPoint = make_shared<AreaLight>(Direccion(0,-1,0),0.5,Punto(0,0.5,0),RGB(0.3,0.3,0.3),Punto(-0.5,0.5,-0.5),Punto(-0.5,0.5,0.5),Punto(0.5,0.5,0.5),Punto(0.5,0.5,-0.5));

      cam.addLight(lightPoint);

      cam.addPrimitive(leftPlane);
      cam.addPrimitive(rightPlane);
      cam.addPrimitive(floorPlane);
      cam.addPrimitive(ceilingPlane);
      cam.addPrimitive(backPlane);
      cam.addPrimitive(leftSphere);
      cam.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen = cam.dibujar();
      // cout << "dibujo" << endl;
      cout << gen._imagenHDR.size() << " " << gen._imagenHDR[0].size() << endl;
      cout << gen.getWidth() << " " << gen.getHeight() << endl;
    //  gen.exportFile("prueba2.ppm");
      Imagen res = ToneMapping::gammaCurve(gen,2.2);
      res.exportFile(filename);

    
      return 0;
    }
    
}