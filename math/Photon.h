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
        Direccion _incidentDir;
        RGB _flux;
    public:
        Photon(Punto pos, Direccion incidentDir, RGB flux): _position(pos), _incidentDir(incidentDir), _flux(flux){

        }
   

};

#endif