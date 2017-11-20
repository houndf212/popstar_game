#ifndef BASIC_MATRIX_H
#define BASIC_MATRIX_H

#include <array>
#include <assert.h>
#include "basic_pos.h"

template<class _T, int _R, int _C>
class Basic_Matrix
{
public:
    typedef _T value_type;
    typedef value_type& ref_type;
public:
    template<class U>
    value_type get(Basic_Pos<U> p) const
    {
        assert(isInMatrix(p));
        return m_matrix[p.row][p.col];
    }

    template<class U>
    void set(Basic_Pos<U> p, value_type v)
    {
        assert(isInMatrix(p));
        m_matrix[p.row][p.col] = v;
    }

    void setAll(value_type v)
    {
        for (auto &vec : m_matrix) {
            vec.fill(v);
        }
    }

    template<class U>
    static bool isInMatrix(Basic_Pos<U> p)
    {
        return 0<=p.row && p.row<row_size() && 0<=p.col && p.col<col_size();
    }
    static constexpr int row_size() { return _R; }
    static constexpr int col_size() { return _C; }
private:
    std::array<std::array<value_type, _C>, _R> m_matrix;
};

#endif // BASIC_MATRIX_H
