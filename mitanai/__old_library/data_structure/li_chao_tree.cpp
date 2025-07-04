// Convex Hull Trix (Minimum)
template<class T>
class li_chao_tree {
    int n;
    vector <T> xs;
    // y = ax + b
    vector <T> a, b;
    vi ls, rs;
    
    T eval(T na, T nb, T x) {
        return na * xs[x] + nb;
    }
    
    void add(int k, T na, T nb) {
        int l = ls[k], r = rs[k], m = (l + r) / 2;
        if (l + 1 == r) {
            if (eval(a[k], b[k], l) > eval(na, nb, l)) {
                a[k] = na;
                b[k] = nb;
            }
            return;
        }
        if (eval(a[k], b[k], l) <= eval(na, nb, l) and eval(a[k], b[k], r) <= eval(na, nb, r)) return;
        if (eval(a[k], b[k], l) >= eval(na, nb, l) and eval(a[k], b[k], r) >= eval(na, nb, r)) {
            a[k] = na;
            b[k] = nb;
            return;
        }
        if (eval(a[k], b[k], m) > eval(na, nb, m)) {
            swap(a[k], na);
            swap(b[k], nb);
        }
        if (eval(a[k], b[k], l) > eval(na, nb, l)) {
            add(2 * k, na, nb);
            return;
        }
        if (eval(a[k], b[k], r) > eval(na, nb, r)) {
            add(2 * k + 1, na, nb);
            return;
        }
    }
    
    void init(const vector <T> &_xs) {
        n = 1;
        while (n < (int) _xs.size()) n *= 2;
        a.assign(2 * n, 0);
        b.assign(2 * n, numeric_limits<T>::max());
        ls.resize(2 * n);
        rs.resize(2 * n);
        rep(i, n)
        {
            ls[n + i] = i;
            rs[n + i] = i + 1;
        }
        rrep(i, n)
        {
            ls[i] = ls[2 * i];
            rs[i] = rs[2 * i + 1];
        }
        xs.resize(n + 1, _xs.back() + 1);
        rep(i, _xs.size())
        xs[i] = _xs[i];
    }

public:
    li_chao_tree(const vector <T> &_xs) {
        assert(is_sorted(all(xs)));
        init(_xs);
    }
    
    li_chao_tree(int n) {
        static_assert(numeric_limits<T>::is_integer);
        vector <T> v(n);
        iota(all(v), 0);
        init(v);
    }
    
    T get_min(int i) {
        assert(0 <= i and i < n);
        int x = i;
        i += n;
        T res = linf;
        while (i >= 1) {
            chmin(res, eval(a[i], b[i], x));
            i >>= 1;
        }
        return res;
    }
    
    void add_line(T na, T nb) {
        add(1, na, nb);
    }
    
    void add_segment(int l, int r, T na, T nb) {
        assert(0 <= l and l <= r and r <= n);
        l += n, r += n;
        while (l < r) {
            if (l & 1) add(l++, na, nb);
            if (r & 1) add(--r, na, nb);
            l >>= 1, r >>= 1;
        }
    }
};