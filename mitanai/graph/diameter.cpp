// G is the tree
// can calc diameter by "dfs(dfs(0).second).first"
P dfs(const vvi &G, int u, int p = -1) {
    int res = 0, ind = u;
    for (int v : G[u]) {
        if (v == p) continue;
        auto d = dfs(G, v, u);
        if (chmax(res, d.first + 1)) ind = d.second;
    }
    return {res, ind};
}