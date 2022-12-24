#ifndef AREA_LIGHT_HPP
#define AREA_LIGHT_HPP

#include "Light.h"
#include "../geometry/Plano.h"
#include "../scene/BSDF.h"

class AreaLight : public Light{
    
    Plano _p;
public:

    
    /**
     * @brief Construye un area light dado su normal, la distnacia, el centro y 
     *        la intensidad de la luz
     * 
     * @param normal normal de la luz
     * @param d distancia del centro focal de la cámara a la luz
     * @param center punto de centro de la luz
     * @param power potencia de la luz
     */
    AreaLight(Direccion normal,float d,Punto center, RGB power):  _p(Plano(normal,d)), Light(center,power) {
        if(normal * center + d != 0) throw logic_error("el centro no pertenece al plano de la luz de area");
        
    }

    virtual ~AreaLight() { /* whatever goes here, or nothing... */ }
    Direccion getNormal() { return _p.getNormal();}
    float getDistancia() { return _p.getDistancia();}
    BSDF getEmission() { return _p.getEmision();}

    /**
     * @brief función virtual para calcular la intersección de un rayo con la 
     *        luz de área
     * 
     * @param r rayo con el que intersecta
     */
    virtual Intersect intersect(Ray r) = 0;
};


class SquareLight : public AreaLight {
    Punto _p1, _p2, _p3, _p4;
public:

    /**
     * @brief devuelve una luz cuadrad dada su normal, la distancia del punto 
     *        focal de la cámara a la luz, el centro de la luz, la potencia de 
     *        la luz, y los cuatro puntos que definen el cuadrado de la luz. 
     *        Solo funciona cuando los cuatro puntos forman un cuadrado en el 
     *        plano que se define la luz.
     * 
     * @param normal normal de la luz
     * @param d distancia del centro focal de la cámara a la luz
     * @param center punto de centro de la luz
     * @param power potencia de la luz
     */
    SquareLight(Direccion normal,float d,Punto center, RGB power, Punto p1, Punto p2, Punto p3, Punto p4): _p1(p1), _p2(p2), _p3(p3), _p4(p4), AreaLight(normal, d, center, power) {
        if(normal * p1 + d != 0) throw logic_error("el punto p1 no pertenece al plano de la luz de area");
        if(normal * p2 + d != 0) throw logic_error("el punto p2 no pertenece al plano de la luz de area"); 
        if(normal * p3 + d != 0) throw logic_error("el punto p3 no pertenece al plano de la luz de area");
        if(normal * p4 + d != 0) throw logic_error("el punto p4 no pertenece al plano de la luz de area");
    }


    /**
     * @brief función para calcular la intersección de un rayo con la 
     *        luz de área
     * 
     * @param r rayo con el que intersecta
     */
    Intersect intersect(Ray r) override {
        Intersect s;
        s._emision = this->getEmission();
        float denominador = r.getDireccion() * this->getNormal();
        if(denominador == 0){ s._intersect = false; return s;}
        else s._intersect = true;
        s._t = -(this->getDistancia() + this->getNormal() * r.getPunto())/denominador;
        if(s._t <= 0.00001) s._intersect = false;
        s._punto = r.getPunto() + r.getDireccion() * s._t;
        
        if(r.getDireccion().angulo(this->getNormal()) < M_PI / 2)
        s._normal = this->getNormal().normalizar();
        else 
        {
            s._normal = this->getNormal().normalizar() *-1;
        //  cout << "desde dentro";
        }
        s._intersect = s._intersect && s._punto.getX() >= _p1.getX() && s._punto.getX() <= _p3.getX() && s._punto.getY() >= _p1.getY() && s._punto.getY() <= _p3.getY() && s._punto.getZ() >= _p1.getZ() && s._punto.getZ() <= _p3.getZ();
       
        return s;
    }
};

class CircleLight : public AreaLight {
    double _radius;
public:

    /**
     * @brief devuelve una luz cuadrad dada su normal, la distancia del punto 
     *        focal de la cámara a la luz, el centro de la luz, la potencia de 
     *        la luz, y el radio del círculo
     * 
     * @param normal normal de la luz
     * @param d distancia del centro focal de la cámara a la luz
     * @param center punto de centro de la luz
     * @param power potencia de la luz
     * @param radius radio del círculo
     */
    CircleLight(Direccion normal,float d,Punto center, RGB power, double radius): _radius(radius), AreaLight(normal, d, center, power) {}

    /**
     * @brief función para calcular la intersección de un rayo con la 
     *        luz de área
     * 
     * @param r rayo con el que intersecta
     */
    Intersect intersect(Ray r) override {
        Intersect s;
        s._emision = this->getEmission();
        float denominador = r.getDireccion() * this->getNormal();
        if(denominador == 0){ s._intersect = false; return s;}
        else s._intersect = true;
        s._t = -(this->getDistancia() + this->getNormal() * r.getPunto())/denominador;
        if(s._t <= 0.00001) s._intersect = false;
        s._punto = r.getPunto() + r.getDireccion() * s._t;
        
        if(r.getDireccion().angulo(this->getNormal()) < M_PI / 2)
        s._normal = this->getNormal().normalizar();
        else 
        {
            s._normal = this->getNormal().normalizar() *-1;
        //  cout << "desde dentro";
        }
        Direccion d = s._punto - this->getCenter();
        s._intersect = s._intersect && d.modulo() <= _radius;
        return s;
    }
};
#endif