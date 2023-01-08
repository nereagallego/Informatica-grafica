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
     auto lightPoint = make_shared<Light>(Punto(0,0,0.8),RGB(1,1,1));
      auto areaLight = make_shared<SquareLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(0.5,0.5,0.5),Punto(-0.5,1,-0.5),Punto(-0.5,1,0.5),Punto(0.5,1,0.5),Punto(0.5,1,-0.5));
       auto cicleLight = make_shared<CircleLight>(Direccion(0,-1,0),1,Punto(0,1,0),RGB(1,1,1),0.3);
    // auto lightPoint = make_shared<AreaLight>(Direccion(0,-1,0),0.5,Punto(0,0.5,0),RGB(0.3,0.5,0.3),Punto(-0.5,0.5,-0.5),Punto(-0.5,0.5,0.5),Punto(0.5,0.5,0.5),Punto(0.5,0.5,-0.5));

    //  cam.addLight(lightPoint);
      cam.addLight(cicleLight);

      //  cam.addPrimitive(sofa);

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
      Imagen res = ToneMapping::gammaCurve(gen,4.4);
      res.exportFile("area-light-2p.ppm");

      cam1.addLight(cicleLight);

      //  cam.addPrimitive(sofa);

       cam1.addPrimitive(leftPlane);
       cam1.addPrimitive(rightPlane);
       cam1.addPrimitive(floorPlane);
       cam1.addPrimitive(ceilingPlane);
       cam1.addPrimitive(backPlane);
       cam1.addPrimitive(leftSphere);
       cam1.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen1 = cam1.dibujar();
      // cout << "dibujo" << endl;
    //  gen.exportFile("prueba2.ppm");
      Imagen res1 = ToneMapping::gammaCurve(gen1,4.4);
      res1.exportFile("area-light-12p.ppm");

      cam2.addLight(cicleLight);

      //  cam.addPrimitive(sofa);

       cam2.addPrimitive(leftPlane);
       cam2.addPrimitive(rightPlane);
       cam2.addPrimitive(floorPlane);
       cam2.addPrimitive(ceilingPlane);
       cam2.addPrimitive(backPlane);
       cam2.addPrimitive(leftSphere);
       cam2.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen2 = cam2.dibujar();
      Imagen res2 = ToneMapping::gammaCurve(gen2,4.4);
      res2.exportFile("area-light-32p.ppm");

        cam3.addLight(cicleLight);

      //  cam.addPrimitive(sofa);

       cam3.addPrimitive(leftPlane);
       cam3.addPrimitive(rightPlane);
       cam3.addPrimitive(floorPlane);
       cam3.addPrimitive(ceilingPlane);
       cam3.addPrimitive(backPlane);
       cam3.addPrimitive(leftSphere);
       cam3.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen3 = cam3.dibujar();

      Imagen res3 = ToneMapping::gammaCurve(gen3,4.4);
      res3.exportFile("area-light-128p.ppm");

      cam4.addLight(cicleLight);

      //  cam.addPrimitive(sofa);

       cam4.addPrimitive(leftPlane);
       cam4.addPrimitive(rightPlane);
       cam4.addPrimitive(floorPlane);
       cam4.addPrimitive(ceilingPlane);
       cam4.addPrimitive(backPlane);
       cam4.addPrimitive(leftSphere);
       cam4.addPrimitive(rightSphere);

      //cam.addPrimitive(rightTriangle);
      // cout << "añado primitivas" << endl;
      Imagen gen4 = cam4.dibujar();

      Imagen res4 = ToneMapping::gammaCurve(gen4,4.4);
      res4.exportFile("area-light-512p.ppm");

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