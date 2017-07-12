#ifndef FLAGVAL_H
#define FLAGVAL_H
#include "pos.h"

class FlagVal
{
public:
    int val;
    Pos original_pos;
    FlagVal() = default;
    FlagVal(int i, Pos p);
public:
    static constexpr int Blank = 0;
    static constexpr int Alone = 1;
    static constexpr int Unflaged = -1;
};

extern const FlagVal Flag_Blank;
//extern const FlagVal Flag_Alone;
//extern const FlagVal Flag_Unflaged;

//bool operator ==(const FlagVal& f1, const FlagVal& f2)
//{
//    return f1.val == f2.val;
//}

//bool operator !=(const FlagVal& f1, const FlagVal& f2)
//{
//    return !(f1==f2);
//}
#endif // FLAGVAL_H
