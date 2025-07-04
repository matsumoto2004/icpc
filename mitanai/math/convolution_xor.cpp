template<class T>
void fwt(vector<T> &v) {
    int n = v.size();
    assert(n == 1 << __builtin_ctz(n));
    for (int i = 1; i < n; i <<= 1) {
        rep(j, n) {
            if ((j & i) == 0) {
                T x = v[j], y = v[j | i];
                v[j] = x + y, v[j | i] = x - y;
            }
        }
    }
}

template<class T>
void ifwt(vector<T> &v) {
    int n = v.size();
    assert(n == 1 << __builtin_ctz(n));
    for (int i = 1; i < n; i <<= 1) {
        rep(j, n) {
            if ((j & i) == 0) {
                T x = v[j], y = v[j | i];
                // T = mint の時は 2 の逆元を前計算すると速い
                v[j] = (x + y) / 2, v[j | i] = (x - y) / 2;
            }
        }
    }
}

// sum_{i ^ j = k} {a_i * b_j} = c_k
template<class T>
vector<T> convolution_xor(vector<T> a, vector<T> b) {
    int s = max(a.size(), b.size());
    int t = 1;
    while (t < s) t *= 2;
    a.resize(t);
    b.resize(t);
    fwt(a);
    fwt(b);
    rep(i, t) a[i] *= b[i];
    ifwt(a);
    a.resize(s);
    return a;
}