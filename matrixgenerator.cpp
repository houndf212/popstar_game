#include "matrixgenerator.h"
#include <random>
#include <chrono>

Matrix MatrixGenerator::gen(int n)
{
    using namespace std;
    typedef std::default_random_engine::result_type type_t;
    type_t seed = chrono::system_clock::now().time_since_epoch().count();
    std::uniform_int_distribution<int> dist(1, n);
    std::default_random_engine rng;
    rng.seed(seed);

    Matrix m;
    for (int r=0; r<m.row_size(); ++r)
    {
        for (int c=0; c<m.col_size(); ++c)
        {
            Pos p(r, c);
            m.set(p, FlagVal(dist(rng), p));
        }
    }
    return m;
}

