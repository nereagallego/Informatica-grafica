#include "Transformppm.h"
#include "RGB.h"
#include "ToneMapping.h"

using namespace std;
int main(){
    ifstream in;
    Transformppm prueba;
    prueba.readingFile("fichpequeño.ppm");

    prueba.savingFile("prueba.txt");

    cout << prueba << endl;
    ToneMapping operaciones;
    Transformppm resul;
    resul = operaciones.clampGamma(prueba,2.2,1);

    cout << resul;
   /* resul = operaciones.equalize(prueba.getImagen(),48);
    prueba.setImagen(resul);
    cout << prueba;
    resul = operaciones.clampEqualize(prueba.getImagen(),20);
    prueba.setImagen(resul);
    cout << prueba;
*/
    diff("fichpequeño.ppm", "prueba.txt");
    return 0;
}