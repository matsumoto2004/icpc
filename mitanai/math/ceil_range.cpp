// divide i = 1..n into O(√n) groups by the value of ceil(n / i)
// {t, l, r} : ceil(n / i) = t for i = l..r
// sorted in the descending order of t
// e.g. n = 4  res = {{4, 1, 1}, {2, 2, 3}, {1, 4, 4}}
template<class T>
vector <tuple<T, T, T>> ceil_range(T n) {
    assert(n >= 1);
    T D = 1;
    while ((D + 1) * (D + 1) <= n) ++D;
    vector <tuple<T, T, T>> res;
    for (T i = 1; i <= n; i++) {
        if ((n + i - 1) / i <= D) break;
        res.emplace_back((n + i - 1) / i, i, i);
    }
    for (T i = D; i >= 2; i--) {
        T l = (n + i - 1) / i;
        T r = (n + i - 2) / (i - 1) - 1;
        if (l <= r) res.emplace_back(i, l, r);
    }
    res.emplace_back(1, n, n);
    return res;
}