

#include "ToneMapping.h"

Imagen ToneMapping::clamp(Imagen imagen, float clamp){
    Imagen result(imagen.getHeight(), imagen.getWidth(),imagen.getColorResolution(), imagen.getComment(), 1);
    cout << result.getHeight() << " "  << result.getWidth() << endl;
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
//    cout << "equilize" << endl;
    float MAX = imagen.getMax();
    
    Imagen result(imagen.getHeight(), imagen.getWidth(),imagen.getColorResolution(), imagen.getComment(), 1);
    double newMax = 0.0;
    //Para cada pixel...
    for(int i = 0; i < imagen.getHeight(); i ++){
        for(int j = 0; j < imagen.getWidth(); j ++){
            RGB aux = imagen._imagenHDR[i][j];
            RGB fin(aux.getRed()/MAX, aux.getGreen()/MAX, aux.getBlue()/MAX);
            result._imagenHDR[i][j] = fin;
            newMax = max(newMax,aux.getRed()*255,aux.getGreen()*255,aux.getBlue()*255);
        }
    }
    result.setMax(newMax);
    return result;
}

Imagen ToneMapping::clampEqualize(Imagen imagen, float clamp){
    Imagen result(imagen.getHeight(), imagen.getWidth(),imagen.getColorResolution(), imagen.getComment(), clamp);
    
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
 //   Imagen aux = equalize(Image);
    Imagen result(Image.getHeight(), Image.getWidth(),Image.getColorResolution(), Image.getComment(), 1);
    double maxV = Image.getMax();
    double newMax = 0.0;
    //Para cada pixel...
    for(int i = 0; i < Image.getHeight(); i ++){
        for(int j = 0; j < Image.getWidth(); j ++){
            RGB x = Image._imagenHDR[i][j];
            if(x.getRed() > maxV) x.setRed(maxV);
            else x.setRed(pow(x.getRed(),1/gamma)/pow(maxV,1/gamma));

            if(x.getGreen() > maxV) x.setGreen(maxV);
            else x.setGreen(pow(x.getGreen(),1/gamma)/pow(maxV,1/gamma));

            if(x.getBlue() > maxV) x.setBlue(maxV);
            else x.setBlue(pow(x.getBlue(),1/gamma)/pow(maxV,1/gamma));
     
         //   x.setBlue(pow(x.getBlue()/aux.getMax(),gamma)*aux.getMax());
 
        //    x.setGreen(pow(x.getGreen()/aux.getMax(),gamma)*aux.getMax());
            result._imagenHDR[i][j] = x;
            newMax = max(newMax,x.getRed()*255,x.getGreen()*255,x.getBlue()*255);
        }
    }
    result.setMax(newMax);
    return result;
}

Imagen ToneMapping::clampGamma(Imagen Image, float gamma, float clamp_){
    Imagen result(Image.getHeight(), Image.getWidth(),Image.getColorResolution(), Image.getComment(), 1);
    double maxV = Image.getMax();
    //Para cada pixel...
    for(int i = 0; i < Image.getHeight(); i ++){
        for(int j = 0; j < Image.getWidth(); j ++){
            RGB x = Image._imagenHDR[i][j];
            if(x.getRed() > clamp_) x.setRed(1);
            else x.setRed(pow(x.getRed(),1/gamma)/pow(maxV,1/gamma));

            if(x.getGreen() > clamp_) x.setGreen(1);
            else x.setGreen(pow(x.getGreen(),1/gamma)/pow(maxV,1/gamma));

            if(x.getBlue() > clamp_) x.setBlue(1);
            else x.setBlue(pow(x.getBlue(),1/gamma)/pow(maxV,1/gamma));
     
         //   x.setBlue(pow(x.getBlue()/aux.getMax(),gamma)*aux.getMax());
 
        //    x.setGreen(pow(x.getGreen()/aux.getMax(),gamma)*aux.getMax());
            result._imagenHDR[i][j] = x;
        }
    }
    return result;
}

Imagen ToneMapping::reinhard(Imagen Image){
//    Imagen aux = clampEqualize(Image, clamp);
    Imagen result(Image.getHeight(), Image.getWidth(),Image.getColorResolution(), Image.getComment(), 1);
    
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

Imagen ToneMapping::reinhard2(Imagen Image, float _clamp){
//    Imagen aux = clampEqualize(Image, clamp);
    Imagen result(Image.getHeight(), Image.getWidth(),Image.getColorResolution(), Image.getComment(), 1);
    
    //Para cada pixel...
    for(int i = 0; i < Image.getHeight(); i ++){
        for(int j = 0; j < Image.getWidth(); j ++){
            RGB x = Image._imagenHDR[i][j];
            RGB n = x * (x / (_clamp*_clamp) + 1);
            RGB d = x + 1;
            result._imagenHDR[i][j] = n / d;
        }
    }
    return result;
}

double max(const double a, const double b, const  double c, const double d){
    if(a > b && a > c && a > d) return a;
    else if(b > c && b > d) return b;
    else if(c > d) return c;
    else return d;
}