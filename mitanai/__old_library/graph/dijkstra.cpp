// (to, len)
using vve = vector <vector<pair < int, ll>>>;

vl dijkstra(const vve &G, int start) {
    int sz = G.size();
    vl dist(sz, linf);
    PQ <ll> q;
    q.emplace(0, start);
    dist[start] = 0;
    while (!q.empty()) {
        auto[d, u] = q.top();
        q.pop();
        if (dist[u] < d) continue;
        for (auto[v, len]: G[u]) {
            if (chmin(dist[v], d + len)) {
                q.emplace(d + len, v);
            }
        }
    }
    return dist;
}