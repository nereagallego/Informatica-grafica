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

ostream& operator<<(ostream& os, const Matrix4& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            os << mat.mat[i][j] << " ";
        }
        os << mat.mat[i][3] << endl;
    }
    return os;
}