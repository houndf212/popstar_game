#ifndef MATRIXSLICE_H
#define MATRIXSLICE_H

#include "matrix.h"
#include <iostream>

class MatrixSlice
{
    typedef std::vector<PosVec> GroupContainer;
public:
    MatrixSlice(const Matrix& m);
    // for human click
    bool canClick(Pos p) const;
    PosVec getGroup(Pos p) const;

    bool isOver() const;
    int getMovesCount() const { return groupVec.size(); }
    GroupContainer getAllGroups() const { return groupVec; }
    inline PosVec getGroup(int index) const;
//    void print() const {std::cout << slicematrix <<std::endl;}
private:
    inline void setAloneGroup(Pos p) { slicematrix.set(p, FlagVal::Alone); }
    inline void unFlagAll() { slicematrix.setAll(FlagVal::Unflaged); }
    bool isFlagged(Pos p) const;
    void slice(const Matrix& m);
    void seedPos(const Matrix& m, Pos p, PosVec *ps, Matrix::value_type v, int group);
private:
    GroupContainer groupVec;
    IntMatrix slicematrix;
};

PosVec MatrixSlice::getGroup(int index) const
{
    assert(0<=index && index<int(groupVec.size()));
    return groupVec[index];
}

#endif // MATRIXSLICE_H
