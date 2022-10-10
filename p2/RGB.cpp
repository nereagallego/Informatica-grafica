#include "RGB.h"

RGB::RGB(float red_, float green_, float blue_){
    Red = red_;
    Green = green_;
    Blue = blue_;
}

float RGB::getGreen(){
    return Green;
}

float RGB::getRed(){
    return Red;
}

float RGB::getBlue(){
    return Blue;
}