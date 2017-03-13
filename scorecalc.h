#ifndef SCORECALC_H
#define SCORECALC_H
#include <list>
#include <tuple>
#include <iostream>
#include "pos.h"
#include "matrix.h"

class ScoreCalc
{
    friend std::ostream& operator<<(std::ostream& os, const ScoreCalc& sc);
    typedef std::list<std::tuple<Pos, Matrix::value_type, int>> ClickList;
public:
    void put(Pos p, Matrix::value_type v, int n);
    int getScore() const;
    int getLeft() const;
private:
    ClickList lst;
};

std::ostream& operator<<(std::ostream& os, const ScoreCalc& sc);
inline bool operator<(const ScoreCalc& s1, const ScoreCalc& s2)
{
    return s1.getScore() < s2.getScore();
}

#endif // SCORECALC_H
