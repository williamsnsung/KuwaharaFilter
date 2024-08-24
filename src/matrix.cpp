#include "matrix.h"

Matrix::Matrix(int x, int y)
    :m(x * y, 0)
    ,X(x)
    ,Y(y)

Matrix::Matrix(Matrix mtx)
    :m(mtx.m)
    ,X(mtx.X)
    ,Y(mtx.Y)

double& Matrix::loc(int i, int j)
{
    return m[i * Y + j];
}

Image Matrix::eigenvalues();
Matrix::Matrix operator*=(Matrix n)
inline Matrix operator*(Matrix n)
Matrix::Matrix operator*=(double n)
inline Matrix operator*(double n)

Matrix::Matrix operator/=(matrix n)
inline Matrix operator/(matrix n)
Matrix::Matrix operator/=(double n)
inline Matrix operator/(double n)

Matrix::Matrix operator-=(Matrix n)
inline Matrix operator-(Matrix n)
Matrix::Matrix operator-=(double n)
inline Matrix operator-(double n)

Matrix::Matrix operator+=(Matrix n)
inline Matrix operator+(Matrix n)
Matrix::Matrix operator+=(double n)
{
    
}
inline Matrix operator+(double n)
