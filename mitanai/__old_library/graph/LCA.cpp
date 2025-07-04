class LCA {
    int n;
    vvi G;
    vi dep;
    vvi par;
    
    void dfs(int u, int p, int d) {
        par[0][u] = p;
        dep[u] = d;
        for (int v: G[u]) if (v != p) dfs(v, u, d + 1);
    }
    
    void init() {
        n = G.size();
        dep.assign(n, -1);
        par.resize(30);
        rep(i, 30)
        par[i].resize(n);
        rep(i, n)
        if (dep[i] == -1) dfs(i, -1, 0);
        rep(k, 29)
        rep(i, n)
        {
            if (par[k][i] < 0) par[k + 1][i] = -1;
            else par[k + 1][i] = par[k][par[k][i]];
        }
    }
 
public:
    LCA(const vvi &G) : G(G) { init(); }
    
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