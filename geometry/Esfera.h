#ifndef ESFERA_HPP
#define ESFERA_HPP


#include "../math/Direccion.h"
#include <cmath>
#include <iostream>
#include "../math/CoordenadasHomogeneas.h"
#include "Ray.h"
#include "../math/Direccion.h"
#include "Primitive.h"

class Ray;

class Esfera : public Primitive {
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
    Esfera(Direccion eje, Punto centro, Punto referencia): _radio(eje.modulo()/2), _centro(centro), _ejeY(eje.normalizar()), _referencia(referencia) 
    {
         Direccion rad = centro - referencia;
        if(abs(rad.modulo() - _radio) > 10E-6){
            cerr << "Parámetros incorrectos " << endl;
            cerr << "Radio: "  << _radio << " distancia del centro a la ciudad de referencia "  << rad.modulo() << endl;
        }
         _ejeZ = rad.normalizar();
         _ejeX = crossProduct(_ejeY,_ejeZ).normalizar();
    };

    Esfera(Direccion eje, Punto centro, Punto referencia, RGB emision): Primitive(emision), _radio(eje.modulo()/2),  _centro(centro), _ejeY(eje.normalizar()), _referencia(referencia)  {
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
    Punto pointDefinition(float incl, float azim);

    Direccion getEjeY();
    Direccion getEjeX();
    Direccion getEjeZ();
    Punto getCentro();
    Punto getReferencia();
    float getRadio();

    Intersect intersect(Ray r) override;
};

#endif