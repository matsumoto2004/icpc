template<class T>
class polynomial : public vector<T> {
public:
    using vector<T>::vector;
    
    constexpr T eval(T x) const {
        T res = 0;
        T now = 1;
        rep(i, this->size()) {
            res += (*this)[i] * now;
            now *= x;
        }
        return res;
    }
    
    // return f'(x)
    constexpr polynomial differ() const {
        vector<T> res;
        rep2(i, 1, this->size()) res.pb((*this)[i] * i);
        return polynomial(all(res));
    }
    
    // return ∫ f(x)dx
    constexpr polynomial integral() const {
        int n = this->size();
        if (n == 0) return vector<T>();
        vector<T> res = {0};
        rep(i, n) res.pb((*this)[i] / (i + 1));
        return polynomial(all(res));
    };
    
    constexpr polynomial operator+(const polynomial &a) const {
        vector<T> res(max(this->size(), a.size()));
        rep(i, this->size()) res[i] += (*this)[i];
        rep(i, a.size()) res[i] += a[i];
        return polynomial(all(res));
    }
    
    constexpr polynomial operator-(const polynomial &a) const {
        vector<T> res(max(this->size(), a.size()));
        rep(i, this->size()) res[i] += (*this)[i];
        rep(i, a.size()) res[i] -= a[i];
        return polynomial(all(res));
    }
    
    constexpr polynomial operator*(const polynomial &a) const {
        vector<T> res = convolution(*this, a);
        return polynomial(all(res));
    }
    
    constexpr polynomial operator*(T k) const {
        polynomial res(*this);
        rep(i, res.size()) res[i] *= k;
        return res;
    }
    
    constexpr polynomial &operator+=(const polynomial &a) {
        return *this = *this + a;
    }
    
    constexpr polynomial &operator-=(const polynomial &a) {
        return *this = *this - a;
    }
    
    constexpr polynomial &operator*=(const polynomial &a) {
        return *this = *this * a;
    }
    
    // P *= (ax + b)
    constexpr void multiply(T a = 0, T b = 1) {
        int n = this->size();
        this->push_back(T(0));
        rrep(i, n) {
            (*this)[i + 1] += (*this)[i] * a;
            (*this)[i] *= b;
        }
    }
    
    // P /= (ax + b)
    constexpr void divide(T a = 0, T b = 1) {
        int n = this->size();
        assert(n >= 2);
        assert(a != 0 or b != 0);
        if (b == T(0)) {
            assert((*this)[0] == T(0));
            T inv = T(1) / a;
            rep(i, n - 1) (*this)[i] = (*this)[i + 1] * inv;
            this->back() = T(0);
        } else {
            T inv = T(1) / b;
            rep(i, n - 1) {
                (*this)[i] *= inv;
                (*this)[i + 1] -= (*this)[i] * a;
            }
            assert(this->back() == T(0));
        }
    }
};

template<class T>
polynomial <T> lagrange_interpolation(const vector <T> &x, const vector <T> &y) {
    int n = x.size();
    assert(n == y.size());
    assert(n >= 2);
    polynomial <T> now(1, T(1)), res;
    now.reserve(n + 1);
    rep(i, n)
    now.multiply(1, -x[i]);
    rep(i, n)
    {
        now.divide(1, -x[i]);
        res += now * (y[i] / now.eval(x[i]));
        now.multiply(1, -x[i]);
    }
    res.resize(n);
    return res;
}