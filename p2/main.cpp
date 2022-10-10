#include "Transformppm.h"
#include "RGB.h"

using namespace std;
int main(){
    ifstream in;
    Transformppm prueba;
    prueba.readingFile("fichpequeño.ppm");

    prueba.savingFile("prueba.txt");
}