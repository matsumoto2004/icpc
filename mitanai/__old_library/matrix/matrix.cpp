template<typename T>
class matrix : public vector<vector < T>>

{
public:
using vector<vector < T>>::vector;

constexpr int get_h() const { return this->size(); }

constexpr int get_w() const { return (get_h() ? (*this)[0].size() : 0); }

constexpr matrix
&

operator+=(const matrix &a) {
    rep(i, get_h())
    rep(j, get_w())(*this)[i][j] += a[i][j];
    return *this;
}

constexpr matrix
&

operator*=(const int &k) {
    rep(i, get_h())
    rep(j, get_w())(*this)[i][j] *= k;
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

constexpr matrix

operator*(const matrix &a) const {
    int h = get_h(), w = get_w(), ah = a.get_h(), aw = a.get_w();
    assert(w == ah);
    matrix res(h, vector<T>(aw));
    rep(i, h)
    rep(j, w)
    rep(k, aw)
    res[i][k] += (*this)[i][j] * a[j][k];
    return res;
}

constexpr matrix
&

operator*=(const matrix &a) { return *this = *this * a; }

constexpr matrix
pow(ll
t) const {
int h = get_h(), w = get_w();
assert(h
== w);
matrix res(h, vector<T>(w)), a(*this);
rep(i, get_h()
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

using mat = matrix<>;