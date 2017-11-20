#ifndef POS_H
#define POS_H
#include <iostream>
#include <vector>
#include "basic_pos.h"

typedef Basic_Pos<int> Pos;
typedef std::vector<Pos> PosVec;

bool operator==(const Pos& p1, const Pos& p2);
inline bool operator!=(const Pos& p1, const Pos& p2) { return !(p1==p2); }
bool operator<(const Pos& p1, const Pos& p2);

std::ostream &operator<<(std::ostream& os, const Pos& p);
std::istream &operator>>(std::istream& in, Pos& p);
#endif // POS_H
