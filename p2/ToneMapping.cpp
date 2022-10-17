

#include "ToneMapping.h"

Transformppm ToneMapping::clamp(Transformppm Imagen){
    vector<RGB> ImagenLocal = Imagen.getImagen();
    vector<RGB> ImagenResultado;
    //Para cada pixel...
    for(RGB aux: ImagenLocal){
        if(aux.getRed() > 1){
            aux.setRed(0);
        }
        if(aux.getGreen() > 1){
            aux.setGreen(0);
        }
        if(aux.getBlue() > 1){
            aux.setBlue(0);
        }
        ImagenResultado.push_back(aux);
    }
    return Transformppm(ImagenResultado);
}