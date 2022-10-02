#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <iostream>
#include <vector>

using namespace std;

class Matrix4{
private:
    float mat[4][4];

    float det() const;
    Matrix4 adjunta() const;
    Matrix4 transpuesta() const;

public:
    Matrix4(): mat{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}} {}
    Matrix4(float m[4][4]);

    Matrix4 operator +(const Matrix4 m) const;

    Matrix4 operator -(const Matrix4 m) const;

    Matrix4 operator *(const Matrix4 m) const;
    vector<float> operator *(const float v[4]);
    float* operator[](const int &index) ;

    Matrix4 inversa() const;

   //decltype(auto) operator[](unsigned int i) { return mat[i]; }
    //decltype(auto) operator[](unsigned int i) const { return mat[i]; }

    friend ostream& operator<<(ostream& os, const Matrix4& mat);
};

#endif