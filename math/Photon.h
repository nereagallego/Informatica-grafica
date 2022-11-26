#ifndef PHOTON_HPP
#define PHOTON_HPP
#include <stdlib.h>
#include "Direccion.h"
#include "Punto.h"
#include <iostream>
#include "../color/RGB.h"
using namespace std;



class Direccion;

// Clase Photon
class Photon{
    private:
        Punto _position;
        Direccion _incidentDir, _normal;
        RGB _flux;
    public:
        Photon(Punto pos, Direccion incidentDir, RGB flux, Direccion normal): _position(pos), _incidentDir(incidentDir), _flux(flux), _normal(normal){

        }
   

};

#endif