class Mo {
    int n, q;
    vi l, r;
public:
    Mo(int _n, const vi &_l, const vi &_r) : n(_n), l(_l), r(_r) {
        assert(SZ(l) == SZ(r));
        q = SZ(l);
    }
    
    // auto add = [](int i, T &now);
    template<class T, class ADD, class DEL>
    vector <T> solve(T e, const ADD &add, const DEL &del) {
        int D = max(1, int(double(n) / sqrt(q)));
        vi ord(q);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            if (r[i] / D != r[j] / D) return r[i] / D < r[j] / D;
            return l[i] < l[j];
        });
        vector <T> ans(q);
        T now = e;
        int nl = 0, nr = 0;
        for (int i: ord) {
            while (l[i] < nl) add(--nl, now);
            while (nr < r[i]) add(nr++, now);
            while (l[i] > nl) del(nl++, now);
            while (nr > r[i]) del(--nr, now);
            ans[i] = now;
        }
        return ans;
    }
};
