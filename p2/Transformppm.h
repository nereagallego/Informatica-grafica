#ifndef TRANSFORMPPM_HPP
#define TRANSFORMPPM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
#include "RGB.h"

using namespace std;

class Transformppm{
private:
    string _format, _max, _comment, _sizeResolution, _colorResolution; 
    vector<RGB> _imagenHDR;
    int _colorResolutionNumber;
    float _MAX;
public:

    /**
     * @brief Construct a new Transformppm object
     * Constructor vacío 
     * 
     */
    Transformppm();

    /**
     * @brief Construct a new Transformppm object
     * 
     * @param ImagenHDR_ vector con la imagen a construir
     */
    Transformppm(vector<RGB> ImagenHDR_);

    /**
     * @brief Construct a new Transformppm object
     * 
     * @param format formato de la imagen
     * @param max cadena con el valor máximo
     * @param comment comentario (puede no estar "")
     * @param sizeResolution 
     * @param colorResolution 
     * @param c valor de color resolution
     * @param m valor de max
     */
    Transformppm(string format, string max, string comment, string sizeResolution, string colorResolution, int c, int m);

    string getFormat();
    string getComment();
    string getSizeResolution();
    int getColorResolution();
    float getMax();

    vector<RGB> getImagen();
    void setImagen(vector<RGB> Imagen);

    /**
     * @brief Lee el contenido del fichero de nombre PPMfile y guarda su 
     * contenido en memoria
     * 
     * @param PPMfile 
     */
    void readingFile(string PPMfile);

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
    friend ostream& operator<<(ostream& os, const Transformppm& t);

    
};

// Dice si dos ficheros contienen en mismo contenido
void diff(string file1, string file2);

#endif