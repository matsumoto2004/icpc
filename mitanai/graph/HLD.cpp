// Heavy Light Decomposition
class HLD {
    vvi G;
    int n;
    vi sz, in, head, rev, par;
    
    void dfs_sz(int u, int p) {
        par[u] = p;
        sz[u] = 1;
        if (G[u].size() and G[u][0] == p) swap(G[u][0], G[u].back());
        for (int &v : G[u]) {
            if (v == p) continue;
            dfs_sz(v, u);
            sz[u] += sz[v];
            if (sz[G[u][0]] < sz[v]) swap(G[u][0], v);
        }
    }
    
    void dfs_hld(int u, int p, int &t) {
        in[u] = t++;
        rev[in[u]] = u;
        for (int v : G[u]) {
            if (v == p) continue;
            head[v] = (G[u][0] == v ? head[u] : v);
            dfs_hld(v, u, t);
        }
    }
    
    void init() {
        n = G.size();
        sz.resize(n);
        in.resize(n);
        head.resize(n);
        rev.resize(n);
        par.resize(n);
        dfs_sz(0, -1);
        int t = 0;
        dfs_hld(0, -1, t);
    }

public:
    HLD(const vvi &G) : G(G) {
        init();
    }
    
    // go up by k times from vertex v
    int la(int v, int k) {
        while (true) {
            int u = head[v];
            if (in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }
    
    int lca(int u, int v) {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) return u;
        }
    }

//    e -> identity element
//    q -> query to the line
//    f -> function to merge lines
//    q and f must be commutative i.e. q(l,r) = q(r,l)
//    set edge true for query to edges
    template<class T, class Q, class F>
    T fold(int u, int v, const T &e, const Q &q, const F &f, bool edge) {
        T l = e, r = e;
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v), swap(l, r);
            if (head[u] == head[v]) break;
            l = f(q(in[head[v]], in[v] + 1), l);
        }
        return f(f(q(in[u] + edge, in[v] + 1), l), r);
    }
    
    template<class F>
    void update(int u, int v, const F &f, bool edge) {
        for (;; v = par[head[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (head[u] == head[v]) break;
            f(in[head[v]], in[v] + 1);
        }
        f(in[u] + edge, in[v] + 1);
    }
    
    int get_id(int i) {
        return in[i];
    }
};