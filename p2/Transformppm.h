#ifndef Transformppm_HPP
#define Transformppm_HPP

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Transformppm{
private:
    float mat[4][4];

public:
   void savingFile(string PPMfile);
};

#endif