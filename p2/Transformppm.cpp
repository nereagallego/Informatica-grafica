#include "Transformppm.h"
#include "RGB.h"

Transformppm::Transformppm(){
    _format = "";
    _max = "";
    _comment = "";
    _sizeResolution = "";
    _colorResolution = "";
}

void Transformppm::readingFile(string PPMfile){
    ifstream indata;
    indata.open(PPMfile);
    if(!indata) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
//  vector<RGB> ImagenHDR; // guardamos la imagen en HDR

    getline(indata,_format);
    getline(indata,_max);
    getline(indata,_comment);
    getline(indata,_sizeResolution);
    getline(indata,_colorResolution);

    float c = stoi(_colorResolution);
    string delimiter = "=";
    string token = _max.substr( _max.find(delimiter) + 1, _max.length()); // token is "scott"
    

    float MAX = stoi(token);
    cout << "Pasa de aqui " << endl;
    string red,green,blue;
    float num = 0;
    while(!indata.eof()){
        indata >> red;
        indata >> green;
        indata >> blue;
        RGB tuple((stof(red)*MAX)/c,(stof(green)*MAX)/c,(stof(blue)*MAX)/c);
        //Hay que hacer la conversion de cada canal de cada pixel
        // get.red()...
      
        _imagenHDR.push_back(tuple);
        num++;
    }

    cout << "Elementos procesados " << num << endl;
    cout << "Primer elemento " << _imagenHDR.front().getRed();

}


void Transformppm::savingFile(string fichero){
    ofstream ofdata;
    ofdata.open(fichero);
    ofdata << _format << endl;
    ofdata << _max << endl;
    ofdata << _comment << endl;
    ofdata << _sizeResolution << endl;
    ofdata << _colorResolution << endl;


    float c = stoi(_colorResolution);
    string delimiter = "=";
    string token = _max.substr( _max.find(delimiter) + 1, _max.length()); // token is "scott"
    float MAX = stoi(token);
    int col=1;
    for(RGB aux: _imagenHDR){
        ofdata << (aux.getRed()*c)/MAX << " " << (aux.getGreen()*c)/MAX << " "<< (aux.getBlue()*c)/MAX << "\t";
        if(col == 2050){
            ofdata << endl;
            col = 0;
        }
        col++;
    }




}