const double eps = 1e-9;

template<class T>
T determinant(matrix <T> a) {
    assert(a.get_h() == a.get_w());
    int n = a.get_h();
    T res = 1;
    rep(col, n)
    {
        int pivot = -1;
        rep(row, col, n)
        {
            if (a[row][col] != T(0)) pivot = row;
        }
        if (pivot == -1) return 0;
        if (pivot != col) {
            res *= -1;
            swap(a[pivot], a[col]);
        }
        res *= a[col][col];
        rep(row, n)
        {
            if (row == col) continue;
            if (a[row][col] == T(0)) continue;
            T fac = a[row][col] / a[col][col];
            rep(col2, n)
            a[row][col2] -= a[col][col2] * fac;
        }
    }
    return res;
}

template<>
double determinant(matrix<double> a) {
    assert(a.get_h() == a.get_w());
    int n = a.get_h();
    double res = 1;
    rep(col, n)
    {
        int pivot = -1;
        double mx = eps;
        rep(row, col, n)
        {
            if (abs(a[row][col]) > mx) {
                mx = abs(a[row][col]);
                pivot = row;
            }
        }
        if (pivot == -1) return 0;
        if (pivot != col) {
            res *= -1;
            swap(a[pivot], a[col]);
        }
        res *= a[col][col];
        rep(row, n)
        {
            if (row == col) continue;
            if (abs(a[row][col]) <= eps) continue;
            double fac = a[row][col] / a[col][col];
            rep(col2, n)
            a[row][col2] -= a[col][col2] * fac;
        }
    }
    return res;
}