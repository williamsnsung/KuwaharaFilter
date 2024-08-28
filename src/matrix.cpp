#include "matrix.h"

// TODO add concept to restricit x and y to positive and not both 0
Matrix::Matrix(int x, int y)
    :m(x * y, 0)
    ,X(x)
    ,Y(y)
{
}

Matrix::Matrix(const Matrix& mtx)
    :m(mtx.m)
    ,X(mtx.X)
    ,Y(mtx.Y)
{
}

double& Matrix::loc(int i, int j)
{
    return m[i * Y + j];
}

Matrix Matrix::eigenvalues()
// TODO add concept to make sure that both matrices have correct rows and columns
Matrix& Matrix::operator*=(const Matrix& n)
Matrix& Matrix::operator*=(const double& n)
{
    for (auto& i : m)
    {
        i *= n;
    }
    return *this;
}

// TODO add concept to make sure that both matrices have correct rows and columns
// TODO add concept to prevent division by 0
Matrix& Matrix::operator/=(const Matrix& n)
Matrix& Matrix::operator/=(const double& n)
{
    for (auto& i : m)
    {
        i /= n;
    }
    return *this;
}

// TODO add concept to make sure that both matrices have correct rows and columns
Matrix& Matrix::operator-=(const Matrix& n)
Matrix& Matrix::operator-=(const double& n)
{
    m += -n;
    return *this;
}

// TODO add concept to make sure that both matrices have correct rows and columns
Matrix& Matrix::operator+=(const Matrix& n)
Matrix& Matrix::operator+=(const double& n)
{
    for (auto& i : m)
    {
        i += n;
    }
    return *this;
}
