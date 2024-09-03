#include "matrix.h"
#include <iostream>
int main()
{
    Matrix a(2,2);
    a.loc(0,0) = 1;
    a.loc(0,1) = 2;
    a.loc(1,0) = 3;
    a.loc(1,1) = 4;

    Matrix b(1,3);
    b.loc(0,0) = 1;
    b.loc(0,1) = 2;
    b.loc(0,2) = 3;

    Matrix c(3,1);
    c.loc(0,0) = 4;
    c.loc(1,0) = 5;
    c.loc(2,0) = 6;

    Matrix d(2,2);
    d.loc(0,0) = 2;
    d.loc(0,1) = 0;
    d.loc(1,0) = 1;
    d.loc(1,1) = 2;

    std::cout << b << "\n";
    std::cout << 2 << "\n";
    std::cout << b * 2;
    return 0;
}
