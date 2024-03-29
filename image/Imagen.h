#ifndef TRANSFORMPPM_HPP
#define TRANSFORMPPM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "../color/RGB.h"

using namespace std;

class Imagen{
private:
    string _format, _comment; 
    int _height, _width;
    int _colorResolution;
    float _MAX;
public:
    // content of pixels
    vector<vector<RGB>> _imagenHDR;
    /**
     * @brief Construct a new Imagen object
     * Constructor vacío 
     * 
     */
    Imagen();

    /**
     * @brief Construct a new Imagen object
     * 
     * @param ImagenHDR_ vector con la imagen a construir
     */
    Imagen(vector<vector<RGB>> ImagenHDR_);

    /**
     * @brief Construct a new Imagen object
     * 
     * @param h height
     * @param w width
     * @param c color resolution
     * @param m max value
     */
    Imagen(int h, int w, int c, int m): _imagenHDR(h, vector<RGB>(w)), _colorResolution(c), _MAX(m), _format("P3"), _height(h), _width(w){}

    /**
     * @brief Construct a new Imagen object
     * 
     * @param h height
     * @param w width
     * @param c colomment
     * @param m max value
     */
    Imagen(int h, int w, string c, int m): _imagenHDR(h, vector<RGB>(w)), _colorResolution(m), _MAX(m), _format("P3"), _comment(c), _height(h), _width(w) {}
    
    /**
     * @brief Construct a new Imagen object
     * 
     * @param h height
     * @param w width
     * @param c color resolution
     * @param com comment of the image
     * @param m max value
     */
    Imagen(int h, int w, int c, string com, int m): _imagenHDR(h, vector<RGB>(w)), _colorResolution(c), _MAX(m), _format("P3"), _comment(com), _height(h), _width(w) {}

    /**
     * @brief Construct a new Imagen object
     * 
     * @param h height
     * @param w width
     * @param c color resolution
     * @param com comment of the image
     * @param m max value
     * @param data pixels of image
     */
    Imagen(int h, int w, int c, string com, int m, vector<vector<RGB>> data): _imagenHDR(data), _colorResolution(c), _MAX(m), _format("P3"), _comment(com), _height(h), _width(w) {}

    /**
     * @brief Construct a new Imagen object
     * 
     * @param h height
     * @param w width
     * @param m max value
     */
    Imagen(int h, int w, int m): _imagenHDR(h, vector<RGB>(w)), _colorResolution(m), _MAX(m), _format("P3"), _height(h), _width(w) {}

    

    string getFormat();
    string getComment();
    int getWidth();
    int getHeight();
    int getColorResolution();
    float getMax();
    void setMax(float v);
    void setColorResolution(float v);

    vector<vector<RGB>> getImagen();
    void setImagen(vector<vector<RGB>> Imagen);

    /**
     * @brief Read a image from a file
     * 
     * @param PPMfile fichero del que se va a leer la imagen
     * @return Imagen 
     */
    Imagen readingFile(string PPMfile);

    /**
     * @brief Guarda en el fichero fichero el contenido que hay en memoria 
     * sobre cierta imagen
     * 
     * @param fichero 
     */
    void savingFile(string fichero);

    /**
     * @brief Guarda en el fichero fichero el contenido que hay en memoria
     * sobre cierta imagen
     * Deja el contenido de la imagen con valores máximos de 255
     * 
     * @param fichero 
     */
    void exportFile(string fichero);
    
    // pretty stdout
    friend ostream& operator<<(ostream& os, const Imagen& t);

    
};

// Dice si dos ficheros contienen en mismo contenido
void diff(string file1, string file2);

#endif