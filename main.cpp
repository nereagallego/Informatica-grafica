
#include "math/Direccion.h"
#include "math/Punto.h"
#include "geometry/Plano.h"
#include "geometry/Ray.h"
#include "geometry/Triangulo.h"
#include "scene/Camera.h"
#include "geometry/Esfera.h"


using namespace std;

int main(){
    
    // Direccion d(-1,0,0);
    // Plano plane(d,3);
    // Ray r(Direccion(1,0,0),Punto(0,0,0));
    
    // float t = plane.intersect(r);
    // if (t != -1){
    //     Punto p = r.getPunto() + r.getDireccion() * t;
    //     cout << p << endl;
    // }

    // Esfera e(Direccion(0,2,0),Punto(3,0,0), Punto(3,1,0));
    // t = e.intersect(r);
    // if (t != -1){
    //     Punto p = r.getPunto() + r.getDireccion() * t;
    //     cout << p << endl;
    // } else cout << "No corta" << endl;
    
    // Triangulo tri(Punto(3,-2,-2), Punto(3,-2,2), Punto(3,1,1));
    // t = tri.intersect(r);
    // if (t != -1){
    //     Punto p = r.getPunto() + r.getDireccion() * t;
    //     cout << p << endl;
    // } else cout << "No corta" << endl;

    // Primitive p = plane;
    // t = p.intersect(r);
    // if (t != -1){
    //     Punto p = r.getPunto() + r.getDireccion() * t;
    //     cout << p << endl;
    // } else cout << "No corta" << endl;

    // p = e;
    // t = e.intersect(r);
    // if (t != -1){
    //     Punto p = r.getPunto() + r.getDireccion() * t;
    //     cout << p << endl;
    // } else cout << "No corta" << endl;

   // vector<shared_ptr<Primitive>> primitives;
    Camera cam(Direccion(-1,0,0),Direccion(0,1,0), Direccion(0,0,3), Punto(0,0,3));
    auto leftPlane = make_shared<Plano>(Direccion(1,0,0), 1);
    leftPlane->setEmision(RGB(1,0,0));
    auto rightPlane = make_shared<Plano> (Direccion(-1, 0, 0), 1);
    rightPlane->setEmision(RGB(0, 1, 0));
    
    cam.addPrimitive(leftPlane);
    cam.addPrimitive(rightPlane);
    

    cam.dibujar();

    cout << "No revienta" << endl;
    cam.save();
    
}