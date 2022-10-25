#ifndef TONEMAPPING_HPP
#define TONEMAPPING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
#include "Transformppm.h"
#include <cmath>

using namespace std;

namespace ToneMapping{

   /**
    * @brief Realiza la operación de clampeo
    * Si los valores son mayores que clamp_ los deja como clamp_
    * 
    * @param Imagen Objeto de tipo Transformppm a transformar
    * @param clamp_ valor de clampeo
    * @return Transformppm 
    */
   Transformppm clamp(Transformppm Imagen, float clamp_=1);

   /**
    * @brief Equaliza una imagen
    * 
    * @param Image imagen a equalizar
    * @return Transformppm 
    */
   Transformppm equalize(Transformppm Image);

   /**
    * @brief Ecualiza una imagen y a continuación clampea a cierto valor
    * 
    * @param Image imagen a modificar
    * @param clamp valor a clampear
    * @return Transformppm 
    */
   Transformppm clampEqualize(Transformppm Image, float clamp);

   /**
    * @brief aplica la curva gamma a una imagen
    * 
    * @param Image imagen a modificar
    * @param gamma valor de la curva gamma
    * @return Transformppm 
    */
   Transformppm gammaCurve(Transformppm Image, float gamma);

   /**
    * @brief campear una imagen y aplicar una curva gamma
    * Primero de camplea y equaliza la imagen y luego se aplica la curva gamma
    * 
    * @param Image imagen a modificar
    * @param gamma valor de la curva gamma
    * @param clamp valor de clampeo
    * @return Transformppm 
    */
   Transformppm clampGamma(Transformppm Image, float gamma, float clamp=1);

   /**
    * @brief Transformación reinhard sencilla de una imagen
    * 
    * @param Image imagen a modificar
    * @param clamp valor del clamp
    * @return Transformppm 
    */
   Transformppm reinhard(Transformppm Image, float clamp);
    
   
};



#endif