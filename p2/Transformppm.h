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
    Transformppm();
    Transformppm(vector<RGB> ImagenHDR_);
    Transformppm(string format, string max, string comment, string sizeResolution, string colorResolution, int c, int m);
    string getFormat();
    string getComment();
    string getSizeResolution();
    
    
    int getColorResolution();
    float getMax();
    void readingFile(string PPMfile);
    void savingFile(string fichero);
    vector<RGB> getImagen();
    void setImagen(vector<RGB> Imagen);
    // pretty stdout
    friend ostream& operator<<(ostream& os, const Transformppm& t);

    
};

void diff(string file1, string file2);

#endif