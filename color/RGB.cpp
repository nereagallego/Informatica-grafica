#include "RGB.h"

RGB::RGB(double red_, double green_, double blue_){
    Red = red_;
    Green = green_;
    Blue = blue_;
}

double RGB::getGreen(){
    return Green;
}

double RGB::getRed(){
    return Red;
}

double RGB::getBlue(){
    return Blue;
}

void RGB::setGreen(double green_){
    Green=green_;
}

void RGB::setRed(double red_){
    Red = red_;
}

void RGB::setBlue(double blue_){
     Blue = blue_;
}

ostream& operator<<(ostream& os, const RGB p) {
    os << " (" << p.Red  << ", " << p.Green << ", " << p.Blue << ")" ;
    return os;
}

RGB RGB::operator+(RGB a){
    return RGB(Red+a.getRed(), Green + a.getGreen(), Blue + a.getBlue());
}

RGB RGB::operator-(RGB a){
    return RGB(Red-a.getRed(), Green - a.getGreen(), Blue - a.getBlue());
}

RGB RGB::operator *(RGB a){
    return RGB(Red*a.getRed(), Green*a.getGreen(), Blue*a.getBlue());
}

RGB RGB::operator/(RGB a){
    return RGB(Red/a.getRed(), Green/a.getGreen(), Blue/a.getBlue());
}



RGB RGB::operator +(double num){
    return RGB(Red+num, Green+num, Blue+num);
}

RGB RGB::operator -(double num){
    return RGB(Red-num, Green-num, Blue-num);
}

RGB RGB::operator *(double num){
    return RGB(Red*num, Green*num, Blue*num);
}

RGB RGB::operator /(double num){
    return RGB(Red/num, Green/num, Blue/num);
}

