class SCC {
    int n;
    vvi G;
    vi ord, low;
    stack<int> st;

    void dfs(int u, int &k) {
        ord[u] = low[u] = k++;
        st.push(u);
        for (int v: G[u]) {
            if (ord[v] == -1) {
                dfs(v, k);
                chmin(low[u], low[v]);
            } else {
                chmin(low[u], ord[v]);
            }
        }
        if (low[u] == ord[u]) {
            while (true) {
                int now = st.top();
                st.pop();
                ord[now] = inf;
                id[now] = num;
                if (now == u) break;
            }
            ++num;
        }
    }

public:
    // number of components
    int num;
    vi id;
    vvi scc_list;

    SCC(const vvi &G) : G(G) {
        n = G.size();
        ord.assign(n, -1);
        low.resize(n);
        id.resize(n);
        num = 0;
        int k = 0;
        rep(i, n)
        if (ord[i] == -1) dfs(i, k);
        vi cnt(num);
        rep(i, n)
        {
            id[i] = num - 1 - id[i];
            ++cnt[id[i]];
        }
        scc_list.resize(num);
        rep(i, num)
        scc_list[i].reserve(cnt[i]);
        rep(i, n)
        scc_list[id[i]].pb(i);
    }
};