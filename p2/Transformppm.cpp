#include "Transformppm.h"
#include "RGB.h"

Transformppm::Transformppm(){
    _format = "";
    _max = "";
    _comment = "";
    _sizeResolution = "";
    _colorResolution = "";
    _colorResolutionNumber = 0;
    _MAX = 0.0;
}

Transformppm::Transformppm(vector<RGB> ImagenHDR_){
    _format = "";
    _max = "";
    _comment = "";
    _sizeResolution = "";
    _colorResolution = "";
    _colorResolutionNumber = 0;
    _MAX = 0.0;
    _imagenHDR = ImagenHDR_;

}
void diff(string file1, string file2){
    ifstream f1;
    f1.open(file1);

    ifstream f2;
    f2.open(file2);
    string word1, word2;
    int count = 0;
    do{
        f1 >> word1;
        f2 >> word2;
        count ++;
        if(word1!=word2) cout << "palabara " << word1 << " y " << word2 << " distinta\n";
    } while(!f1.eof() && !f2.eof());
    if(f1.eof() && !f2.eof()){
        cout << file1 << " es más corto" << endl;
        while(f2 >> word2){
            cout << word2 << endl;
        }
    } else if(f2.eof() && ! f1.eof()){
        cout << file2 << " es más corto" << endl;
        while(f1 >> word2){
            cout << word2 << endl;
        }
    }
    f1.close();
    f2.close();
}

void Transformppm::readingFile(string PPMfile){
    ifstream indata;
    indata.open(PPMfile);
    if(!indata) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }

    getline(indata,_format);
    //cout << _format << endl;
    getline(indata,_max);
    //cout << _max << endl;
    getline(indata,_comment);
    //cout << _comment << endl;
    getline(indata,_sizeResolution);
    //cout << _sizeResolution << endl;
    getline(indata,_colorResolution);
    //cout << _colorResolution << endl;

    _colorResolutionNumber = stoi(_colorResolution);
    //cout << _colorResolutionNumber << endl;
    string delimiter = "=";
    string token = _max.substr( _max.find(delimiter) + 1, _max.length()); // token is "scott"
    

    _MAX = stoi(token);
    //cout << _MAX << endl;
    //cout << "Pasa de aqui " << endl;
    string red,green,blue;
    float num = 0;
    while(indata >> red){
        
        if (red=="\n") cout << "jeje" << endl;
        indata >> green;
        indata >> blue;
        //cout << red << " " << green << " " << blue << endl;
        RGB tuple((stof(red)*_MAX)/_colorResolutionNumber,(stof(green)*_MAX)/_colorResolutionNumber,(stof(blue)*_MAX)/_colorResolutionNumber);
        //Hay que hacer la conversion de cada canal de cada pixel
        // get.red()...
        //cout << (stof(red)*_MAX)/_colorResolutionNumber << " " << (stof(green)*_MAX)/_colorResolutionNumber << " " << (stof(blue)*_MAX)/_colorResolutionNumber << endl;
      
        _imagenHDR.push_back(tuple);
        num++;
    }

   // cout << "Elementos procesados " << num << endl;
    //cout << "Primer elemento " << _imagenHDR.front().getRed();
    indata.close();

}


void Transformppm::savingFile(string fichero){
    cout << endl << endl << endl;
    ofstream ofdata;
    ofdata.open(fichero);
    ofdata << _format << endl;
    ofdata << _max << endl;
    ofdata << _comment << endl;
    ofdata << _sizeResolution << endl;
    ofdata << _colorResolution << endl;


    string delimiter = "=";
    string token = _max.substr( _max.find(delimiter) + 1, _max.length()); // token is "scott"
    int col=0;
   // bool first = true;

    for(RGB aux: _imagenHDR){
       // if(first) first = false;
      //  else ofdata << "     ";

        ofdata << fixed << setprecision(0) <<  aux.getRed()*(_colorResolutionNumber/_MAX) << " " << aux.getGreen()*(_colorResolutionNumber/_MAX) << " "<< aux.getBlue()*(_colorResolutionNumber/_MAX) << "     ";
        //cout << aux.getRed() << " " << aux.getGreen() << " " << aux.getBlue() << endl;
        //cout << fixed << setprecision(0) <<  aux.getRed()*(_colorResolutionNumber/_MAX) << " " << aux.getGreen()*(_colorResolutionNumber/_MAX) << " "<< aux.getBlue()*(_colorResolutionNumber/_MAX) << endl;
        // if(col == 2050){
        //     ofdata << endl;
        //     col = 0;
        // }
        //cout << col << endl;

        col++;
        
    }
    ofdata << endl ;
    ofdata.close();




}

vector<RGB> Transformppm::getImagen(){
    return _imagenHDR;
}