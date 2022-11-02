

#include "ToneMapping.h"

Imagen ToneMapping::clamp(Imagen imagen, float clamp){
    vector<RGB> ImagenLocal = imagen.getImagen();
    Imagen result(imagen.getFormat(), "#MAX="+to_string(1),imagen.getComment(), imagen.getSizeResolution(), to_string(imagen.getColorResolution()), imagen.getColorResolution(), 1);
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
    

Imagen ToneMapping::equalize(Imagen imagen){
    float MAX = imagen.getMax();
    vector<RGB> ImagenLocal = imagen.getImagen();
    Imagen result(imagen.getFormat(), "#MAX="+to_string(1),imagen.getComment(), imagen.getSizeResolution(), to_string(imagen.getColorResolution()), imagen.getColorResolution(), 1);
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

Imagen ToneMapping::clampEqualize(Imagen imagen, float clamp){
    vector<RGB> ImagenLocal = imagen.getImagen();
    Imagen result(imagen.getFormat(), "#MAX="+to_string(1),imagen.getComment(), imagen.getSizeResolution(), to_string(imagen.getColorResolution()), imagen.getColorResolution(), 1);
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



Imagen ToneMapping::gammaCurve(Imagen Image, float gamma){
    Imagen aux = equalize(Image);
    vector<RGB> ImagenLocal = aux.getImagen();
    Imagen result(aux.getFormat(), "#MAX="+to_string(1),aux.getComment(), aux.getSizeResolution(), to_string(aux.getColorResolution()), aux.getColorResolution(), 1);
    vector<RGB> imagenFinal;
    for(RGB x: ImagenLocal){
       // if(x.getRed() < aux.getMax()){
            x.setRed(pow(x.getRed()/aux.getMax(),gamma)*aux.getMax());
     //   }
    //    if(x.getBlue() < aux.getMax()){
            x.setBlue(pow(x.getBlue()/aux.getMax(),gamma)*aux.getMax());
    //    }
    //    if(x.getGreen() < aux.getMax()){
            x.setGreen(pow(x.getGreen()/aux.getMax(),gamma)*aux.getMax());
    //    }
        imagenFinal.push_back(x);
    } 
    result.setImagen(imagenFinal);
    return result;
}

Imagen ToneMapping::clampGamma(Imagen Image, float gamma, float clamp_){
    Imagen aux = clampEqualize(Image,clamp_);
    vector<RGB> ImagenLocal = aux.getImagen();
    Imagen result(aux.getFormat(), "#MAX="+to_string(1),aux.getComment(), aux.getSizeResolution(), to_string(aux.getColorResolution()), aux.getColorResolution(), 1);
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

Imagen ToneMapping::reinhard(Imagen Image, float clamp){
    Imagen aux = clampEqualize(Image, clamp);
    vector<RGB> ImagenLocal = aux.getImagen();
    Imagen result(aux.getFormat(), "#MAX="+to_string(1),aux.getComment(), aux.getSizeResolution(), to_string(aux.getColorResolution()), aux.getColorResolution(), 1);
    vector<RGB> imagenFinal;
    for(RGB x: ImagenLocal){
        x.setRed(x.getRed()/(1+x.getRed()));
        x.setGreen(x.getGreen()/(1+x.getGreen()));
        x.setBlue(x.getBlue()/(1+x.getBlue()));
        imagenFinal.push_back(x);
    } 
    result.setImagen(imagenFinal);
    return result;
}