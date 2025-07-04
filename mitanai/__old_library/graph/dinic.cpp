template<typename T>
class dinic {
    struct edge {
        int to;
        T cap;
        int rev;
        
        edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
    };
    
    int n;
    vector <vector<edge>> G;
    vi level, iter;
    
    void bfs(int s) {
        level.assign(n, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : G[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    
    T dfs(int v, int t, T f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < (int) G[v].size(); i++) {
            auto &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
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
    explicit dinic(int n) : n(n), G(n), level(n), iter(n) {}
    
    void add_edge(int from, int to, T cap) {
        G[from].eb(to, cap, G[to].size());
        G[to].eb(from, 0, G[from].size() - 1);
    }
    
    // O(|E||V|^2)
    T max_flow(int s, int t) {
        T fl = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return fl;
            iter.assign(n, 0);
            T f;
            while ((f = dfs(s, t, numeric_limits<T>::max())) > 0) fl += f;
        }
    }
};