template<class T, int H, int W>
class matrix : public array<array < T, W>, H

> {
public:
using array<array < T, W>, H>::array;

constexpr matrix
&

operator+=(const matrix &a) {
    rep(i, H)
    rep(j, W)(*this)[i][j] += a[i][j];
    return *this;
}

constexpr matrix
&

operator*=(const int &k) {
    rep(i, H)
    rep(j, W)(*this)[i][j] *= k;
    return *this;
}

constexpr matrix
&

operator-=(const matrix &a) {
    *this += a * (-1);
    return *this;
}

constexpr matrix

operator+(const matrix &a) const { return res(*this) += a; }

constexpr matrix

operator*(const int &k) const { return res(*this) *= k; }

constexpr matrix

operator-(const matrix &a) const { return res(*this) -= a; }

template<int X>
constexpr matrix<T, H, X>

operator*(const matrix<T, W, X> &a) const {
    matrix res(H, vector<T>(X));
    rep(i, H)
    rep(j, W)
    rep(k, X)
    res[i][k] += (*this)[i][j] * a[j][k];
    return res;
}

constexpr matrix
&

operator*=(const matrix &a) { return *this = *this * a; }

constexpr matrix
pow(ll
t) const {
static_assert(H
== W);
matrix res(H, vector<T>(W)), a(*this);
rep(i, H
) res[i][i] = 1;
while (t > 0) {
if (t & 1) res *=
a;
t >>= 1;
a *=
a;
}
return
res;
}
};

template<int H, int W>
using mat = matrix<, H, W>;