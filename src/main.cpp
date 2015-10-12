#include <iostream>

#include "matrix.h"


int main() {
    myLib::Matrix<int> m(10,10);
    myLib::Matrix<int> m1(10);
    m[2][1] = 1;
    m.print();
    return 0;
}