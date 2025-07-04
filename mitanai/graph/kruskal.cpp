struct edge {
    int x, y;
    ll cost;
    
    edge(int x, int y, ll cost) : x(x), y(y), cost(cost) {}
};

ll kruskal(int n, vector <edge> &v) {
    unionfind uf(n);
    sort(all(v), [](const edge &a, const edge &b) { return a.cost < b.cost; });
    ll ret = 0;
    for (auto e : v) {
        if (uf.same(e.x, e.y)) continue;
        uf.merge(e.x, e.y);
        ret += e.cost;
    }
    return ret;
}