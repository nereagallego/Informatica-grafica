#include "Transformppm.h"
#include <cstring>

void Transformppm::savingFile(string PPMfile){
    ifstream indata;
    indata.open(PPMfile);
    if(!indata) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
    vector<int> ImagenHDR; // guardamos la imagen en HDR
    string line,max, _,resolution,colorRes;

    getline(indata,line);
    getline(indata,max);
    getline(indata,_);
    getline(indata,resolution);
    getline(indata,colorRes);

    int c = stoi(colorRes);
    string delimiter = "=";
    string token = max.substr( max.find(delimiter) + 1, max.length()); // token is "scott"
    

    
    int MAX = stoi(token);
    cout << "Pasa de aqui " << endl;
    string chan;
    int num = 0;
    while(num < 7){
        indata >> chan;
        int aux = stoi(chan);
       cout << "Los valores son: " << aux << " " << MAX << " " << c << endl;
       cout << "Se va a guardar " <<aux/(MAX/c) << endl; 
        ImagenHDR.push_back(aux/(MAX/c));
        num++;
    }

    cout << "Elementos procesados " << num << endl;
    cout << "Primer elemento " << ImagenHDR.front();



}