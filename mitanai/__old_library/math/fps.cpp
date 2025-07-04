class NTT {
    int pr;
    
    constexpr ll pow_mod(ll x, ll n, int m) {
        if (m == 1) return 0;
        ll res = 1;
        ll now = x % m;
        while (n > 0) {
            if (n & 1) res = (res * now) % m;
            now = (now * now) % m;
            n >>= 1;
        }
        return res;
    }
    
    constexpr int primitive_root(int mod) {
        if (mod == 2) return 1;
        if (mod == 167772161) return 3;
        if (mod == 469762049) return 3;
        if (mod == 754974721) return 11;
        if (mod == 998244353) return 3;
        int divs[20] = {};
        divs[0] = 2;
        int cnt = 1;
        int x = (mod - 1) / 2;
        while (x % 2 == 0) x /= 2;
        for (int i = 3; (ll) i * i <= x; i += 2) {
            if (x % i == 0) {
                divs[cnt++] = i;
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
        if (x > 1) divs[cnt++] = x;
        for (int g = 2;; g++) {
            bool ok = true;
            for (int i = 0; i < cnt; i++) {
                if (pow_mod(g, (mod - 1) / divs[i], mod) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return g;
        }
    }

public:
    NTT() { init(mint::get_mod()); }
    
    mint sum_e[30]; // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]
    mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    
    void init(int mod) {
        pr = primitive_root(mod);
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = __builtin_ctz(mint::get_mod() - 1);
        mint e = mint(pr).pow((mint::get_mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
        now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }
    
    void operator()(vm &a, bool inverse = false) {
        int n = a.size();
        int h = __builtin_ctz(n);
        if (inverse) {
            rrep(ph, h + 1, 1)
            {
                int w = 1 << (ph - 1), p = 1 << (h - ph);
                mint now = 1;
                rep(s, w)
                {
                    int offset = s << (h - ph + 1);
                    rep(i, p)
                    {
                        auto l = a[i + offset];
                        auto r = a[i + offset + p];
                        a[i + offset] = l + r;
                        a[i + offset + p] = (l - r) * now;
                    }
                    now *= sum_ie[__builtin_ctz(~(unsigned int) (s))];
                }
            }
            mint iv = mint(n).inv();
            rep(i, n)
            a[i] *= iv;
        } else {
            rep(ph, 1, h + 1)
            {
                int w = 1 << (ph - 1), p = 1 << (h - ph);
                mint now = 1;
                rep(s, w)
                {
                    int offset = s << (h - ph + 1);
                    rep(i, p)
                    {
                        auto l = a[i + offset];
                        auto r = a[i + offset + p] * now;
                        a[i + offset] = l + r;
                        a[i + offset + p] = l - r;
                    }
                    now *= sum_e[__builtin_ctz(~(unsigned int) (s))];
                }
            }
        }
    }
} ntt;

class fps : public vector<mint> {
    static fps convolution(const fps &a, const fps &b) {
        if (a.empty()) return {};
        if (b.empty()) return {};
        int s = a.size() + b.size() - 1;
        if (min(a.size(), b.size()) <= 50) {
            fps res(s);
            if (a.size() >= b.size()) {
                rep(i, a.size())
                rep(j, b.size())
                res[i + j] += a[i] * b[j];
            } else {
                rep(j, b.size())
                rep(i, a.size())
                res[i + j] += a[i] * b[j];
            }
            return res;
        }
        int t = 1;
        while (t < s) t *= 2;
        fps A(t), B(t);
        rep(i, a.size())
        A[i] = a[i];
        rep(i, b.size())
        B[i] = b[i];
        ntt(A);
        ntt(B);
        rep(i, t)
        A[i] *= B[i];
        ntt(A, true);
        A.resize(s);
        return A;
    }

public:
    using vector<mint>::vector;
    
    mint eval(mint x) const {
        mint res = 0;
        mint now = 1;
        rep(i, this->size())
        {
            res += (*this)[i] * now;
            now *= x;
        }
        return res;
    }
    
    // return f'(x)
    fps differ() const {
        int n = this->size();
        fps res(n - 1);
        rep2(i, 1, n)
        res[i - 1] = (*this)[i] * i;
        return res;
    }
    
    // return ∫ f(x)dx
    fps integral() const {
        int n = this->size();
        if (n == 0) return fps();
        fps res(n + 1);
        rep(i, n)
        res[i + 1] = (*this)[i] / (i + 1);
        return res;
    };
    
    fps &operator+=(const fps &a) {
        if (this->size() < a.size()) this->resize(a.size());
        rep(i, a.size())(*this)[i] += a[i];
        return *this;
    }
    
    fps &operator-=(const fps &a) {
        if (this->size() < a.size()) this->resize(a.size());
        rep(i, a.size())(*this)[i] -= a[i];
        return *this;
    }
    
    fps &operator*=(const fps &a) {
        return *this = fps::convolution(*this, a);
    }
    
    fps &operator*=(mint k) {
        rep(i, this->size())(*this)[i] *= k;
        return *this;
    }
    
    fps operator+(const fps &a) const {
        fps res(*this);
        return res += a;
    }
    
    fps operator-(const fps &a) const {
        fps res(*this);
        return res -= a;
    }
    
    fps operator*(const fps &a) const {
        fps res(*this);
        return res *= a;
    }
    
    fps operator*(mint k) const {
        fps res(*this);
        return res *= k;
    }

    //間違ってるかも!!
    fps &operator/=(mint k) {
        rep(i, this->size())(*this)[i] /= k;
        return *this;
    }

    fps operator/(mint k) const {
        fps res(*this);
        return res /= k;
    }
    //


//    // P /= (ax + b)
//    constexpr void divide(T a = 0, T b = 1) {
//        int n = this->size();
//        assert(n >= 2);
//        assert(a != 0 or b != 0);
//        if (b == T(0)) {
//            assert((*this)[0] == T(0));
//            T inv = T(1) / a;
//            rep(i, n - 1) (*this)[i] = (*this)[i + 1] * inv;
//            this->back() = T(0);
//        } else {
//            T inv = T(1) / b;
//            rep(i, n - 1) {
//                (*this)[i] *= inv;
//                (*this)[i + 1] -= (*this)[i] * a;
//            }
//            assert(this->back() == T(0));
//        }
//    }

//  reference of inv, log, exp, pow : https://opt-cp.com/fps-fast-algorithms/
    fps inv(int deg = -1) const {
        int n = this->size();
        assert(n and (*this)[0].val() == 1);
        if (deg == -1) deg = n;
        fps res(deg);
        res[0] = (*this)[0].inv();
        for (int m = 1; m < deg; m <<= 1) {
            fps f(2 * m), g(2 * m);
            rep(i, min(n, 2 * m))
            f[i] = (*this)[i];
            rep(i, m)
            g[i] = res[i];
            ntt(f), ntt(g);
            rep(i, 2 * m)
            f[i] *= g[i];
            ntt(f, true);
            rep(i, m)
            f[i] = 0;
            ntt(f);
            rep(i, 2 * m)
            f[i] *= g[i];
            ntt(f, true);
            rep(i, m, min(2 * m, deg))
            res[i] = -f[i];
        }
        return res;
    }
    
    fps &divide_inplace(const fps &a, int d = -1) {
        int n = this->size();
        if (d == -1) d = n;
        assert(d >= 0);
        *this = convolution(move(*this), a.inv(d));
        this->resize(d);
        return *this;
    }
    
    fps divide(const fps &a, int d = -1) {
        fps res(*this);
        return res.divide_inplace(a, d);
    }
    
    fps log(int deg = -1) const {
        int n = this->size();
        assert(n and (*this)[0].val() == 1);
        if (deg == -1) deg = n;
        fps res(this->differ());
        res.divide_inplace(*this, deg);
        res = res.integral();
        res.pop_back();
        return res;
    }
    
    fps exp(int deg = -1) const {
        int n = this->size();
        assert(n and (*this)[0].val() == 0);
        if (deg == -1) deg = n;
        fps g{1}, g_fft, f(*this);
        f.resize(deg);
        f[0] = 1;
        fps h_prime(this->differ());
        h_prime.pb(0);
        for (int m = 1; m < deg; m *= 2) {
            // prepare
            fps f_fft(f.begin(), f.begin() + m);
            f_fft.resize(2 * m);
            ntt(f_fft);
            
            // Step 2.a'
            if (m > 1) {
                fps _f(m);
                rep(i, m)
                _f[i] = f_fft[i] * g_fft[i];
                ntt(_f, true);
                _f.erase(_f.begin(), _f.begin() + m / 2);
                _f.resize(m), ntt(_f);
                rep(i, m)
                _f[i] *= g_fft[i];
                ntt(_f, true);
                _f.resize(m / 2);
                _f *= -1;
                g.insert(g.end(), _f.begin(), _f.begin() + m / 2);
            }
            
            // Step 2.b'--d'
            fps t(f.begin(), f.begin() + m);
            t = t.differ();
            t.pb(0);
            {
                // Step 2.b'
                fps r(h_prime.begin(), h_prime.begin() + m - 1);
                // Step 2.c'
                r.resize(m);
                ntt(r);
                rep(i, m)
                r[i] *= f_fft[i];
                ntt(r, true);
                // Step 2.d'
                t -= r;
                t.insert(t.begin(), t.back());
                t.pop_back();
            }
    
            // Step 2.e'
            t.resize(2 * m);
            ntt(t);
            g_fft = g;
            g_fft.resize(2 * m);
            ntt(g_fft);
            rep(i, 2 * m)
            t[i] *= g_fft[i];
            ntt(t, true);
            t.resize(m);
    
            // Step 2.f'
            fps v(f.begin() + m, f.begin() + min(deg, 2 * m));
            v.resize(m);
            t.insert(t.begin(), m - 1, 0);
            t.push_back(0);
            t = t.integral();
            rep(i, m)
            v[i] -= t[m + i];
    
            // Step 2.g'
            v.resize(2 * m);
            ntt(v);
            rep(i, 2 * m)
            v[i] *= f_fft[i];
            ntt(v, true);
            v.resize(m);
    
            // Step 2.h'
            rep(i, min(deg - m, m))
            f[m + i] = v[i];
        }
        return f;
    }
    
    fps pow(ll k, int deg = -1) const {
        int n = this->size();
        if (deg == -1) deg = n;
        assert(k >= 0);
        if (k == 0) {
            fps res(deg);
            if (deg > 0) res[0] = 1;
            return res;
        }
        int l = 0;
        while (l < n && (*this)[l].val() == 0) ++l;
        if (l > (deg - 1) / k or l == n) return fps(deg);
        mint c = (*this)[l];
        fps res(this->begin() + l, this->end());
        res *= c.inv();
        res = res.log(deg - l * k);
        res *= k;
        res = res.exp();
        res *= c.pow(k);
        res.insert(res.begin(), l * k, 0);
        return res;
    }
    
    // calc f(x + c)
    // time complexity : O(n log n)
    fps taylor_shift(mint c) {
        int n = this->size();
        vm fact(n), ifact(n);
        fact[0] = 1;
        rep(i, 1, n)
        fact[i] = fact[i - 1] * i;
        ifact[n - 1] = fact[n - 1].inv();
        rrep(i, n - 1)
        ifact[i] = ifact[i + 1] * (i + 1);
        fps f(n), g(n);
        mint nc = 1;
        rep(i, n)
        {
            f[i] = (*this)[n - 1 - i] * fact[n - 1 - i];
            g[i] = nc * ifact[i];
            nc *= c;
        }
        fps h = f * g;
        fps res(n);
        rep(i, n)
        res[i] = ifact[i] * h[n - 1 - i];
        return res;
    }
};