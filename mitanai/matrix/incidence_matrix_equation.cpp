// solve Bx = c  where B is an incidence matrix of a graph
// return void vector if there is no answer
template<class T, bool mod2 = false>
vector<T> incidence_matrix_equation(int n, const vp &edge, const vector<T> &c) {
    assert(c.size() == n);

    struct Edge {
        int id, to;
        bool fwd;

        Edge(int id, int to, bool fwd) : id(id), to(to), fwd(fwd) {}
    };

    vector<vector<Edge>> G(n);
    rep(i, edge.size()) {
        P p = edge[i];
        G[p.first].eb(i, p.second, true);
        G[p.second].eb(i, p.first, false);
    }

    vector<T> ans(edge.size());
    vb seen(n);

    auto dfs = [&](auto &self, int v) -> T {
        seen[v] = true;
        T res = c[v];
        for (Edge e : G[v]) {
            if (seen[e.to]) continue;
            T d = self(self, e.to);
            if (e.fwd) ans[e.id] = d;
            else ans[e.id] = -d;
            res += d;
            if (mod2) (ans[e.id] += 2) %= 2;
        }
        if (mod2) (res += 2) %= 2;
        return res;
    };

    rep(i, n) {
        if (seen[i]) continue;
        T y = dfs(dfs, i);
        if (y != 0) return {};
    }

    return ans;
};