
#include "p1/Direccion.h"
#include "p1/Punto.h"
#include "p3/Plano.h"
#include "p3/Ray.h"


using namespace std;

int main(){
    
    Direccion d(-1,0,0);
    Plano plane(d,3);
    Ray r(Direccion(1,0,0),Punto(0,0,0));
    
    float t = r.intersect(plane);
    if (t != -1){
        Punto p = r.getPunto() + r.getDireccion() * t;
        cout << p << endl;
    }

    Esfera e(Direccion(0,2,0),Punto(3,0,0), Punto(3,1,0));
    t = r.intersect(e);
    if (t != -1){
        Punto p = r.getPunto() + r.getDireccion() * t;
        cout << p << endl;
    } else cout << "No corta" << endl;
     
    
}