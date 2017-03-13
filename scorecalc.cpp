#include "scorecalc.h"
#include "matrix.h"
using namespace std;

void ScoreCalc::put(Pos p, Matrix::value_type v, int n)
{
    assert(n>=2);
    assert(v.val>0);
    lst.push_back(std::make_tuple(p, v, n));
}

int ScoreCalc::getScore() const
{
    int n = Matrix::row_size() * Matrix::col_size();
    int s1 = 0;
    for (auto it=lst.cbegin(); it!=lst.cend(); ++it)
    {
        int s = std::get<2>(*it);
        n -= s;
        s1 += s*s*5;
    }

    if (n<=9)
        s1 += 2000 - n*n*20;

    return s1;
}

int ScoreCalc::getLeft() const
{
    int n = Matrix::row_size() * Matrix::col_size();
    for (auto it=lst.begin(); it!=lst.cend(); ++it)
    {
        int s = std::get<2>(*it);
        n -= s;
    }
    return n;
}

ostream &operator<<(ostream &os, const ScoreCalc &sc)
{
    os << "score: "<<sc.getScore()
       <<", moves: "<<sc.lst.size()
      <<", left: "<<sc.getLeft()
      <<endl;
    int i=0;
    for(auto it=sc.lst.cbegin(); it!=sc.lst.cend(); ++it)
    {
        os << std::get<0>(*it) <<"["<<std::get<1>(*it).val<<","<<std::get<2>(*it)<<"]\t";
        ++i;
        if (i%5 == 0) cout<<endl;
    }
    return os <<endl;
}
