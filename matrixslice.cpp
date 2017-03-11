#include "matrixslice.h"
using namespace std;

MatrixSlice::MatrixSlice(const Matrix &m)
{
    slice(m);
}

bool MatrixSlice::isOver() const
{
    return groupVec.empty();
}

bool MatrixSlice::isFlagged(Pos p) const
{
    return slicematrix.get(p) != FlagVal::Unflaged;
}

bool MatrixSlice::canClick(Pos p) const
{
    if (!slicematrix.isInMatrix(p))
        return false;

    int group = slicematrix.get(p);
    return group > FlagVal::Alone;
}

Group MatrixSlice::getGroup(Pos p) const
{
    assert(slicematrix.isInMatrix(p));
    int group = slicematrix.get(p);
    return groupVec[group-FlagVal::Alone-1];
}

void MatrixSlice::slice(const Matrix &m)
{
    unFlagAll();
    int groupNum = FlagVal::Alone + 1;
    for (int r=0; r<m.row_size(); ++r)
    {
        for (int c=0; c<m.col_size(); ++c)
        {
            Pos p(r, c);
            if (isFlagged(p))
                continue;

            if (m.get(p).val == FlagVal::Blank)
            {
                slicematrix.set(p, FlagVal::Blank);
            }
            else
            {
                 Group s;
                 seedPos(m, p, &s, m.get(p), groupNum);
                 if (s.size() == 1)
                 {
                     assert (s.front() == p);
                     setAloneGroup(p);
                 }
                 else
                 {
                     assert(s.size() >= 2 );
                     groupVec.push_back(s);
                     ++groupNum;
                 }
            }
        }
    }
}

void MatrixSlice::seedPos(const Matrix &m, Pos p, Group *ps, Matrix::value_type v, int group)
{
    if (m.isInMatrix(p) && !isFlagged(p) && m.get(p).val == v.val)
    {
        slicematrix.set(p, group);
        ps->push_back(p);
        seedPos(m, Pos(p.row, p.col-1), ps, v, group);
        seedPos(m, Pos(p.row, p.col+1), ps, v, group);
        seedPos(m, Pos(p.row-1, p.col), ps, v, group);
        seedPos(m, Pos(p.row+1, p.col), ps, v, group);
    }
}
