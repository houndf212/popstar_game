#include "matrixgame.h"
#include "matrixslice.h"
#include <vector>

int MatrixGame::removePosSet(Matrix &m, const Group &s)
{
    assert(s.size() >= 2);
    for (auto& p : s)
    { removePos(m, p); }
    moveEmptyCol(m);
    return s.size();
}

void MatrixGame::removePos(Matrix &m, Pos p)
{
    assert(m.isInMatrix(p));
    for (int r=p.row; r>0; --r)
    {
        m.set(Pos(r, p.col), m.get(Pos(r-1, p.col)));
    }
    m.set(Pos(0, p.col), Flag_Blank);
}

void MatrixGame::moveEmptyCol(Matrix &m)
{
    std::vector<int> noEmptyCols;
    for (int col=0; col<m.col_size(); ++col)
    {
        if (!isEmptyCol(m, col))
        {
            noEmptyCols.push_back(col);
        }
    }
    //如果全是空行，或者有值的行已经在左端（所有空行在最右边）
    //减少很多次赋值
    if (noEmptyCols.empty()
            || size_t(noEmptyCols.back()) == noEmptyCols.size()-1)
        return;

    for (int c=0; size_t(c)<noEmptyCols.size(); ++c)
    {
        if (c!=noEmptyCols[c])
        { moveCol(m, c, noEmptyCols[c]); }
    }
}

void MatrixGame::moveCol(Matrix &m, int col1, int col2)
{
    assert(0<=col1 && col1<col2);
    for (int row=0; row<m.row_size(); ++row)
    {
        m.set(Pos(row, col1), m.get(Pos(row, col2)));
        m.set(Pos(row, col2), Flag_Blank);
    }
}

bool MatrixGame::isEmptyCol(const Matrix &m, int col)
{
    for (int row=0; row<m.row_size(); ++row)
    {
        if (m.get(Pos(row, col)).val != Flag_Blank.val)
            return false;
    }
    return true;
}
