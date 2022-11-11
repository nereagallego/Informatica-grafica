#include "math/Direccion.h"
#include <cmath>
#include <iostream>
#include "math/CoordenadasHomogeneas.h"
#include "geometry/Ray.h"
#include "math/Direccion.h"
#include "geometry/Primitive.h"

class Planet  {
private:
    Direccion _ejeY,_ejeX,_ejeZ;
    Punto _centro;
    Punto _referencia;
    float _radio;
public:
    /**
     * @brief Construct a new Esfera object
     * 
     * @param eje eje de la esfera
     * @param centro centro de la esfera
     * @param referencia punto de referencia de la esfera
     */
    Planet(Direccion eje, Punto centro, Punto referencia): _radio(eje.modulo()/2), _centro(centro), _ejeY(eje.normalizar()), _referencia(referencia) 
    {
         Direccion rad = centro - referencia;
        if(abs(rad.modulo() - _radio) > 10E-6){
            cerr << "Parámetros incorrectos " << endl;
            cerr << "Radio: "  << _radio << " distancia del centro a la ciudad de referencia "  << rad.modulo() << endl;
        }
         _ejeZ = rad.normalizar();
         _ejeX = crossProduct(_ejeY,_ejeZ).normalizar();
    };

    Planet(Direccion eje, Punto centro, Punto referencia, RGB emision): _radio(eje.modulo()/2),  _centro(centro), _ejeY(eje.normalizar()), _referencia(referencia)  {
        Direccion rad = centro - referencia;
        if(abs(rad.modulo() - _radio) > 10E-6){
            cerr << "Parámetros incorrectos " << endl;
            cerr << "Radio: "  << _radio << " distancia del centro a la ciudad de referencia "  << rad.modulo() << endl;
        }
         _ejeZ = rad.normalizar();
         _ejeX = crossProduct(_ejeY,_ejeZ).normalizar();
    }; 
    /**
     * @brief devuelve el punto dado su azimuth y su inclinación
     * 
     * @paramia incl inclinación (en radianes)
     * @param azim azimuth (en radianes)
     * @return Punto 
     */
    Punto pointDefinition(float incl, float azim){
        if(incl < 0 or incl > M_PI or azim < - M_PI or azim > M_PI){
            cout << "Parametros no válidos." << endl;
        }
        Punto point(_radio*sin(incl)*cos(azim), _radio*sin(incl)*sin(azim), _radio * cos(incl));
        // Se obtiene la normal a la superficie restando la ciudad de la referencia - centro
        float v[4][4] = {{_ejeX.getX(),_ejeY.getX(),_ejeZ.getX(),_centro.getX()},{_ejeX.getY(),_ejeY.getY(),_ejeZ.getY(),_centro.getY()},{_ejeX.getZ(),_ejeY.getZ(),_ejeZ.getZ(),_centro.getZ()},{0,0,0,1}};
        Matrix4 T(v);

        CoordenadasHomogeneas w(point);

        return w.cambioBase(T).punto();
    }

    Direccion getEjeY();
    Direccion getEjeX();
    Direccion getEjeZ();
    Punto getCentro();
    Punto getReferencia();
    float getRadio();

};