#ifndef TONEMAPPING_HPP
#define TONEMAPPING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
#include "Imagen.h"
#include <cmath>

using namespace std;

namespace ToneMapping{

   /**
    * @brief Realiza la operación de clampeo
    * Si los valores son mayores que clamp_ los deja como clamp_
    * 
    * @param Imagen Objeto de tipo Imagen a transformar
    * @param clamp_ valor de clampeo
    * @return Imagen 
    */
   Imagen clamp(Imagen Imagen, float clamp_=1);

   /**
    * @brief Equaliza una imagen
    * 
    * @param Image imagen a equalizar
    * @return Imagen 
    */
   Imagen equalize(Imagen Image);

   /**
    * @brief Ecualiza una imagen y a continuación clampea a cierto valor
    * 
    * @param Image imagen a modificar
    * @param clamp valor a clampear
    * @return Imagen 
    */
   Imagen clampEqualize(Imagen Image, float clamp);

   /**
    * @brief aplica la curva gamma a una imagen
    * 
    * @param Image imagen a modificar
    * @param gamma valor de la curva gamma
    * @return Imagen 
    */
   Imagen gammaCurve(Imagen Image, float gamma);

   /**
    * @brief campear una imagen y aplicar una curva gamma
    * Primero de camplea y equaliza la imagen y luego se aplica la curva gamma
    * 
    * @param Image imagen a modificar
    * @param gamma valor de la curva gamma
    * @param clamp valor de clampeo
    * @return Imagen 
    */
   Imagen clampGamma(Imagen Image, float gamma, float clamp=1);

   /**
    * @brief Transformación reinhard sencilla de una imagen
    * 
    * @param Image imagen a modificar
    * @return Imagen 
    */
   Imagen reinhard(Imagen Image);

   /**
    * @brief Transformación extended reinhard de una imagen
    * 
    * @param Image imagen a modificar
    * @param _clamp valor del clamp
    * @return Imagen 
    */
   Imagen reinhard2(Imagen image, float _clamp);
    
   
};



#endif