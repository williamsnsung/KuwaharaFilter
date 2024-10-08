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

// TODO range check
// https://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func
// Last accessed [2024-08-31]
const double& Matrix::loc(int i, int j) const
{
    return m[i * Y + j];
}

double& Matrix::loc(int i, int j)
{
    return const_cast<double &>(static_cast<const Matrix &>(*this).loc(i,j));
}

Matrix& Matrix::operator*=(const Matrix& n)
{
    verify_dimensions(Y, n.X);
    Matrix res(X, n.Y);
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < n.Y; j++)
        {
            for (int k = 0; k < Y; k++)
            {
                res.loc(i,j) += this->loc(i,k) * n.loc(k,j);
            }
        }
    }
    std::swap(res.X, X);
    std::swap(res.Y, Y);
    std::swap(res.m, m);
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
    for (auto& i : m)
    {
        i -= n;
    }
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

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    Matrix res = lhs;
    res *= rhs;
    return res;
}

Matrix operator*(const double& lhs, const Matrix& rhs)
{
    Matrix res = rhs;
    res *= lhs;
    return res;
}

Matrix operator*(const Matrix& lhs, const double& rhs)
{
    Matrix res = lhs;
    res *= rhs;
    return res;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
    Matrix res = lhs;
    res -= rhs;
    return res;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    Matrix res = lhs;
    res += rhs;
    return res;
}

std::ostream& operator<<(std::ostream& os, const Matrix& n)
{
    std::string res = "";
    for (int i = 0; i < n.X; i++)
    {
        for (int j = 0; j < n.Y; j++)
        {
            res += std::to_string(n.loc(i,j)) + "\t";
        }
        res += "\n";
    }
    return os << res;
}
