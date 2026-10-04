#include <cmath>
#include <bits/stdc++.h>

// Transpose
// dot product
// shape checkling
// abbreviation for the division of the matrrix or multiplicarion
// log exponentiation
// sigmoid
// summation functions
// initializers

// addition ke ops
// -> 1> mat + mat
// -> 2> mat+num

// multiplication operations
// -> mat to mat
// ->scaler to matrix

// divisions
// ->mat to sclaer division

template <typename T, int R, int C>
void transpose(const T mat[R][C], T out[C][R])
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            out[j][i] = mat[i][j];
}
#define ll long long
template <typename D, int M, int N, int X>
void dot(const D mat1[M][N], const D mat2[N][X], D out[M][X])
{
    for (int sm = 0; sm < M; sm++)
    {
        for (int i = 0; i < X; i++)
        {
            ll sum = 0;
            for (int itr = 0; itr < N; itr++)
                sum += (mat1[sm][itr] * mat2[itr][i]);

            out[sm][i] = sum;
        }
    }
}

class Matrix
{
public:
    // constructors
};