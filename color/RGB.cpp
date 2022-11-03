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

void RGB::setGreen(float green_){
    Green=green_;
}

void RGB::setRed(float red_){
    Red = red_;
}

void RGB::setBlue(float blue_){
     Blue = blue_;
}

ostream& operator<<(ostream& os, const RGB p) {
    os << " (" << p.Red  << ", " << p.Green << ", " << p.Blue << ")" ;
    return os;
}