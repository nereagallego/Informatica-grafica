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
#include "geometry/Stl.h"
#include "image/CImg.h"
#include "material/Texturas.h"
//#include <jpeglib.h>
#include "material/SimpleBSDF.h"
#include "geometry/Obj.h"

using namespace std;

int main(int argc, char *argv[]){

      
      cimg_library::CImg<unsigned char> src("resources/rock_wall.jpg");
      int width = src.width();
      int height = src.height();

      cout << "La altura es " << height << " y la anchura " << width << endl;
      cout << "y el tamaño es " << src.size() << endl;
      
      cimg_library::CImg<unsigned char> wood("resources/wood_planks.jpg");
      width = wood.width();
      height = wood.height();

      cout << "La altura es " << height << " y la anchura " << width << endl;
      cout << "y el tamaño es " << src.size() << endl;

      
      // //Cargamos obj
      // objl::Loader loader;
      // loader.LoadFile("resources/sofa.obj");
      

      // cout << "El tamaño de el obj es " << loader.LoadedMeshes.size() << endl;

      cout << "entro en main" << endl;
    //  string filename = "hard-soft-shadows.ppm";
      Camera cam(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 2);

      Camera cam1(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 8);

      Camera cam2(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 32);

      Camera cam3(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 128);

      Camera cam4(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 512);

      Camera cam5(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 2);

      Camera cam6(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 8);

      Camera cam7(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 32);

      Camera cam8(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 128);

      Camera cam9(Direccion(-2,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,-3.5), 256, 518, 512);
      
      cout << "creo la camara" << endl;


    //  auto sofa = make_shared<Obj>("resources/diamond5.obj", cam.getL(), cam.getU(), cam.getF(), Punto(0,0,1), 0.25);
    //  sofa->setEmision(make_shared<SimpleBSDF>(RGB(0.407,0.508,0.541176), RGB(), RGB(0.4,0.4,0.4)));
    //  auto sofa = make_shared<Obj>("resources/sofa.obj", cam.getL(), cam.getU(), cam.getF(), Punto(0,0,1));
    //  sofa->setEmision(make_shared<SimpleBSDF>(RGB(1,0,0), RGB(), RGB()));

      auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 2);
      leftPlane->setEmision(make_shared<SimpleBSDF>(RGB(0.72549,0.3098,0.74117647), RGB(), RGB()));
      auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 2);
      rightPlane->setEmision(make_shared<SimpleBSDF>(RGB(0.37647, 0.25098, 0.74117647), RGB(), RGB()));
      auto floorPlane = make_shared<Plano>(Direccion(0,1,0), 1);
      floorPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));
      auto ceilingPlane = make_shared<Plano>(Direccion(0,-1,0),1);
      ceilingPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));
      auto backPlane = make_shared<Plano>(Direccion(0,0,-1),1);
      backPlane->setEmision(make_shared<SimpleBSDF>(RGB(1,1,1), RGB(), RGB()));
      //backPlane->setTexture(src);

      auto leftSphere = make_shared<Esfera>(Punto(-1.2,-0.6,0.25),0.4);
      leftSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.1,0.1,0.1), RGB(0.7,0.7,0.7), RGB()));

      auto rightSphere = make_shared<Esfera>(Punto(1.2,-0.6,-0.25),0.4);
      //rightSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.1,0.1,0.1), RGB(), RGB(0.7, 0.7, 0.7),1.5));
      rightSphere->setEmision(make_shared<SimpleBSDF>(RGB(0.5,0.5,0.5), RGB(), RGB(0.5,0.5,0.5), 1.5));
      auto centerSphere = make_shared<Esfera>(Punto(0,-0.6,0),0.4);
      centerSphere->setEmision(make_shared<SimpleBSDF>(RGB(1,0,0), RGB(), RGB()));
     auto lightPoint = make_shared<Light>(Punto(0,1,0),RGB(1,1,1));
      auto areaLight = make_shared<SquareLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(0.5,0.5,0.5),Punto(-0.5,1,-0.5),Punto(-0.5,1,0.5),Punto(0.5,1,0.5),Punto(0.5,1,-0.5));
       auto cicleLight = make_shared<CircleLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(1,1,1),0.3);
    // auto lightPoint = make_shared<AreaLight>(Direccion(0,-1,0),0.5,Punto(0,0.5,0),RGB(0.3,0.5,0.3),Punto(-0.5,0.5,-0.5),Punto(-0.5,0.5,0.5),Punto(0.5,0.5,0.5),Punto(0.5,0.5,-0.5));

      cam5.addLight(lightPoint);

      //  cam.addPrimitive(sofa);

       cam5.addPrimitive(leftPlane);
       cam5.addPrimitive(rightPlane);
       cam5.addPrimitive(floorPlane);
       cam5.addPrimitive(ceilingPlane);
       cam5.addPrimitive(backPlane);
       cam5.addPrimitive(leftSphere);
       cam5.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen5 = cam5.dibujar();

      Imagen res5 = ToneMapping::gammaCurve(gen5,4.4);
      res5.exportFile("lightPoint-2p.ppm");

        cam6.addLight(lightPoint);

      //  cam.addPrimitive(sofa);

       cam6.addPrimitive(leftPlane);
       cam6.addPrimitive(rightPlane);
       cam6.addPrimitive(floorPlane);
       cam6.addPrimitive(ceilingPlane);
       cam6.addPrimitive(backPlane);
       cam6.addPrimitive(leftSphere);
       cam6.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen6 = cam6.dibujar();

      Imagen res6 = ToneMapping::gammaCurve(gen6,4.4);
      res6.exportFile("lightPoint-12p.ppm");

      cam7.addLight(lightPoint);

      //  cam.addPrimitive(sofa);

       cam7.addPrimitive(leftPlane);
       cam7.addPrimitive(rightPlane);
       cam7.addPrimitive(floorPlane);
       cam7.addPrimitive(ceilingPlane);
       cam7.addPrimitive(backPlane);
       cam7.addPrimitive(leftSphere);
       cam7.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen7 = cam7.dibujar();

      Imagen res7 = ToneMapping::gammaCurve(gen7,4.4);
      res7.exportFile("lightPoint-32p.ppm");

      cam8.addLight(lightPoint);

      //  cam.addPrimitive(sofa);

       cam8.addPrimitive(leftPlane);
       cam8.addPrimitive(rightPlane);
       cam8.addPrimitive(floorPlane);
       cam8.addPrimitive(ceilingPlane);
       cam8.addPrimitive(backPlane);
       cam8.addPrimitive(leftSphere);
       cam8.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen8 = cam8.dibujar();

      Imagen res8 = ToneMapping::gammaCurve(gen8,4.4);
      res8.exportFile("lightPoint-128p.ppm");

      cam9.addLight(lightPoint);

      //  cam.addPrimitive(sofa);

       cam9.addPrimitive(leftPlane);
       cam9.addPrimitive(rightPlane);
       cam9.addPrimitive(floorPlane);
       cam9.addPrimitive(ceilingPlane);
       cam9.addPrimitive(backPlane);
       cam9.addPrimitive(leftSphere);
       cam9.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen9 = cam9.dibujar();

      Imagen res9 = ToneMapping::gammaCurve(gen9,4.4);
      res9.exportFile("lightPoint-512p.ppm");
      
      return 0;
    
}