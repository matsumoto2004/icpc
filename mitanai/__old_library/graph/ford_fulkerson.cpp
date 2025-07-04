template<typename T>
class ford_fulkerson {
    struct edge {
        int to;
        T cap;
        int rev;
        
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
    
    int n;
    vector<vector<edge>> G;
    vb used;
    
    T dfs(int v, int t, T f) {
        if (v == t) return f;
        used[v] = true;
        rep(i, G[v].size()) {
            edge &e = G[v][i];
            if (e.cap > 0 && !used[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
 
public:
    explicit ford_fulkerson(int n) : n(n), G(n), used(n) {}
    
    void add_edge(int from, int to, T cap) {
        G[from].eb(to, cap, G[to].size());
        G[to].eb(from, 0, G[from].size() - 1);
    }
    
    T max_flow(int s, int t) {
        T fl = 0;
        while (true) {
            used.assign(n, false);
            T f = dfs(s, t, inf);
            if (f == 0) return fl;
            fl += f;
        }
    }
};