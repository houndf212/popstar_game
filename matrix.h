#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include "basic_matrix.h"
#include "flagval.h"

constexpr int ROW_SIZE = 10;
constexpr int COL_SIZE = 10;

typedef Basic_Matrix<int, ROW_SIZE, COL_SIZE> IntMatrix;
typedef Basic_Matrix<FlagVal, ROW_SIZE, COL_SIZE> Matrix;

std::ostream& operator<<(std::ostream& os, const Matrix& m);

#endif // MATRIX_H
