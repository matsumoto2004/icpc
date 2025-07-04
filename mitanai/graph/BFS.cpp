vi BFS(const vvi &G, int start) {
    int n = G.size();
    vi dist(n, inf);
    dist[start] = 0;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : G[u]) {
            if (chmin(dist[v], dist[u] + 1)) q.push(v);
        }
    }
    return dist;
}