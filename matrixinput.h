#ifndef MATRIXINPUT_H
#define MATRIXINPUT_H
#include "matrix.h"
#include <string>

class MatrixInput
{
public:
    static Matrix fromString(std::string str);
};

#endif // MATRIXINPUT_H
