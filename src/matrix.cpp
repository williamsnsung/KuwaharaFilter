#include "matrix.h"

const int& Matrix::verify_positive(const int& param)
{
    if (param <= 0)
        throw std::length_error("Matrix constructor: magnitude of matrix <= 0");
    return param;
}

void Matrix::verify_dimensions(const int& a, const int& b)
{
    if (a != b)
        throw std::length_error("Matrix dimension mismatch: dimensions of matrices are incompatible for operation");
}


Matrix::Matrix(int x, int y)
    :m(verify_positive(x * y), 0)
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

// TODO implement the below
Matrix Matrix::eigenvalues()
{
    verify_dimensions(X, Y);
    
}

Matrix& Matrix::operator*=(const Matrix& n)
{
    verify_dimensions(X, n.Y);
    for (int i = 0; i < X * Y; i++)
    {
        m[i] *= n.m[i];
    }
    return *this;
}

Matrix& Matrix::operator*=(const double& n)
{
    for (auto& i : m)
    {
        i *= n;
    }
    return *this;
}


Matrix& Matrix::operator-=(const Matrix& n)
{
    verify_dimensions(X, n.X);
    verify_dimensions(Y, n.Y);
    for (int i = 0; i < X * Y; i++)
    {
        m[i] -= n.m[i];
    }
    return *this;
}
Matrix& Matrix::operator-=(const double& n)
{
    *this += -n;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& n)
{
    verify_dimensions(X, n.X);
    verify_dimensions(Y, n.Y);
    for (int i = 0; i < X * Y; i++)
    {
        m[i] += n.m[i];
    }
    return *this;
}

Matrix& Matrix::operator+=(const double& n)
{
    for (auto& i : m)
    {
        i += n;
    }
    return *this;
}

// TODO implement the below
Matrix operator*(const Matrix& lhs, const Matrix& rhs)
Matrix operator*(const double& lhs, const Matrix& rhs)
Matrix operator*(const Matrix& lhs, const double& rhs)

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
Matrix operator-(const double& lhs, const Matrix& rhs)
Matrix operator-(const Matrix& lhs, const double& rhs)

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
Matrix operator+(const double& lhs, const Matrix& rhs)
Matrix operator+(const Matrix& lhs, const double& rhs)
