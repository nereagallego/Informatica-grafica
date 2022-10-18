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

    /**
     * @brief Get the Red object
     * 
     * @return float 
     */
    float getRed();

    /**
     * @brief Get the Green object
     * 
     * @return float 
     */
    float getGreen();
    
    /**
     * @brief Get the Blue object
     * 
     * @return float 
     */
    float getBlue();

    /**
     * @brief Set the Red object
     * 
     * @param Red_ 
     */
    void setRed(float Red_);

    /**
     * @brief Set the Green object
     * 
     * @param Green_ 
     */
    void setGreen(float Green_);

    /**
     * @brief Set the Blue object
     * 
     * @param Blue_ 
     */
    void setBlue(float Blue_);
};

#endif