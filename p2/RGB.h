#ifndef RGB_HPP
#define RGB_HPP

//Esta clase RGB guarda los valores como 0 o 1 ya que se utiliza para pasar de HDR a memoria
class RGB{
    private:
    float Red;
    float Green;
    float Blue;

    public:
    RGB(float red_ ,float green_, float blue_);

    float getRed();
    float getGreen();
    float getBlue();
};

#endif