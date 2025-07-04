vi topological_sort(const vvi &G) {
    int n = G.size();
    vi in(n);
    rep(i, n)
    for (int j : G[i]) in[j]++;
    queue<int> q;
    rep(i, n)
    if (!in[i]) q.push(i);
    vi res;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res.pb(u);
        for (int v : G[u]) {
            if (--in[v] == 0) q.push(v);
        }
    }
    return res;
}