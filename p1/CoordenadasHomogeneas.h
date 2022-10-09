#ifndef CORDENADAS_HOMOGENEAS_HPP
#define CORDENADAS_HOMOGENEAS_HPP

#include <stdlib.h>
#include "Punto.h"
#include "Direccion.h"
#include "Matrix4.h"
#include "vector"
#include <exception>

class CoordenadasHomogeneas
{
private:
    float coord[4];
    /**
     * @brief Construct a new Coordenadas Homogeneas object
     * 
     * @param x coordenada x
     * @param y coordenada y
     * @param z coordenada z
     * @param w tipo de dato
     */
    CoordenadasHomogeneas(const float x, const float y, const float z, const float w);
public:
    
    /**
     * @brief Construct a new Coordenadas Homogeneas object
     * Construye una coordenada homogenea a partir de un punto
     * 
     * @param p punto desde el cual se construye la coordenada
     */
    CoordenadasHomogeneas(const Punto p);
    /**
     * @brief Construct a new Coordenadas Homogeneas object
     * Construye una coordenada homogenea a partir de una dirección
     * 
     * @param d dirección desde la cual se construye la coordenada
     */
    CoordenadasHomogeneas(const Direccion d);

    /**
     * @brief Devuelve las coordenadas resultantes de realizar la operación de
     *  translación
     * 
     * @param x movimiento en el eje x
     * @param y movimiento en el eje y
     * @param z movimiento en el eje z
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas translacion(const float x, const float y, const float z);

    /**
     * @brief devuelve la coordenada resultante de escalar 
     * 
     * @param x escalado en x
     * @param y escalado en y
     * @param z escalado en z
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas escala(const float x, const float y, const float z);

    /**
     * @brief devuelve las coordenadas resultado de rotar en el eje X rad 
     * radianes
     * 
     * @param rad radianes a rotar
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas rotacionX(const float rad);
    
    /**
     * @brief devuelve las coordenadas resultado de rotar en el eje Y rad 
     * radianes
     * 
     * @param rad radianes a rotar
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas rotacionY(const float rad);

    /**
     * @brief devuelve las coordenadas resultado de rotar en el eje Z rad
     * radianes
     * 
     * @param rad radianes a rotar
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas rotacionZ(const float rad);

    /**
     * @brief Realiza la operacion de cambio de base con la nuevabase contenida 
     * en la matriz m
     * 
     * @param m matriz de cambio de base
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas cambioBase(Matrix4 m);

    /**
     * @brief Realiza las operaciones resultantes de operar con la matriz m
     * 
     * @param m 
     * @return CoordenadasHomogeneas 
     */
    CoordenadasHomogeneas combinaciones(Matrix4 m);

    /**
     * @brief devuelve un punto dadas las coordenadas
     * 
     * @return Punto 
     */
    Punto punto();

    /**
     * @brief devuelve una dirección dadas las coordenadas
     * 
     * @return Direccion 
     */
    Direccion direccion();

    // pretty stdout
    friend ostream& operator<<(ostream& os, const CoordenadasHomogeneas c);
};





#endif