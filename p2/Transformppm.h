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
    void readingFile(string PPMfile);
    void savingFile(string fichero);
    vector<RGB> getImagen();
};

void diff(string file1, string file2);

#endif