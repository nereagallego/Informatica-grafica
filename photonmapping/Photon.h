#ifndef PHOTON_HPP
#define PHOTON_HPP
#include <stdlib.h>
#include "../math/Direccion.h"
#include "../math/Punto.h"
#include <iostream>
#include "../color/RGB.h"
using namespace std;



class Direccion;

// Clase Photon
class Photon{
    private:
        Punto _position;
        Direccion _incidentDir, _normal;
        double _flux;
    public:
        Photon(Punto pos, Direccion incidentDir, double flux, Direccion normal): _position(pos), _incidentDir(incidentDir), _flux(flux), _normal(normal){

        }

        float position(std::size_t i) const { 
            if(i==0) return _position.getX();
            else if(i==1) return _position.getY();
            else if(i==2) return _position.getZ();
            else throw new logic_error("not found position");
        }

        double getFlux() const { return _flux;}
        void setFlux(double f) { _flux = f;}
   

};


#endif