// y[i] = P(i) for i in [0, n)
// return P(eval_x)
// time complexity : O(n)
template<class T>
T lagrange_interpolation_eval(T eval_x, const vector <T> &y) {
    int n = y.size();
    vector <T> ifact(n, T(1));
    rep(i, 1, n)
    ifact[n - 1] *= i;
    ifact[n - 1] = T(1) / ifact[n - 1];
    rrep(i, n - 1)
    ifact[i] = ifact[i + 1] * T(i + 1);
    vector <T> ls(n + 1, T(1)), rs(n + 1, T(1));
    rep(i, n)
    ls[i + 1] = ls[i] * (eval_x - i);
    rrep(i, n)
    rs[i] = rs[i + 1] * (eval_x - i);
    T res = 0;
    rep(i, n)
    {
        T now = ls[i] * rs[i + 1] * ifact[i] * ifact[n - 1 - i] * y[i];
        if ((n - 1 - i) & 1) res -= now;
        else res += now;
    }
    return res;
}