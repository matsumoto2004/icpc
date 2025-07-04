template<class T, int H, int W>
T determinant(matrix <T, H, W> a) {
    static_assert(H == W);
    T res = 1;
    rep(col, H)
    {
        int pivot = -1;
        rep(row, col, H)
        {
            if (a[row][col] != T(0)) pivot = row;
        }
        if (pivot == -1) return 0;
        if (pivot != col) {
            res *= -1;
            swap(a[pivot], a[col]);
        }
        res *= a[col][col];
        rep(row, H)
        {
            if (row == col) continue;
            if (a[row][col] == T(0)) continue;
            T fac = a[row][col] / a[col][col];
            rep(col2, H)
            a[row][col2] -= a[col][col2] * fac;
        }
    }
    return res;
}

template<int H, int W>
double determinant(matrix<double, H, W> a) {
    const double eps = 1e-9;

    static_assert(H == W);
    double res = 1;
    rep(col, H)
    {
        int pivot = -1;
        double mx = eps;
        rep(row, col, H)
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
        rep(row, H)
        {
            if (row == col) continue;
            if (abs(a[row][col]) <= eps) continue;
            double fac = a[row][col] / a[col][col];
            rep(col2, H)
            a[row][col2] -= a[col][col2] * fac;
        }
    }
    return res;
}