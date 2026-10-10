#ifndef COREMATHS_HPP
#define COREMATHS_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

using mat = vector<vector<double>>;

// ---------------------------------------------------------------------------
// Shape helpers (your "shape checking" TODO)
// ---------------------------------------------------------------------------
inline bool isRectangular(const mat &m)
{
    if (m.empty())
        return true;
    for (const auto &row : m)
        if (row.size() != m[0].size())
            return false;
    return true;
}

inline void requireNonEmpty(const mat &m, const char *fn)
{
    if (m.empty() || m[0].empty() || !isRectangular(m))
        throw invalid_argument(string(fn) + ": matrix is empty or ragged");
}

inline void requireSameShape(const mat &a, const mat &b, const char *fn)
{
    requireNonEmpty(a, fn);
    requireNonEmpty(b, fn);
    if (a.size() != b.size() || a[0].size() != b[0].size())
        throw invalid_argument(string(fn) + ": shape mismatch");
}

// ---------------------------------------------------------------------------
// Transpose (C-array version, as in the original)
// ---------------------------------------------------------------------------
template <typename T, int R, int C>
void transpose(const T (&in)[R][C], T (&out)[C][R])
{
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            out[j][i] = in[i][j];
}

inline mat transposeMat(const mat &m)
{
    requireNonEmpty(m, "transposeMat");
    mat out(m[0].size(), vector<double>(m.size()));
    for (size_t i = 0; i < m.size(); ++i)
        for (size_t j = 0; j < m[0].size(); ++j)
            out[j][i] = m[i][j];
    return out;
}

// ---------------------------------------------------------------------------
// Dot product (C-array version, as in the original)
// ---------------------------------------------------------------------------
template <typename D, int M, int N, int X>
void dot(const D (&a)[M][N], const D (&b)[N][X], D (&out)[M][X])
{
    for (int r = 0; r < M; ++r)
    {
        for (int c = 0; c < X; ++c)
        {
            D sum = 0; // FIX: D, not long long
            for (int k = 0; k < N; ++k)
                sum += a[r][k] * b[k][c];
            out[r][c] = sum;
        }
    }
}

inline mat dotMat(const mat &a, const mat &b)
{
    requireNonEmpty(a, "dotMat");
    requireNonEmpty(b, "dotMat");
    if (a[0].size() != b.size())
        throw invalid_argument("dotMat: inner dimensions do not match");
    mat out(a.size(), vector<double>(b[0].size(), 0.0));
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = 0; j < b[0].size(); ++j)
            for (size_t k = 0; k < b.size(); ++k)
                out[i][j] += a[i][k] * b[k][j];
    return out;
}

// ---------------------------------------------------------------------------
// Addition
// ---------------------------------------------------------------------------
inline mat addTwo_Matrices(const mat &a, const mat &b)
{
    requireSameShape(a, b, "addTwo_Matrices");
    mat ans(a.size(), vector<double>(a[0].size(), 0.0));
    for (size_t i = 0; i < a.size(); ++i)
        for (size_t j = 0; j < a[0].size(); ++j)
            ans[i][j] = a[i][j] + b[i][j];
    return ans;
}

inline mat addMatix_withNum(const mat &m, double num)
{
    requireNonEmpty(m, "addMatix_withNum");
    mat other(m.size(), vector<double>(m[0].size(), num));
    return addTwo_Matrices(m, other);
}

// ---------------------------------------------------------------------------
// Scalar multiplication / division
// ---------------------------------------------------------------------------
inline mat scalerToMatrix(double scalar, const mat &m)
{
    requireNonEmpty(m, "scalerToMatrix");
    int rows = m.size();
    int cols = m[0].size();
    mat ans(rows, vector<double>(cols, 0.0));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            ans[i][j] = m[i][j] * scalar; // FIX: element, not the whole matrix
    return ans;
}

inline mat scalerToMatrixdiv(double scalar, const mat &m)
{
    requireNonEmpty(m, "scalerToMatrixdiv");
    if (scalar == 0.0)
        throw invalid_argument("scalerToMatrixdiv: division by zero");
    int rows = m.size();
    int cols = m[0].size();
    mat ans(rows, vector<double>(cols, 0.0));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            ans[i][j] = m[i][j] / scalar;
    return ans;
}

// ---------------------------------------------------------------------------
// exp / log / sigmoid
// ---------------------------------------------------------------------------
inline mat expMat(const mat &m)
{
    requireNonEmpty(m, "expMat");
    mat ans(m.size(), vector<double>(m[0].size(), 0.0));
    for (size_t i = 0; i < m.size(); ++i)
        for (size_t j = 0; j < m[0].size(); ++j)
            ans[i][j] = std::exp(m[i][j]);
    return ans;
}

inline mat logMat(const mat &m)
{
    requireNonEmpty(m, "logMat");
    mat ans(m.size(), vector<double>(m[0].size(), 0.0));
    for (size_t i = 0; i < m.size(); ++i)
        for (size_t j = 0; j < m[0].size(); ++j)
            ans[i][j] = std::log(m[i][j]);
    return ans;
}

inline mat sigmoid(const mat &m)
{
    mat B = m;
    for (auto &row : B)
        for (auto &u : row)
            u = 1.0 / (1.0 + std::exp(-u));
    return B;
}

// ---------------------------------------------------------------------------
// Print helpers
// ---------------------------------------------------------------------------
inline void printMat(const mat &m, const string &title = "", int precision = 4)
{
    size_t rows = m.size();
    size_t cols = m.empty() ? 0 : m[0].size();
    if (!title.empty())
        cout << title << " (" << rows << "x" << cols << "):\n";

    ios_base::fmtflags oldFlags = cout.flags();
    streamsize oldPrec = cout.precision();
    cout << fixed << setprecision(precision);

    for (const auto &row : m)
    {
        cout << "  [ ";
        for (double v : row)
            cout << setw(10) << v << " ";
        cout << "]\n";
    }

    cout.flags(oldFlags);
    cout.precision(oldPrec);
}

template <typename T, int R, int C>
mat toMat(const T (&a)[R][C])
{
    mat m(R, vector<double>(C));
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            m[i][j] = static_cast<double>(a[i][j]);
    return m;
}

template <typename T, int R, int C>
void printArr(const T (&a)[R][C], const string &title = "")
{
    printMat(toMat(a), title);
}

// ---------------------------------------------------------------------------
// Tiny test harness
// (inline variables need C++17; on older standards, move these two counters
//  into a .cpp file or make them static.)
// ---------------------------------------------------------------------------
inline int g_pass = 0;
inline int g_fail = 0;

inline void check(bool cond, const string &name)
{
    if (cond)
    {
        ++g_pass;
        cout << "  [PASS] " << name << "\n";
    }
    else
    {
        ++g_fail;
        cout << "  [FAIL] " << name << "\n";
    }
}

inline bool approx(double a, double b, double eps = 1e-9)
{
    if (std::isnan(a) && std::isnan(b))
        return true;
    if (std::isinf(a) || std::isinf(b))
        return a == b;
    return std::fabs(a - b) <= eps;
}

inline bool approxMat(const mat &a, const mat &b, double eps = 1e-9)
{
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a[i].size() != b[i].size())
            return false;
        for (size_t j = 0; j < a[i].size(); ++j)
            if (!approx(a[i][j], b[i][j], eps))
                return false;
    }
    return true;
}

template <typename F>
bool throwsInvalid(F f)
{
    try
    {
        f();
    }
    catch (const invalid_argument &)
    {
        return true;
    }
    return false;
}

#endif // COREMATHS_HPP
