#ifndef RGB_HPP
#define RGB_HPP

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

    float getRed();
    float getGreen();
    float getBlue();

    void setRed(float Red_);
    void setGreen(float Green_);
    void setBlue(float Blue_);
};

#endif