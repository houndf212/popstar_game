#include "matrixinput.h"
#include "flagval.h"
#include <map>
using namespace std;

Matrix MatrixInput::fromString(std::string str)
{
    assert(str.size() == Matrix::row_size()*Matrix::col_size());
    int num=0;
    map<char, int> mp;
    for (size_t i=0; i<str.size(); ++i)
    {
        char c = str[i];
        if (mp.find(c) == mp.cend())
        {
            ++num;
            mp[c] = num;
            str[i] = num;
        }
        else
        { str[i] = mp[c]; }
    }
//    assert(num == 5);
    Matrix m;
    for(int row=0; row<m.row_size(); ++row)
        for(int col=0; col<m.col_size(); ++col)
        {
            Pos p(row, col);
            m.set(p, FlagVal(str[row*m.col_size() + col], p));
        }

    return m;
}
