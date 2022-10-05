#include "Esfera.h"

Esfera::Esfera(Direccion _eje, Punto _centro, Punto _referencia){
    
    Direccion rad = _centro - _referencia;
    if(abs(rad.modulo() - _eje.modulo()/2) < 0.000006){
        cerr << "Parámetros incorrectos " << endl;
    }
    centro = _centro;
    eje = _eje;
    referencia = _referencia;
}

Punto Esfera::pointDefinition(float incl, float azim){
    if(incl < 0 or incl > M_PI or azim < - M_PI or azim > M_PI){
        cout << "Parametros no válidos." << endl;
    }
    float r = eje.modulo()/2;
    Punto point(r*sin(incl)*cos(azim), r*sin(incl)*sin(azim), r * cos(incl));
    // Se obtiene la normal a la superficie restando la ciudad de la referencia - centro
    Direccion normal(centro - referencia);
    Direccion producto = crossProduct(eje,normal);
    float v[4][4] = {{eje.x,normal.x,producto.x,centro.x},{eje.y,normal.y,producto.y,centro.y},{eje.z,normal.z,producto.z,centro.z},{0,0,0,1}};
    Matrix4 m1(v);

    CoordenadasHomogeneas T(point);
    return T.cambioBase(m1).punto();



   /* CoordenadasHomogeneas c(referencia);
    Direccion ref = referencia - centro;
    // float producto = ref*eje/(ref.modulo()*eje.modulo());
    // cout << "El producto es: " << producto << endl;
    float angulo = acos(ref*eje/(ref.modulo()*eje.modulo()));
    cout << "El angulo es " << angulo << endl;
    CoordenadasHomogeneas c1 = c.rotacionZ(M_PI/2-angulo);
    Punto p = c1.punto();
    Direccion ref2 = p-centro;
    cout << "La primera coord es " << c1.coord[0] << " " << c1.coord[1] << " "<< c1.coord[2] << " y su modulo es " << ref2.modulo() << endl;
    CoordenadasHomogeneas c2 = c1.rotacionY(azim);
    cout << "La segunda coord es " << c2.coord[0] << " " << c2.coord[1] << " "<< c2.coord[2] << endl;
    c2 = c2.rotacionX(M_PI/2-incl);

    cout << "Punto final: "  << c2.coord[0] << " " << c2.coord[1] << " "<< c2.coord[2] << endl;
    p = c2.punto();
    cout << "Distancia al centro deberia ser " << ref.modulo(); 
    ref = p - centro;
    cout << " y es " << ref.modulo() << endl;
    return c2.punto();
    */
}