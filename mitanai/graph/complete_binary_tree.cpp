class complete_binary_tree {
    ll n;
    int log;

public:
    complete_binary_tree(ll n) : n(n), log(63 - __builtin_clzll(n)) {
        assert(n >= 1);
    }

    // calc the set of vertexes which are k away from vertex x
    // return the list of disjoint semi-open intervals
    vector <pair<ll, ll>> k_from_x(ll x, ll k) {
        assert(1 <= x and x <= n);
        vector <pair<ll, ll>> res;
        int dx = 63 - __builtin_clzll(x);
        for (int i = 0; i <= dx; i++) { // i : depth of lca
            if (dx - i > k) continue;
            if (i + k - (dx - i) > log) continue;
            ll l, r;
            if (i == dx) {
                l = x << k;
                r = (x + 1) << k;
            } else {
                ll z = x >> (dx - i);
                if (dx - i < k) {
                    l = z * 2 + (~x >> (dx - i - 1) & 1);
                    l <<= (k - (dx - i) - 1);
                    r = l + (1LL << (k - (dx - i) - 1));
                } else {
                    l = z, r = z + 1;
                }
            }
            if (l > n) continue;
            res.emplace_back(l, min(r, n + 1));
        }
        return res;
    }
};