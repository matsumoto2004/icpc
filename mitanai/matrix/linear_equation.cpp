const double eps = 1e-9;

// return the rank of the matrix
// O(h * w^2)
template<class T>
int GaussJordan(matrix <T> &a, bool isExtended) {
    int rank = 0;
    rep(col, a.get_w())
    {
        if (isExtended and col == a.w - 1) break;
        int pivot = -1;
        rep(row, rank, a.get_h())
        {
            if (a[row][col] != 0) pivot = row;
        }
        if (pivot == -1) continue;
        
        swap(a[pivot], a[rank]);
        
        // fix the value of pivot 1
        rrep(col2, a.get_w())
        a[rank][col2] /= a[rank][col];
        
        rep(row, a.get_h())
        {
            if (row == rank) continue;
            if (a[row][col] == 0) continue;
            T fac = a[row][col];
            rep(col2, a.get_w())
            a[row][col2] -= a[rank][col2] * fac;
        }
        rank++;
    }
    return rank;
}

template<>
int GaussJordan<double>(matrix<double> &a, bool isExtended) {
    int rank = 0;
    rep(col, a.get_w())
    {
        if (isExtended and col == a.get_w() - 1) break;
        int pivot = -1;
        double mx = eps;
        rep(row, rank, a.get_h())
        {
            if (abs(a[row][col]) > mx) {
                mx = abs(a[row][col]);
                pivot = row;
            }
        }
        if (pivot == -1) continue;
        
        swap(a[pivot], a[rank]);
        
        // fix the value of pivot 1
        rrep(col2, a.get_w())
        a[rank][col2] /= a[rank][col];
        
        rep(row, a.get_h())
        {
            if (row == rank) continue;
            if (abs(a[row][col]) <= eps) continue;
            double fac = a[row][col];
            rep(col2, a.get_w())
            a[row][col2] -= a[rank][col2] * fac;
        }
        rank++;
    }
    return rank;
}

// solve ax = b     reference: https://drken1215.hatenablog.com/entry/2019/03/20/202800
// if there is no solution, return empty vector
// otherwise, return one solution (all parameters is fixed 0)
// if T is mint, calculate the numbers of solutions by 'mod^(n-rank)'
// if T is mint, mod must be a prime
template<class T>
vector <T> linear_equation(matrix <T> &a, vector <T> &b) {
    assert(a.get_h() == (int) b.size());
    matrix <T> m(a.get_h(), a.get_w() + 1);
    rep(i, a.get_h())
    {
        rep(j, a.get_w())
        m[i][j] = a[i][j];
        m[i][a.get_w()] = b[i];
    }
    int rank = GaussJordan(m, true);
    
    vector <T> res;
    rep(row, rank, a.get_h())
    {
        if (m[row][a.get_w()] != 0) return res;
    }
    
    res.assign(a.get_w(), 0);
    rep(i, rank)
    {
        rep(j, a.get_w())
        {
            if (m[i][j] != 0) {
                res[j] = m[i][a.get_w()];
                break;
            }
        }
    }
    return res;
}

template<>
vd linear_equation<double>(matrix<double> &a, vector<double> &b) {
    assert(a.get_h() == (int) b.size());
    matrix<double> m(a.get_h(), a.get_w() + 1);
    rep(i, a.get_h())
    {
        rep(j, a.get_w())
        m[i][j] = a[i][j];
        m[i][a.get_w()] = b[i];
    }
    int rank = GaussJordan(m, true);
    
    vd res;
    rep(row, rank, a.get_h())
    {
        if (abs(m[row][a.get_w()]) > eps) return res;
    }
    
    res.assign(a.get_w(), 0);
    rep(i, rank)
    {
        rep(j, a.get_w())
        {
            if (abs(m[i][j]) > eps) {
                res[j] = m[i][a.get_w()];
                break;
            }
        }
    }
    return res;
}