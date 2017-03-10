#include "matrix.h"
#include "iomanip"

using std::cout;
using std::endl;

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    os<<"    0  1  2  3  4  5  6  7  8  9"<<endl;
    os<<" |------------------------------"<<endl;
    for (int r=0; r<m.row_size(); ++r)
    {
        os<<r << "| ";
        for (int c=0; c<m.col_size(); ++c)
        {
            os<<std::setw(2)<< int(m.get(Pos(r, c)).val);
            os<<" ";
        }
        os<<endl;
    }
    os<<endl;
    return os;
}
