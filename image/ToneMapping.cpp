

#include "ToneMapping.h"

Imagen ToneMapping::clamp(Imagen imagen, float clamp){
    Imagen result(imagen.getHeight(), imagen.getWidth(),imagen.getColorResolution(), imagen.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < imagen.getHeight(); i ++){
        for(int j = 0; j < imagen.getWidth(); j ++){
            RGB aux = imagen._imagenHDR[i][j];
            if(aux.getRed() > clamp){
                aux.setRed(clamp);
            } 
            if(aux.getGreen() > clamp){
                aux.setGreen(clamp);
            }
            if(aux.getBlue() > clamp){
                aux.setBlue(clamp);
            } 
            result._imagenHDR[i][j] = aux;
        }
    }
    return result;
}
    

Imagen ToneMapping::equalize(Imagen imagen){
    float MAX = imagen.getMax();
    Imagen result(imagen.getHeight(), imagen.getWidth(),imagen.getColorResolution(), imagen.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < imagen.getHeight(); i ++){
        for(int j = 0; j < imagen.getWidth(); j ++){
            RGB aux = imagen._imagenHDR[i][j];
            aux.setRed(aux.getRed()/MAX);
            aux.setGreen(aux.getGreen()/MAX);
            aux.setBlue(aux.getBlue()/MAX);
            result._imagenHDR[i][j] = aux;
        }
    }
    return result;
}

Imagen ToneMapping::clampEqualize(Imagen imagen, float clamp){
    Imagen result(imagen.getHeight(), imagen.getWidth(),imagen.getColorResolution(), imagen.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < imagen.getHeight(); i ++){
        for(int j = 0; j < imagen.getWidth(); j ++){
            RGB aux = imagen._imagenHDR[i][j];
            if( aux.getRed() > clamp) aux.setRed(1);
            else aux.setRed(aux.getRed()/clamp);

            
            if( aux.getBlue() > clamp) aux.setBlue(1);
            else aux.setBlue(aux.getBlue()/clamp);


            if( aux.getGreen() > clamp) aux.setGreen(1);
            else aux.setGreen(aux.getGreen()/clamp);
            result._imagenHDR[i][j] = aux;
        }
    }
    return result;
    
}



Imagen ToneMapping::gammaCurve(Imagen Image, float gamma){
    Imagen aux = equalize(Image);
    Imagen result(aux.getHeight(), aux.getWidth(),aux.getColorResolution(), aux.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < Image.getHeight(); i ++){
        for(int j = 0; j < Image.getWidth(); j ++){
            RGB x = Image._imagenHDR[i][j];
            x.setRed(pow(x.getRed()/aux.getMax(),gamma)*aux.getMax());
     
            x.setBlue(pow(x.getBlue()/aux.getMax(),gamma)*aux.getMax());
 
            x.setGreen(pow(x.getGreen()/aux.getMax(),gamma)*aux.getMax());
            result._imagenHDR[i][j] = x;
        }
    }
    return result;
}

Imagen ToneMapping::clampGamma(Imagen Image, float gamma, float clamp_){
    Imagen aux = clampEqualize(Image,clamp_);
    Imagen result(aux.getHeight(), aux.getWidth(),aux.getColorResolution(), aux.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < Image.getHeight(); i ++){
        for(int j = 0; j < Image.getWidth(); j ++){
            RGB x = Image._imagenHDR[i][j];
            if(x.getRed() < aux.getMax()){
                x.setRed(pow(x.getRed(),gamma));
            }
            if(x.getBlue() < aux.getMax()){
                x.setBlue(pow(x.getBlue(),gamma));
            }
            if(x.getGreen() < aux.getMax()){
                x.setGreen(pow(x.getGreen(),gamma));
            }
            result._imagenHDR[i][j] = x;
        }
    }
    return result;
}

Imagen ToneMapping::reinhard(Imagen Image, float clamp){
    Imagen aux = clampEqualize(Image, clamp);
    Imagen result(aux.getHeight(), aux.getWidth(),aux.getColorResolution(), aux.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < Image.getHeight(); i ++){
        for(int j = 0; j < Image.getWidth(); j ++){
            RGB x = Image._imagenHDR[i][j];
            x.setRed(x.getRed()/(1+x.getRed()));
            x.setGreen(x.getGreen()/(1+x.getGreen()));
            x.setBlue(x.getBlue()/(1+x.getBlue()));
            result._imagenHDR[i][j] = x;
        }
    }
    return result;
}