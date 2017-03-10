#include "pos.h"

bool operator==(const Pos &p1, const Pos &p2)
{
    return p1.row == p2.row && p1.col == p2.col;
}

bool operator<(const Pos &p1, const Pos &p2)
{
    return p1.row < p2.row || (p1.row == p2.row && p1.col < p2.col);
}

std::ostream &operator <<(std::ostream &os, const Pos &p)
{
    return os <<"("<<int(p.row)<<","<<int(p.col) <<")";
}

std::istream &operator>>(std::istream &in, Pos &p)
{
    return in>>p.row>>p.col;
}
