#include "Imagen.h"

Imagen::Imagen(){
    _format = "P3";
    
    _comment = "";
    
    _colorResolution = 0;
    _MAX = 0.0;
}

Imagen::Imagen(vector<vector<RGB>> ImagenHDR_){
    _format = "P3";
    _comment = "";
    _colorResolution = 0;
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

Imagen Imagen::readingFile(string PPMfile){
    ifstream indata;
    indata.open(PPMfile);
    if(!indata) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
   }
    string max;
    string comment;
    string sizeResolution, h1, w1;
    string colorResolution;
    getline(indata,_format);
    getline(indata,max);
    getline(indata,comment);
    if(comment[0] != '#'){
        sizeResolution = comment;
        getline(indata,colorResolution);
        comment = "";
    } else {
        getline(indata,sizeResolution);
        getline(indata,colorResolution);
    }
    string space_delimiter = " ";
    size_t pos = 0;
    pos = sizeResolution.find(space_delimiter);
    w1 = sizeResolution.substr(0, pos);
    sizeResolution.erase(0, pos + space_delimiter.length());
    _width = stoi(w1);
    _height = stoi(sizeResolution);
    vector<vector<RGB>> _imagenHDR2(_height,vector<RGB>(_width));
    _colorResolution = stoi(colorResolution);
    string delimiter = "=";
    string token = max.substr( max.find(delimiter) + 1, max.length());  
    _MAX = stoi(token);
    string red,green,blue;
    float num = 0;
    for (int i = 0; i < _height; i ++){
        for(int j = 0; j < _width; j ++){
            indata >> red >> green >> blue;
            RGB tuple((stof(red)*_MAX)/(_colorResolution),(stof(green)*_MAX)/(_colorResolution),(stof(blue)*_MAX)/(_colorResolution));
            _imagenHDR2[i][j] = tuple;
        }   
    }
    Imagen img(_height,_width,_colorResolution, comment,_MAX,_imagenHDR2);

    indata.close();
    return img;
}


void Imagen::savingFile(string fichero){
    ofstream ofdata;
    ofdata.open(fichero);
    ofdata << _format << endl;
    ofdata << "#MAX="+to_string((int)_MAX) << endl;
    if(_comment!="")
    ofdata << _comment << endl;
    ofdata << to_string(_width) + " " + to_string(_height) << endl;
    ofdata << _colorResolution << endl;

    for(int i = 0; i < _height; i ++){
        for(int j = 0; j < _width; j ++){
            RGB pixel = _imagenHDR[i][j];
            ofdata << fixed << setprecision(0) <<  pixel.getRed()*(_colorResolution/_MAX) << " " << pixel.getGreen()*(_colorResolution/_MAX) << " "<< pixel.getBlue()*(_colorResolution/_MAX) << "     ";
        } 
        ofdata << endl ;          
    }
    ofdata << endl ;
    ofdata.close();
}

vector<vector<RGB>> Imagen::getImagen(){
    return _imagenHDR;
}


void Imagen::setImagen(vector<vector<RGB>> Imagen){
   _imagenHDR = Imagen;
}

string Imagen::getFormat(){
   return _format;
}

string Imagen::getComment(){
    return _comment;
}


float Imagen::getMax(){
   return _MAX;
}

int Imagen::getColorResolution(){
    return _colorResolution;
}

int Imagen::getHeight(){
    return _height;
}

int Imagen::getWidth(){
    return _width;
}


void Imagen::exportFile(string fichero){
    _colorResolution = 255;
    ofstream ofdata;
    ofdata.open(fichero);
    ofdata << _format << endl;
    ofdata << "#MAX="+to_string(_MAX) << endl;
    ofdata << _comment << endl;
    ofdata << to_string(_width) + " " +to_string(_height) << endl;
    ofdata << _colorResolution << endl;

    for(int i = 0; i < _height; i ++){
        for(int j = 0; j < _width; j ++){
            RGB pixel = _imagenHDR[i][j];

            RGB f(pixel.getRed()*255*(_colorResolution/(_MAX*_colorResolution)), pixel.getGreen()*255*(_colorResolution/(_MAX*_colorResolution)), pixel.getBlue()*255*(_colorResolution/(_MAX*_colorResolution)) );
            ofdata << fixed << setprecision(0) <<  pixel.getRed()*255*(_colorResolution/_MAX) << " " << pixel.getGreen()*255*(_colorResolution/_MAX) << " "<< pixel.getBlue()*255*(_colorResolution/_MAX) << "     ";

        } 
        ofdata << endl ; 
    }

    ofdata << endl ;
    ofdata.close();
}

void Imagen::setMax(float v){
    _MAX = v;
}

void Imagen::setColorResolution(float v){
    _colorResolution = v;
}