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

      cimg_library::CImg<unsigned char> src("resources/rock_wall.jpg");
      int width = src.width();
      int height = src.height();

      cout << "La altura es " << height << " y la anchura " << width << endl;
      cout << "y el tamaño es " << src.size() << endl;

      cimg_library::CImg<unsigned char> wood("resources/wood_planks.jpg");

      cout << "Empezando render..." << endl;
      string filename = argv[1];
      Camera cam(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 518, 1036, 512);
      

      auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 2);
      leftPlane->setEmision(make_shared<Textura>(RGB(0.72549,0.3098,0.74117647), RGB(0.2,0.2,0.2), RGB(),src));
      auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 2);
      rightPlane->setEmision(make_shared<Textura>(RGB(0.37647, 0.25098, 0.74117647), RGB(), RGB(),src));
      auto floorPlane = make_shared<Plano>(Direccion(0,1,0), 1);
      floorPlane->setEmision(make_shared<Textura>(RGB(1,1,1), RGB(), RGB(),wood));
      auto ceilingPlane = make_shared<Plano>(Direccion(0,-1,0),1);
      ceilingPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));
      auto backPlane = make_shared<Plano>(Direccion(0,0,-1),1);
      backPlane->setEmision(make_shared<Textura>(RGB(1,1,1), RGB(), RGB(),src));

      auto leftSphere = make_shared<Esfera>(Punto(-0.8,-0.7,0.25),0.4);
      leftSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.1,0.1,0.1), RGB(0.7,0.7,0.7), RGB()));

      auto rightSphere = make_shared<Esfera>(Punto(0.8,-0.7,-0.25),0.4);
      rightSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.1,0.1,0.1), RGB(), RGB(0.9,0.9,0.9), 1.5));

      auto sphere1 = make_shared<Esfera>(Punto(0,-0.95,-0.25),0.05);
      sphere1->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere2 = make_shared<Esfera>(Punto(-0.2,-0.95,-0.3),0.05);
      sphere2->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere3 = make_shared<Esfera>(Punto(-0.05,-0.95,0.4),0.05);
      sphere3->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere4 = make_shared<Esfera>(Punto(-0.2,-0.95,0.2),0.05);
      sphere4->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));
      

      auto sphere5 = make_shared<Esfera>(Punto(0.1,-0.95,0.4),0.05);
      sphere5->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere6 = make_shared<Esfera>(Punto(-0.4,-0.95,-0.3),0.05);
      sphere6->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere7 = make_shared<Esfera>(Punto(-0.7,-0.95,-0.3),0.05);
      sphere7->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere8 = make_shared<Esfera>(Punto(-0.9,-0.95,-0.3),0.05);
      sphere8->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere9 = make_shared<Esfera>(Punto(-1.2,-0.95,-0.3),0.05);
      sphere9->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere10 = make_shared<Esfera>(Punto(-1.4,-0.95,-0.3),0.05);
      sphere10->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere11 = make_shared<Esfera>(Punto(-1.6,-0.95,0.2),0.05);
      sphere11->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere12 = make_shared<Esfera>(Punto(-1.8,-0.95,-0.4),0.05);
      sphere12->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere13 = make_shared<Esfera>(Punto(0.3,-0.95,0.4),0.05);
      sphere13->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere14 = make_shared<Esfera>(Punto(1.5,-0.95,0.1),0.05);
      sphere14->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

      auto sphere15 = make_shared<Esfera>(Punto(1.7,-0.95,-0.2),0.05);
      sphere15->setEmision(make_shared<SimpleBSDF>(RGB(0.3137,0.7686,0.1647), RGB(), RGB()));

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

       cam.addPrimitive(sphere1);
       cam.addPrimitive(sphere2);
       cam.addPrimitive(sphere3);
       cam.addPrimitive(sphere4);
       cam.addPrimitive(sphere5);
       cam.addPrimitive(sphere6);
        cam.addPrimitive(sphere7);
       cam.addPrimitive(sphere8);
       cam.addPrimitive(sphere9);
        cam.addPrimitive(sphere10);
       cam.addPrimitive(sphere11);
       cam.addPrimitive(sphere12);
         cam.addPrimitive(sphere13);
       cam.addPrimitive(sphere14);
       cam.addPrimitive(sphere15);


      Imagen gen = cam.dibujar();
     
      Imagen res = ToneMapping::gammaCurve(gen,4.4);
      res.exportFile(filename);

    
      return 0;
    }
    
}