

#include "ToneMapping.h"

Transformppm ToneMapping::clamp(Transformppm Imagen, float clamp){
    vector<RGB> ImagenLocal = Imagen.getImagen();
    Transformppm result(Imagen.getFormat(), "#MAX="+to_string(1),Imagen.getComment(), Imagen.getSizeResolution(), to_string(Imagen.getColorResolution()), Imagen.getColorResolution(), 1);
    vector<RGB> ImagenResultado;
    //Para cada pixel...
    for(RGB aux: ImagenLocal){
        if(aux.getRed() > clamp){
            aux.setRed(clamp);
        } 
        if(aux.getGreen() > clamp){
            aux.setGreen(clamp);
        }
        if(aux.getBlue() > clamp){
            aux.setBlue(clamp);
        } 
        ImagenResultado.push_back(aux);
    }
    result.setImagen(ImagenResultado);
    return result;
}
    

Transformppm ToneMapping::equalize(Transformppm Imagen){
    float MAX = Imagen.getMax();
    vector<RGB> ImagenLocal = Imagen.getImagen();
    Transformppm result(Imagen.getFormat(), "#MAX="+to_string(1),Imagen.getComment(), Imagen.getSizeResolution(), to_string(Imagen.getColorResolution()), Imagen.getColorResolution(), 1);
    vector<RGB> ImagenResultado;
    //Para cada pixel...
    for(RGB aux: ImagenLocal){
        aux.setRed(aux.getRed()/MAX);
        aux.setGreen(aux.getGreen()/MAX);
        aux.setBlue(aux.getBlue()/MAX);
        ImagenResultado.push_back(aux);
    }
    result.setImagen(ImagenResultado);
    return result;
}

Transformppm ToneMapping::clampEqualize(Transformppm Imagen, float clamp){
    vector<RGB> ImagenLocal = Imagen.getImagen();
    Transformppm result(Imagen.getFormat(), "#MAX="+to_string(1),Imagen.getComment(), Imagen.getSizeResolution(), to_string(Imagen.getColorResolution()), Imagen.getColorResolution(), 1);
    vector<RGB> ImagenResultado;
    //Para cada pixel...
    for(RGB aux: ImagenLocal){
        if( aux.getRed() > clamp) aux.setRed(1);
        else aux.setRed(aux.getRed()/clamp);

        
        if( aux.getBlue() > clamp) aux.setBlue(1);
        else aux.setBlue(aux.getBlue()/clamp);


        if( aux.getGreen() > clamp) aux.setGreen(1);
        else aux.setGreen(aux.getGreen()/clamp);

        ImagenResultado.push_back(aux);
    }
    result.setImagen(ImagenResultado);
    return result;
}



Transformppm ToneMapping::gammaCurve(Transformppm Image, float gamma){
    Transformppm aux = equalize(Image);
    vector<RGB> ImagenLocal = aux.getImagen();
    Transformppm result(aux.getFormat(), "#MAX="+to_string(1),aux.getComment(), aux.getSizeResolution(), to_string(aux.getColorResolution()), aux.getColorResolution(), 1);
    vector<RGB> imagenFinal;
    for(RGB x: ImagenLocal){
        if(x.getRed() < aux.getMax()){
            x.setRed(pow(x.getRed(),gamma));
        }
        if(x.getBlue() < aux.getMax()){
            x.setBlue(pow(x.getBlue(),gamma));
        }
        if(x.getGreen() < aux.getMax()){
            x.setGreen(pow(x.getGreen(),gamma));
        }
        imagenFinal.push_back(x);
    } 
    result.setImagen(imagenFinal);
    return result;
}

Transformppm ToneMapping::clampGamma(Transformppm Image, float gamma, float clamp_){
    Transformppm aux = clamp(Image,clamp_);
    Transformppm result = gammaCurve(aux,gamma);
    return result;
}