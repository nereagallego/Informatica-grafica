#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <iostream>
#include <vector>

using namespace std;

class Matrix4{
private:
    float _mat[4][4];

    /**
     * @brief devuelve el determinante de la matriz
     * 
     * @return float 
     */
    float det() const;

    /**
     * @brief devuelve la matriz adjunta
     * 
     * @return Matrix4 
     */
    Matrix4 adjunta() const;

    /**
     * @brief devuelve la matriz tanspuesta
     * 
     * @return Matrix4 
     */
    Matrix4 transpuesta() const;

public:
    /**
     * @brief Construct a new Matrix 4 object
     * Construye la matriz vacía (todas sus componentes son 0)
     * 
     */
    Matrix4(): _mat{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}} {}

    /**
     * @brief Construct a new Matrix 4 object
     * Construye la matriz a partir de un vector 4x4
     * 
     * @param m 
     */
    Matrix4(float m[4][4]);

    /**
     * @brief devuelve la suma de dos matrices
     * 
     * @param m matriz con la que se va a sumar
     * @return Matrix4 
     */
    Matrix4 operator +(const Matrix4 m) const;

    /**
     * @brief devuelve la resta de dos matrices
     * 
     * @param m matriz con la que se va a restar
     * @return Matrix4 
     */
    Matrix4 operator -(const Matrix4 m) const;

    /**
     * @brief devuelve la multiplicación de dos matrices
     * 
     * @param m matriz por la que se va a multiplicar
     * @return Matrix4 
     */
    Matrix4 operator *(const Matrix4 m) const;

    /**
     * @brief devuelve el resultado de multiplicar una matriz por un escalar
     * 
     * @param a escalar por el que se va a multiplicar
     * @return Matrix4 
     */
    Matrix4 operator *(const float a) const;

    /**
     * @brief devuelve el resultado de multiplicar una matrix 4x4 por una 
     * matriz 4x1
     * 
     * @param v matriz 4x1 por la que se va a multiplicar
     * @return vector<float> 
     */
    vector<float> operator *(const float v[4]);

    /**
     * @brief operador de acceso a la matriz
     * 
     * @param index índice al que se quiere acceder
     * @return float* 
     */
    float* operator[](const int &index) ;

    /**
     * @brief devuelve la matriz inversa
     * 
     * @return Matrix4 
     */
    Matrix4 inversa() const;

    // pretty stdout
    friend ostream& operator<<(ostream& os, const Matrix4& mat);
};

#endif