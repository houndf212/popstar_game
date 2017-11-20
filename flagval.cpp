#include "flagval.h"


FlagVal::FlagVal(int i, Pos p)
    :val(i)
    ,original_pos(p)
{

}

const FlagVal Flag_Blank(FlagVal::Blank, Pos(-1, -1));
//extern const FlagVal Flag_Alone(FlagVal::Alone, Pos(-1, -1));
//extern const FlagVal Flag_Unflaged(FlagVal::Unflaged, Pos(-1, -1));
