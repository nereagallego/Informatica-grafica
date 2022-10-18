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

class ToneMapping{
private:
  
public:

   Transformppm clamp(Transformppm Imagen, float clamp_=1);
   Transformppm equalize(Transformppm Image);
   Transformppm clampEqualize(Transformppm Image, float clamp);
   Transformppm gammaCurve(Transformppm Image, float gamma);
   Transformppm clampGamma(Transformppm Image, float gamma, float clamp=1);
    
   
};



#endif