template<class M>
class lazy_segtree {
    using S = typename M::S;
    using F = typename M::F;

    int _n, sz, log;
    vector <S> d;
    vector <F> lz;

    void update(int k) { d[k] = M::op(d[2 * k], d[2 * k + 1]); }

    void all_apply(int k, F f) {
        d[k] = M::mapping(f, d[k]);
        if (k < sz) lz[k] = M::composition(f, lz[k]);
    }

    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = M::id;
    }

public:
    constexpr lazy_segtree() : lazy_segtree(0) {}

    constexpr lazy_segtree(int _n) : lazy_segtree(vector<S>(_n, M::e)) {}

    constexpr lazy_segtree(const vector <S> &init) : _n(int(init.size())) {
        log = 0;
        while (1 << log < _n) log++;
        sz = 1 << log;
        d.assign(2 * sz, M::e);
        lz.assign(sz, M::id);
        rep(i, _n)
        d[sz + i] = init[i];
        rrep(i, sz, 1)
        update(i);
    }

    void set(int p, S x) {
        assert(0 <= p and p < _n);
        p += sz;
        rrep(i, log + 1, 1)
        push(p >> i);
        d[p] = x;
        rep(i, 1, log + 1)
        update(p >> i);
    }

    template<class F>
    void apply(int p, const F &f) {
        assert(0 <= p and p < _n);
        p += sz;
        rrep(i, log + 1, 1)
        push(p >> i);
        d[p] = f(d[p]);
        rep(i, 1, log + 1)
        update(p >> i);
    }

    S get(int p) {
        assert(0 <= p and p < _n);
        p += sz;
        rrep(i, log + 1, 1)
        push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l and l <= r and r <= _n);

        l += sz, r += sz;

        rrep(i, log + 1, 1)
        {
            if ((l >> i) << i != l) push(l >> i);
            if ((r >> i) << i != r) push(r >> i);
        }

        S sl = M::e, sr = M::e;
        while (l < r) {
            if (l & 1) sl = M::op(sl, d[l++]);
            if (r & 1) sr = M::op(d[--r], sr);
            l >>= 1, r >>= 1;
        }

        return M::op(sl, sr);
    }

    S all_prod() {
        return d[1];
    }

    void apply(int l, int r, F f) {
        assert(0 <= l and l <= r and r <= _n);

        l += sz, r += sz;

        rrep(i, log + 1, 1)
        {
            if ((l >> i) << i != l) push(l >> i);
            if ((r >> i) << i != r) push(r >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1, r >>= 1;
            }
            l = l2, r = r2;
        }

        rep(i, 1, log + 1)
        {
            if ((l >> i) << i != l) update(l >> i);
            if ((r >> i) << i != r) update(r >> i);
        }
    }

    template<class F>
    int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(M::e));
        if (l == _n) return _n;
        l += sz;
        rrep(i, log + 1, 1)
        push(l >> i);
        S now = M::e;
        do {
            while (~l & 1) l >>= 1;
            if (!f(M::op(now, d[l]))) {
                while (l < sz) {
                    push(l);
                    l *= 2;
                    if (f(M::op(now, d[l]))) {
                        now = M::op(now, d[l]);
                        ++l;
                    }
                }
                return l - sz;
            }
            now = M::op(now, d[l]);
            ++l;
        } while ((l & -l) != l);
        return _n;
    }

    template<class F>
    int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(M::e));
        if (r == 0) return 0;
        r += sz;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S now = M::e;
        do {
            r--;
            while (r > 1 && (r & 1)) r >>= 1;
            if (!f(M::op(d[r], now))) {
                while (r < sz) {
                    push(r);
                    r = 2 * r + 1;
                    if (f(M::op(d[r], now))) {
                        now = M::op(d[r], now);
                        --r;
                    }
                }
                return r + 1 - sz;
            }
            now = M::op(d[r], now);
        } while ((r & -r) != r);
        return 0;
    }
};

class M {
public:
    using S = ;

    static constexpr S
    e =;

    static constexpr S

    op(const S &l, const S &r) {
        return;
    }

    using F = ;

    static constexpr F
    id =;

    static constexpr F

    composition(const F &g, const F &f) {
        return;
    }

    static constexpr S

    mapping(const F &f, const S &x) {
        return;
    }
};