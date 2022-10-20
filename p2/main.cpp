#include "Transformppm.h"
#include "RGB.h"
#include "ToneMapping.h"

using namespace std;
int main(){
    ifstream in;
    Transformppm prueba;
    ToneMapping operaciones;
    prueba.readingFile("forest_path.ppm");
    Transformppm salida = operaciones.equalize(prueba);
    cout << salida.getMax();
    salida.exportFile("prueba.ppm");

    // cout << prueba << endl;
    
    // Transformppm resul;
    // resul = operaciones.clampGamma(prueba,2.2,1);

    // cout << resul;
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