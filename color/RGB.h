#ifndef RGB_HPP
#define RGB_HPP

#include <iostream>
#include <stdlib.h>

using namespace std;

//Esta clase RGB guarda los valores como 0 o 1 ya que se utiliza para pasar de HDR a memoria
class RGB{
    private:
    float Red;
    float Green;
    float Blue;

    public:
    /**
     * @brief Construct a new RGB object
     * 
     * @param red_ value of the red pixel
     * @param green_ value of the green pixel
     * @param blue_ value of the blue pixel
     */
    RGB(float red_ ,float green_, float blue_);

    /**
     * @brief Construct a new RGB object
     * Constructor vacío
     * 
     */
    RGB(): Red(0), Green(0), Blue(0){};

    float getRed();
    float getGreen();
    float getBlue();

    void setRed(float Red_);
    void setGreen(float Green_);
    void setBlue(float Blue_);

    RGB operator +(RGB a);

    RGB operator /(float num);
    RGB operator *(RGB a);
    RGB operator *(float num);
    RGB operator -(RGB a);
    // pretty stdout
    friend ostream& operator<<(ostream& os, const RGB p);
};

#endif