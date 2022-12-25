#include "CImg.h"
#include <iostream>


using namespace std;

int main(){
    cimg_library::CImg<float> src("../resources/rock_wall.jpg");
    int width = src.width();
    int height = src.height();

    cout << "La altura es " << height << " y la anchura " << width << endl;
}