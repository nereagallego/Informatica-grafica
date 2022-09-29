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

 //   return mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3] - mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0] + mat[0][1] * mat[1][2] * mat[2][3]
}