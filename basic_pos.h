#ifndef BASIC_POS_H
#define BASIC_POS_H

template<class T>
class Basic_Pos
{
public:
    typedef T value_type;
public:
    Basic_Pos() = default;
    Basic_Pos(value_type r, value_type c):row(r), col(c) {}
    value_type row;
    value_type col;
};

#endif // BASIC_POS_H
