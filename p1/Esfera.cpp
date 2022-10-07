#include "Esfera.h"

Esfera::Esfera(Direccion _eje, Punto _centro, Punto _referencia){
    
    Direccion rad = _centro - _referencia;
    radio = _eje.modulo()/2;
    if(abs(rad.modulo() - radio) > 10E-6){
        cerr << "Parámetros incorrectos " << endl;
        cerr << "Radio: "  << radio << " distancia del centro a la ciudad de referencia "  << rad.modulo() << endl;
    }
    centro = _centro;
    ejeY = _eje.normalizar();
    referencia = _referencia;
    ejeZ = rad.normalizar();
    ejeX = crossProduct(ejeY,ejeZ).normalizar();

}

Punto Esfera::pointDefinition(float incl, float azim){
    if(incl < 0 or incl > M_PI or azim < - M_PI or azim > M_PI){
        cout << "Parametros no válidos." << endl;
    }
    Punto point(radio*sin(incl)*cos(azim), radio*sin(incl)*sin(azim), radio * cos(incl));
    // Se obtiene la normal a la superficie restando la ciudad de la referencia - centro
    float v[4][4] = {{ejeX.getX(),ejeY.getX(),ejeZ.getX(),centro.getX()},{ejeX.getY(),ejeY.getY(),ejeZ.getY(),centro.getY()},{ejeX.getZ(),ejeY.getZ(),ejeZ.getZ(),centro.getZ()},{0,0,0,1}};
    Matrix4 T(v);

    CoordenadasHomogeneas w(point);
    // Direccion ciudad_ref(referencia - centro);
    // cout << "Distancia al centro deberia ser " << ciudad_ref.modulo(); 
    // Direccion ref(w.cambioBase(T).punto() - centro);
    // cout << " y es " << ref.modulo() << endl;
    
    
    return w.cambioBase(T).punto();



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