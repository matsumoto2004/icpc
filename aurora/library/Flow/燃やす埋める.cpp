template<class COST> struct TwoVariableSubmodularOpt {
    // edge class
    struct Edge {
        // core members
        int rev, from, to;
        COST cap, icap, flow;
        
        // constructor
        Edge(int r, int f, int t, COST c)
        : rev(r), from(f), to(t), cap(c), icap(c), flow(0) {}
        void reset() { cap = icap, flow = 0; }
        
        // debug
        friend ostream& operator << (ostream& s, const Edge& E) {
            return s << E.from << "->" << E.to << '(' << E.flow << '/' << E.icap << ')';
        }
    };
    
    // constructor
    TwoVariableSubmodularOpt() : N(2), S(0), T(0), OFFSET(0) {}
    TwoVariableSubmodularOpt(int n, COST inf = 0)
    : N(n), S(n), T(n + 1), OFFSET(0), INF(inf), list(n + 2) {}
    void init(int n, COST inf = 0) {
        N = n, S = n, T = n + 1;
        OFFSET = 0, INF = inf;
        list.assign(N + 2, Edge());
        pos.clear();
    }
    friend ostream& operator << (ostream& s, const TwoVariableSubmodularOpt &G) {
        const auto &edges = G.get_edges();
        for (const auto &e : edges) s << e << endl;
        return s;
    }

    // add 1-Variable submodular functioin
    void add_single_cost(int xi, COST false_cost, COST true_cost) {
        assert(0 <= xi && xi < N);
        if (false_cost >= true_cost) {
            OFFSET += true_cost;
            add_edge(S, xi, false_cost - true_cost);
        } else {
            OFFSET += false_cost;
            add_edge(xi, T, true_cost - false_cost);
        }
    }
    
    // add "project selection" constraint (xi = T, xj = F is penalty C)
    void add_psp_penalty(int xi, int xj, COST cost) {
        assert(0 <= xi && xi < N);
        assert(0 <= xj && xj < N);
        assert(cost >= 0);
        add_edge(xi, xj, cost);
    }
    
    // add general 2-variable submodular function
    // (xi, xj) = (F, F): A, (F, T): B
    // (xi, xj) = (T, F): C, (T, T): D
    void add_submodular_function(int xi, int xj, COST A, COST B, COST C, COST D) {
        assert(0 <= xi && xi < N);
        assert(0 <= xj && xj < N);
        assert(B + C >= A + D);  // assure submodular function
        OFFSET += A;
        add_single_cost(xi, 0, D - B);
        add_single_cost(xj, 0, B - A);
        add_psp_penalty(xi, xj, B + C - A - D);
    }
    
    // add all True profit
    void add_all_true_profit(const vector<int> &xs, COST profit) {
        assert(profit >= 0);
        int slack = (int)list.size();
        list.resize(slack + 1);
        OFFSET -= profit;
        add_edge(S, slack, profit);
        for (auto xi : xs) {
            assert(xi >= 0 && xi < N);
            add_edge(slack, xi, INF);
        }
    }
    
    // solve
    COST solve() {
        return dinic() + OFFSET;
    }
    vector<bool> reconstruct() {
        vector<bool> res(N, false), seen(list.size(), false);
        queue<int> que;
        seen[S] = true;
        que.push(S);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (const auto &e : list[v]) {
                if (e.cap && !seen[e.to]) {
                    if (e.to < N) res[e.to] = true;
                    seen[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return res;
    }
    
private:
    // inner data
    int N, S, T;
    COST OFFSET, INF;
    vector<vector<Edge>> list;
    vector<pair<int,int>> pos;
    
    // add edge
    Edge &get_rev_edge(const Edge &e) {
        if (e.from != e.to) return list[e.to][e.rev];
        else return list[e.to][e.rev + 1];
    }
    Edge &get_edge(int i) {
        return list[pos[i].first][pos[i].second];
    }
    const Edge &get_edge(int i) const {
        return list[pos[i].first][pos[i].second];
    }
    vector<Edge> get_edges() const {
        vector<Edge> edges;
        for (int i = 0; i < (int)pos.size(); ++i) {
            edges.push_back(get_edge(i));
        }
        return edges;
    }
    void add_edge(int from, int to, COST cap) {
        if (!cap) return;
        pos.emplace_back(from, (int)list[from].size());
        list[from].push_back(Edge((int)list[to].size(), from, to, cap));
        list[to].push_back(Edge((int)list[from].size() - 1, to, from, 0));
    }
    
    // Dinic's algorithm
    COST dinic(COST limit_flow) {
        COST current_flow = 0;
        vector<int> level((int)list.size(), -1), iter((int)list.size(), 0);
        
        // Dinic BFS
        auto bfs = [&]() -> void {
            level.assign((int)list.size(), -1);
            level[S] = 0;
            queue<int> que;
            que.push(S);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (const Edge &e : list[v]) {
                    if (level[e.to] < 0 && e.cap > 0) {
                        level[e.to] = level[v] + 1;
                        if (e.to == T) return;
                        que.push(e.to);
                    }
                }
            }
        };
        
        // Dinic DFS
        auto dfs = [&](auto self, int v, COST up_flow) {
            if (v == T) return up_flow;
            COST res_flow = 0;
            for (int &i = iter[v]; i < (int)list[v].size(); ++i) {
                Edge &e = list[v][i], &re = get_rev_edge(e);
                if (level[v] >= level[e.to] || e.cap == 0) continue;
                COST flow = self(self, e.to, min(up_flow - res_flow, e.cap));
                if (flow <= 0) continue;
                res_flow += flow;
                e.cap -= flow, e.flow += flow;
                re.cap += flow, re.flow -= flow;
                if (res_flow == up_flow) break;
            }
            return res_flow;
        };
        
        // flow
        while (current_flow < limit_flow) {
            bfs();
            if (level[T] < 0) break;
            iter.assign((int)iter.size(), 0);
            while (current_flow < limit_flow) {
                COST flow = dfs(dfs, S, limit_flow - current_flow);
                if (!flow) break;
                current_flow += flow;
            }
        }
        return current_flow;
    };
    COST dinic() {
        return dinic(numeric_limits<COST>::max());
    }
};