template<class T>
class dirichlet {
    static int n, k, l;
    // v[i] : i^(-s)
    // V[i] : sum_{j=1}^{floor(n/i)} i^(-s)
    vector <T> v, V;
public:
    static void set_n(int _n) {
        n = _n;
        k = ceil(cbrt((ll) n * n));
        l = (n + k - 1) / k;
    }
    
    static dirichlet e() {
        vector <T> v(k + 1, 0);
        v[1] = 1;
        vector <T> V(l + 1, 1);
        V[0] = 0;
        return dirichlet(v, V);
    }
    
    static dirichlet zeta() {
        vector <T> v(k + 1, 1);
        v[0] = 0;
        vector <T> V(l + 1, 0);
        rep(i, 1, l + 1)
        V[i] = n / i;
        return dirichlet(v, V);
    }
    
    dirichlet() {
        assert(n > 0);
        v.assign(k + 1, 0);
        V.assign(l + 1, 0);
    }
    
    dirichlet(const vector <T> &_v, const vector <T> &_V) : v(_v), V(_V) {
        assert(n > 0);
        assert(_v.size() == k + 1);
        assert(_V.size() == l + 1);
    }
    
    constexpr T
    
    get_v(int i) const {
        assert(1 <= i and i <= k);
        return v[i];
    }
    
    constexpr vector<T>
    
    get_v() const { return v; }
    
    constexpr T
    
    get_V(int i) const {
        assert(1 <= i and i <= l);
        return V[i];
    }
    
    constexpr vector<T>
    
    get_V() const { return V; }
    
    // O(K log K + (NL)^(1/2)) ≒ O(N^(2/3)(log N)^(1/3))
    dirichlet operator*(const dirichlet &d) const {
        const vector<T> &a = v, &A = V;
        const vector<T> &b = d.get_v(), &B = d.get_V();
        vector<T> A_low(k + 1), B_low(k + 1);
        rep(i, k)
        A_low[i + 1] = A_low[i] + a[i + 1];
        rep(i, k)
        B_low[i + 1] = B_low[i] + b[i + 1];
        auto get_A = [&](int i) { return (i <= k ? A_low[i] : A[n / i]); };
        auto get_B = [&](int i) { return (i <= k ? B_low[i] : B[n / i]); };
        vector<T> c(k + 1);
        rep(i, 1, k + 1)
        rep(j, 1, k / i + 1)
        {
            c[i * j] += a[i] * b[j];
        }
        vector<T> C(l + 1);
        rep(i, 1, l + 1)
        {
            int now = n / i;
            int m = floor(sqrt(now));
            rep(j, 1, m + 1)
            {
                C[i] += a[j] * get_B(now / j);
                C[i] += b[j] * (get_A(now / j) - get_A(m));
            }
        }
        return dirichlet(move(c), move(C));
    }
    
    dirichlet &operator*=(const dirichlet &d) {
        return *this = *this * d;
    }
    
    dirichlet operator/(const dirichlet &d) const {
        assert(d.get_v(1) != T(0));
        const vector<T> &a = v, &A = V;
        const vector<T> &b = d.get_v(), &B = d.get_V();
        vector<T> B_low(k + 1);
        rep(i, k)
        B_low[i + 1] = B_low[i] + b[i + 1];
        auto get_B = [&](int i) { return (i <= k ? B_low[i] : B[n / i]); };
        vector<T> c = a;
        rep(i, 1, k + 1)
        {
            c[i] /= b[1];
            rep(j, 2, k / i + 1)
            {
                c[i * j] -= c[i] * b[j];
            }
        }
        vector<T> C_low(k + 1);
        rep(i, k)
        C_low[i + 1] = C_low[i] + c[i + 1];
        vector<T> C = A;
        auto get_C = [&](int i) { return (i <= k ? C_low[i] : C[n / i]); };
        rrep(i, l + 1, 1)
        {
            int now = n / i;
            int m = floor(sqrt(now));
            rep(j, 1, m + 1)
            {
                if (j > 1) C[i] -= b[j] * get_C(now / j);
                C[i] -= c[j] * (get_B(now / j) - get_B(m));
            }
            C[i] /= b[1];
        }
        return dirichlet(move(c), move(C));
    }
    
    dirichlet &operator/=(const dirichlet &d) {
        return *this = *this / d;
    }
    
    dirichlet pow(ll t) const {
        assert(t >= 0);
        dirichlet res = dirichlet::e();
        dirichlet now(*this);
        while (t > 0) {
            if (t & 1) res *= now;
            now *= now;
            t >>= 1;
        }
        return res;
    }
};

template<class T> int dirichlet<T>::n = 0;
template<class T> int dirichlet<T>::k = 0;
template<class T> int dirichlet<T>::l = 0;