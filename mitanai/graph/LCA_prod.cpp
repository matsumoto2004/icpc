template<class M>
class LCA {
    using S = typename M::S;
    int n;
    vector <vector<pair < int, S>>>
    G;
    vi dep;
    vvi par;
    vector <vector<S>> dp;

    void dfs(int u, int p, S ps, int d) {
        par[0][u] = p;
        dep[u] = d;
        dp[0][u] = ps;
        for (auto [v, s]: G[u]) if (v != p) dfs(v, u, s, d + 1);
    }

    void init() {
        n = G.size();
        dep.assign(n, -1);
        par.resize(30);
        dp.resize(30);
        rep(i, 30)
        {
            par[i].resize(n);
            dp[i].assign(n, M::e);
        }
        rep(i, n)
        if (dep[i] == -1) dfs(i, -1, M::e, 0);
        rep(k, 29)
        rep(i, n)
        {
            if (par[k][i] < 0) par[k + 1][i] = -1;
            else {
                par[k + 1][i] = par[k][par[k][i]];
                dp[k + 1][i] = M::op(dp[k][i], dp[k][par[k][i]]);
            }
        }
    }

public:
    LCA(const vector <vector<pair < int, S>>

    > &G) :
    G(G) {init();}

    int operator()(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        rep(k, 30)
        if ((dep[v] - dep[u]) >> k & 1) v = par[k][v];
        if (u == v) return u;
        rrep(k, 30)
        {
            if (par[k][u] != par[k][v]) {
                u = par[k][u];
                v = par[k][v];
            }
        }
        assert(par[0][u] == par[0][v]);
        return par[0][u];
    }

    int dist(int u, int v) {
        int w = this->operator()(u, v);
        return dep[u] + dep[v] - dep[w] * 2;
    }

    S prod(int u, int v) {
        int l = this->operator()(u, v);
        int du = dist(u, l), dv = dist(v, l);
        S res = M::e;
        rep(k, 30)
        {
            if (du >> k & 1) {
                res = M::op(res, dp[k][u]);
                u = par[k][u];
            }
            if (dv >> k & 1) {
                res = M::op(res, dp[k][v]);
                v = par[k][v];
            }
        }
        return res;
    }

    // path from u to v (including u, v)
    vi path(int u, int v) {
        int l = this->operator()(u, v);
        vi ul, vl;
        while (l != u) {
            ul.pb(u);
            u = par[0][u];
        }
        while (l != v) {
            vl.pb(v);
            v = par[0][v];
        }
        ul.pb(l);
        ul.insert(ul.end(), rall(vl));
        return ul;
    }
};

class M {
public:
    using S = ;

    static constexpr S
    e =;

    // must be commutative
    static constexpr S

    op(const S &l, const S &r) {
        return;
    }
};