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