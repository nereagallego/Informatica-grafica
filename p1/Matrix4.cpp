#include "Matrix4.h"

Matrix4::Matrix4(float m[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            mat[i][j] = m[i][j];
        }
    }
}

Matrix4 Matrix4::operator+(const Matrix4 m) const{
    Matrix4 result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            result.mat[i][j] = mat[i][j] + m.mat[i][j];
        }
    }

    return result;
}

Matrix4 Matrix4::operator-(const Matrix4 m) const {
    Matrix4 result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            result.mat[i][j] = mat[i][j] - m.mat[i][j];
        }
    }

    return result;
}

Matrix4 Matrix4::operator*(const Matrix4 m) const{
    Matrix4 result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k ++)
                result.mat[i][j] += mat[i][k] * m.mat[k][j];
        }
    }

    return result;
}

vector<float> Matrix4::operator*(const float v[4]) {
    vector<float> result(4);
    for(int i = 0; i < 4; i ++){
        result[i] = 0;
        for(int j = 0; j < 4; j ++){
            result[i] += mat[i][j]*v[j]; 
        }
    }
    return result;
}

ostream& operator<<(ostream& os, const Matrix4& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            os << mat.mat[i][j] << " ";
        }
        os << mat.mat[i][3] << endl;
    }
    return os;
}

float* Matrix4::operator [](const int &index)  // overloading operator []
{
  return  mat[index];
}

Matrix4 Matrix4::inversa() const{

}

float Matrix4::det() const {

    return mat[0][0] * (mat[1][1] * mat[2][2] * mat[3][3] +  
                        mat[2][1] * mat[3][2] * mat[1][3] +  
                        mat[1][2] * mat[2][3] * mat[3][1] - 
                        mat[1][3] * mat[2][2] * mat[3][1] - 
                        mat[2][1] * mat[1][2] * mat[3][3] - 
                        mat[3][2] * mat[2][3] * mat[1][1]) 
         - mat[1][0] * (mat[0][1] * mat[2][2] * mat[3][3] + 
                        mat[2][1] * mat[3][2] * mat[0][3] + 
                        mat[0][2] * mat[2][3] * mat[3][1] - 
                        mat[0][3] * mat[2][2] * mat[3][1] - 
                        mat[2][1] * mat[0][2] * mat[3][3] - 
                        mat[3][2] * mat[2][3] * mat[0][1]) 
         + mat[2][0] * (mat[0][1] * mat[1][2] * mat[3][3] + 
                        mat[1][1] * mat[3][2] * mat[0][3] + 
                        mat[0][2] * mat[1][3] * mat[3][1] - 
                        mat[0][3] * mat[1][2] * mat[3][1] - 
                        mat[1][1] * mat[0][2] * mat[3][3] - 
                        mat[3][2] * mat[1][3] * mat[0][1]) 
         - mat[3][0] * (mat[0][1] * mat[1][2] * mat[2][3] + 
                        mat[1][1] * mat[2][2] * mat[0][3] +
                        mat[0][2] * mat[1][3] * mat[2][1] - 
                        mat[0][3] * mat[1][2] * mat[2][1] -
                        mat[1][1] * mat[0][2] * mat[2][3] - 
                        mat[2][2] * mat[1][3] * mat[0][1]);
}

Matrix4 Matrix4::adjunta() const{
    Matrix4 result;
    result[0][0] = mat[1][1] * mat[2][2] * mat[3][3] +  
                        mat[2][1] * mat[3][2] * mat[1][3] +  
                        mat[1][2] * mat[2][3] * mat[3][1] - 
                        mat[1][3] * mat[2][2] * mat[3][1] - 
                        mat[2][1] * mat[1][2] * mat[3][3] - 
                        mat[3][2] * mat[2][3] * mat[1][1];
    result[1][0] = -(mat[0][1] * mat[2][2] * mat[3][3] + 
                        mat[2][1] * mat[3][2] * mat[0][3] + 
                        mat[0][2] * mat[2][3] * mat[3][1] - 
                        mat[0][3] * mat[2][2] * mat[3][1] - 
                        mat[2][1] * mat[0][2] * mat[3][3] - 
                        mat[3][2] * mat[2][3] * mat[0][1]);
    result[2][0] = mat[0][1] * mat[1][2] * mat[3][3] + 
                        mat[1][1] * mat[3][2] * mat[0][3] + 
                        mat[0][2] * mat[1][3] * mat[3][1] - 
                        mat[0][3] * mat[1][2] * mat[3][1] - 
                        mat[1][1] * mat[0][2] * mat[3][3] - 
                        mat[3][2] * mat[1][3] * mat[0][1];
    result[3][0] = -(mat[0][1] * mat[1][2] * mat[2][3] + 
                        mat[1][1] * mat[2][2] * mat[0][3] +
                        mat[0][2] * mat[1][3] * mat[2][1] - 
                        mat[0][3] * mat[1][2] * mat[2][1] -
                        mat[1][1] * mat[0][2] * mat[2][3] - 
                        mat[2][2] * mat[1][3] * mat[0][1]);

    result[0][1] = -(mat[1][0] * mat[2][2] * mat[3][3] + 
                        mat[2][0] * mat[3][2] * mat[1][3] + 
                        mat[1][2] * mat[2][3] * mat[3][0] - 
                        mat[1][3] * mat[2][2] * mat[3][0] - 
                        mat[2][0] * mat[1][2] * mat[3][3] - 
                        mat[2][3] * mat[3][2] * mat[1][0]);
    result[1][1] = mat[0][0] * mat[2][2] * mat[3][3] + 
                        mat[2][0] * mat[3][2] * mat[0][3] + 
                        mat[0][2] * mat[2][3] * mat[3][0] - 
                        mat[0][3] * mat[2][2] * mat[3][0] - 
                        mat[2][0] * mat[0][2] * mat[3][3] - 
                        mat[2][3] * mat[3][2] * mat[0][0];
    result[2][1] = mat[0][0] * mat[1][2] * mat[3][3] + 
                        mat[1][0] * mat[3][2] * mat[0][3] + 
                        mat[0][2] * mat[1][3] * mat[3][0] - 
                        mat[0][3] * mat[1][2] * mat[3][0] - 
                        mat[1][0] * mat[0][2] * mat[3][3] - 
                        mat[1][3] * mat[3][2] * mat[0][0];
    result[3][1] = mat[0][0] * mat[1][2] * mat[2][3] + 
                        mat[1][0] * mat[2][2] * mat[0][3] + 
                        mat[0][2] * mat[1][3] * mat[2][0] - 
                        mat[0][3] * mat[1][2] * mat[2][0] - 
                        mat[1][0] * mat[0][2] * mat[2][3] - 
                        mat[1][3] * mat[2][2] * mat[0][0];
    
}





//  a00 a01 a02 a03
//  a10 a11 a12 a13
//  a20 a21 a22 a23
//  a30 a31 a32 a33


//  a00 a02 a03
//  a20 a22 a23
//  a30 a32 a33