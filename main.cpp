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
#include "image/CImg.h"
#include "material/Texturas.h"
//#include <jpeglib.h>
#include "material/SimpleBSDF.h"
#include "geometry/Obj.h"

using namespace std;


int main(int argc, char *argv[]){
    if(argc < 2) cout << "uso: ./main <nombre_fichero>" << endl;
    else{
      
      //Esta escena genera la Cornel Box con 2 esferas.

      cout << "Empezando render..." << endl;
      string filename = argv[1];
      Camera cam(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 259, 518, 128);
      

      auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 2);
      leftPlane->setEmision(make_shared<SimpleBSDF>(RGB(0.72549,0.3098,0.74117647), RGB(0.2,0.2,0.2), RGB()));
      auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 2);
      rightPlane->setEmision(make_shared<SimpleBSDF>(RGB(0.37647, 0.25098, 0.74117647), RGB(), RGB()));
      auto floorPlane = make_shared<Plano>(Direccion(0,1,0), 1);
      floorPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));
      auto ceilingPlane = make_shared<Plano>(Direccion(0,-1,0),1);
      ceilingPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));
      auto backPlane = make_shared<Plano>(Direccion(0,0,-1),1);
      backPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));

      auto leftSphere = make_shared<Esfera>(Punto(-0.5,-0.7,0.25),0.3);
      leftSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.1,0.1,0.1), RGB(0.7,0.7,0.7), RGB()));

      auto rightSphere = make_shared<Esfera>(Punto(0.5,-0.7,-0.25),0.3);
      rightSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.5,0.5,0.5), RGB(), RGB(0.5,0.5,0.5), 1.5));
     auto lightPoint = make_shared<Light>(Punto(0,0,0.8),RGB(0.3,0.3,0.3));
      auto areaLight = make_shared<SquareLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(0.5,0.5,0.5),Punto(-0.5,1,-0.5),Punto(-0.5,1,0.5),Punto(0.5,1,0.5),Punto(0.5,1,-0.5));
       auto cicleLight = make_shared<CircleLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(0.5,0.5,0.5),0.3);

      cam.addLight(cicleLight);

       cam.addPrimitive(leftPlane);
       cam.addPrimitive(rightPlane);
       cam.addPrimitive(floorPlane);
       cam.addPrimitive(ceilingPlane);
       cam.addPrimitive(backPlane);
       cam.addPrimitive(leftSphere);
       cam.addPrimitive(rightSphere);


      Imagen gen = cam.dibujar();
     
      Imagen res = ToneMapping::gammaCurve(gen,4.4);
      res.exportFile(filename);

    
      return 0;
    }
    
}