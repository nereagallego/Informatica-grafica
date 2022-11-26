#ifndef RGB_HPP
#define RGB_HPP

#include <iostream>
#include <stdlib.h>

using namespace std;

//Esta clase RGB guarda los valores como 0 o 1 ya que se utiliza para pasar de HDR a memoria
class RGB{
    private:
    double Red;
    double Green;
    double Blue;

    public:
    /**
     * @brief Construct a new RGB object
     * 
     * @param red_ value of the red pixel
     * @param green_ value of the green pixel
     * @param blue_ value of the blue pixel
     */
    RGB(double red_ ,double green_, double blue_);

    /**
     * @brief Construct a new RGB object
     * Constructor vacío
     * 
     */
    RGB(): Red(0), Green(0), Blue(0){};

    double getRed();
    double getGreen();
    double getBlue();

    void setRed(double Red_);
    void setGreen(double Green_);
    void setBlue(double Blue_);

    RGB operator +(RGB a);
    RGB operator -(RGB a);
    RGB operator *(RGB a);
    RGB operator /(RGB a);

        
    RGB operator +(double num);
    RGB operator -(double num);
    RGB operator *(double num);
    RGB operator /(double num);
    // pretty stdout
    friend ostream& operator<<(ostream& os, const RGB p);
};

#endif