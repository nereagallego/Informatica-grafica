#include "Direccion.h"
#include "CoordenadasHomogeneas.h"
#include "Matrix4.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){

    Direccion d1(1,2,3);
    Direccion d4(1,2,3);
    Punto d2(1,2,3);

    Punto d3 = d1 + d2;

    cout << d3.x << " " << d3.y << " " << d3.z << endl;

    Punto p2(1,2,3);

    Direccion p3 = d2 - p2;

    float mod = d1.modulo();

    cout << "El modulo es " << mod << endl;

    Direccion norm = d1.normalizar();

    //DOT PRODUCT

    float res = d1*d4;

    cout << "El producto escalar es: " << res << endl;

    
    cout << norm.x << " " << norm.y << " " << norm.z << endl;


    //CROSS PRODUCT

    Direccion d5(1,2,3);
    Direccion d6(0,0,1);
    
    Direccion cross = crossProduct(d5,d6);

    cout << cross.x << " " << cross.y << " " << cross.z << endl;

    CoordenadasHomogeneas c1 = CoordenadasHomogeneas(p2);


    //float v[4][4] = {{1,0,0,2},{0,1,0,2},{0,0,1,2},{0,0,0,1}};
    //Matrix4 m(v);
    cout << "Coordenada " << c1.coord[0] << " " << c1.coord[1] << " " << c1.coord[2] << endl;
    CoordenadasHomogeneas res1 = c1.translacion(2,2,2);

    cout << "Translacion " << res1.coord[0] << " " << res1.coord[1] << " " << res1.coord[2] << endl;

    // MATRIX 4 x 4
  //  float v[4][4] = {{1,2,0,0},{3,0,0,0},{0,0,0,0},{0,0,0,0}};
/*    Matrix4 m1(v), m2;

    cout << m1 << endl;
    Matrix4 m3 = m1 + m2;
    cout << m3 << endl;
    Matrix4 m4 = m1*m3;
    cout << m4 << endl;

    //SCALE
    CoordenadasHomogeneas c2 = CoordenadasHomogeneas(p2);

    CoordenadasHomogeneas res2 = c1.escala(2,2,1);

    cout << res2.coord[0] << " " << res2.coord[1] << " " << res2.coord[2] << endl;

    //ROTATION

    CoordenadasHomogeneas c3 = CoordenadasHomogeneas(p2);

    CoordenadasHomogeneas res3 = c3.rotacionZ(3.141592);

    cout << res3.coord[0] << " " << res3.coord[1] << " " << res3.coord[2] << endl;*/


    //CHANGE OF BASIS

    float v[4][4] = {{1,2,3,0},{2,2,2,0},{8,0,1,0},{0,4,0,1}};
    Matrix4 m1(v);
    CoordenadasHomogeneas r5 = c1.cambioBase(m1);

    cout << "El cambio de base es " << r5.coord[0] <<" " <<  r5.coord[1]<<" "   << r5.coord[2] <<" " << r5.coord[3] << endl;

    cout << m1 << endl;
    cout << "Matriz inversa: " << m1.inversa() << endl;



    return 0;
}