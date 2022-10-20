
#include "p1/Direccion.h"
#include "p1/Punto.h"
#include "p3/Plano.h"
#include "p3/Ray.h"


using namespace std;

int main(){
    
    Direccion d(-1,0,0);
    Plano plane(d,3);
    Ray r(Direccion(1,0,0),Punto(0,0,0));
    
    Punto p = r.intersect(plane);
    cout << p << endl; 
    
}