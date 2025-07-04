struct edge {
    int a, b; // from a to b
    ll len;

    edge(int a, int b, ll l) : a(a), b(b), len(l) {}
};

// return value is {} if there is a negative cycle.
/* detect only if a certain node(goal) is reachable
      from a negative cycle (if goal != -1) */
// detect any negative cycles (if goal == -1)
vector <ll> bellman_ford(int n, const vector <edge> &v, int start, int goal = -1) {
    vector <ll> dist(n, linf);
    dist[start] = 0;
    if (goal == -1) {
        rep(i, n)
        {
            for (auto e: v) {
                if (dist[e.a] < linf && chmin(dist[e.b], dist[e.a] + e.len)) {
                    if (i == n - 1) return {};
                }
            }
        }
    } else {
        rep(i, n * 2)
        {
            for (auto e: v) {
                if (dist[e.a] < linf && chmin(dist[e.b], dist[e.a] + e.len)) {
                    if (i >= n - 1 && e.b == goal) return {};
                    else if (i >= n - 1) dist[e.b] = -linf;
                }
            }
        }
    }
    return dist;
}