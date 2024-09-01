#include "matrix.h"
#include <iostream>
int main()
{
    Matrix a(2,2);
    a.loc(0,0) = 1;
    a.loc(0,1) = 1;
    a.loc(1,0) = 1;
    a.loc(1,1) = 1;
    Matrix b(2,3);
    Matrix c(3,2);
    std::cout << a;
    return 0;
}
