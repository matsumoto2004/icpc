class lowlink {
    vvi G;
    vi ord, low;
    
    int dfs(int u, int p, int k) {
        ord[u] = low[u] = k++;
        bool flag = false;
        int cnt = 0;
        for (int v: G[u]) {
            if (ord[v] < 0) {
                cnt++;
                k = dfs(v, u, k);
                chmin(low[u], low[v]);
                flag |= p >= 0 and ord[u] <= low[v];
                if (ord[u] < low[v]) bridge.eb(u, v);
            } else if (v != p) {
                chmin(low[u], ord[v]);
            }
        }
        flag |= p < 0 and cnt > 1;
        if (flag) articulation.pb(u);
        return k;
    }
    
    void init() {
        ord.assign(G.size(), -1);
        low.assign(G.size(), -1);
        int k = 0;
        rep(i, G.size()) {
            if (ord[i] < 0) k = dfs(i, -1, k);
        }
    }

public:
    vi articulation;
    vp bridge;
    
    lowlink(const vvi &G) : G(G) { init(); }
};