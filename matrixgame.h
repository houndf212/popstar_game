#ifndef MATRIXGAME_H
#define MATRIXGAME_H
#include "matrix.h"

class MatrixGame
{
public:
    static int removePosSet(Matrix& m, const Group& s);
private:
    static void removePos(Matrix& m, Pos p);
    static void moveEmptyCol(Matrix& m);
    static void moveCol(Matrix& m, int col1, int col2);
    static bool isEmptyCol(const Matrix& m, int col);
};

#endif // MATRIXGAME_H
