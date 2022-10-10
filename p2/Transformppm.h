#ifndef TRANSFORMPPM_HPP
#define TRANSFORMPPM_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "RGB.h"

using namespace std;

class Transformppm{
private:
//    float mat[4][4];
    string _format, _max, _comment, _sizeResolution, _colorResolution; 
    vector<RGB> _imagenHDR;
public:
    Transformppm();
    void readingFile(string PPMfile);
    void savingFile(string fichero);
};

#endif