template<class Cap, class Cost>
class MCF {
    struct _edge {
        int to, rev;
        Cap cap;
        Cost cost;
        
        _edge(int to, int rev, Cap cap, Cost cost) : to(to), rev(rev), cap(cap), cost(cost) {}
    };
    
    int n;
    vp pos;
    vector <vector<_edge>> G;

public:
    explicit MCF(int n) : n(n), G(n) {}
    
    int add_edge(int from, int to, Cap cap, Cost cost) {
        assert(0 <= from and from < n);
        assert(0 <= to and to < n);
        assert(from != to);
        pos.eb(from, G[from].size());
        G[from].eb(to, G[to].size(), cap, cost);
        G[to].eb(from, G[from].size() - 1, 0, -cost);
        return pos.size() - 1;
    }
    
    struct edge {
        int from, to;
        Cap cap, flow;
        Cost cost;
        
        edge(int from, int to, Cap cap, Cap flow, Cost cost) : from(from), to(to), cap(cap), flow(flow), cost(cost) {}
    };
    
    edge get_edge(int i) {
        assert(0 <= i && i < int(pos.size()));
        auto e = G[pos[i].first][pos[i].second];
        auto re = G[e.to][e.rev];
        return edge(pos[i].first, e.to, e.cap + re.cap, re.cap, e.cost);
    }
    
    vector <edge> edges() {
        int m = pos.size();
        vector <edge> res(m);
        rep(i, m)
        res[i] = get_edge(i);
        return res;
    }
    
    pair <Cap, Cost> flow(int s, int t) {
        return flow(s, t, numeric_limits<Cap>::max());
    }
    
    pair <Cap, Cost> flow(int s, int t, Cap flow_limit) {
        return slope(s, t, flow_limit).back();
    }
    
    vector <pair<Cap, Cost>> slope(int s, int t) {
        return slope(s, t, numeric_limits<Cap>::max());
    }
    
    // this must not be called more than once
    // O(F (E + V) log V)
    vector <pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
        assert(0 <= s and s < n);
        assert(0 <= t and t < n);
        assert(s != t);
        // variants (C = maxcost):
        // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0
        // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all _edge
        vector <Cost> dual(n, 0), dist(n);
        vi pv(n), pe(n);
        vb seen(n);
        auto dual_ref = [&]() -> bool {
            fill(all(dist), numeric_limits<Cost>::max());
            fill(all(pv), -1);
            fill(all(pe), -1);
            fill(all(seen), false);
            priority_queue < pair < Cost, int >, vector < pair < Cost, int >>, greater < pair < Cost, int>>> q;
            dist[s] = 0;
            q.emplace(0, s);
            while (not q.empty()) {
                int u = q.top().second;
                q.pop();
                if (seen[u]) continue;
                seen[u] = true;
                if (u == t) break;
                // dist[u] = shortest(s, u) + dual[s] - dual[u]
                // dist[u] >= 0 (all reduced cost are positive)
                // dist[u] <= (n-1)C
                rep(i, G[u].size())
                {
                    auto e = G[u][i];
                    if (seen[e.to] or !e.cap) continue;
                    // |-dual[e.to] + dual[u]| <= (n-1)C
                    // cost <= C - -(n-1)C + 0 = nC
                    Cost cost = e.cost - dual[e.to] + dual[u];
                    if (chmin(dist[e.to], dist[u] + cost)) {
                        pv[e.to] = u;
                        pe[e.to] = i;
                        q.emplace(dist[e.to], e.to);
                    }
                }
            }
            if (!seen[t]) {
                return false;
            }
            
            rep(u, n)
            {
                if (!seen[u]) continue;
                // dual[u] = dual[u] - dist[t] + dist[u]
                //         = dual[u] - (shortest(s, t) + dual[s] - dual[t]) + (shortest(s, u) + dual[s] - dual[u])
                //         = - shortest(s, t) + dual[t] + shortest(s, v)
                //         = shortest(s, v) - shortest(s, t) >= 0 - (n-1)C
                dual[u] -= dist[t] - dist[u];
            }
            return true;
        };
        Cap flow = 0;
        Cost cost = 0, prev_cost_per_flow = -1;
        vector <pair<Cap, Cost>> res;
        res.eb(flow, cost);
        while (flow < flow_limit) {
            if (!dual_ref()) break;
            Cap c = flow_limit - flow;
            for (int u = t; u != s; u = pv[u]) {
                chmin(c, G[pv[u]][pe[u]].cap);
            }
            for (int u = t; u != s; u = pv[u]) {
                auto &e = G[pv[u]][pe[u]];
                e.cap -= c;
                G[u][e.rev].cap += c;
            }
            Cost d = -dual[s];
            flow += c;
            cost += c * d;
            if (prev_cost_per_flow == d) {
                res.pop_back();
            }
            res.eb(flow, cost);
            prev_cost_per_flow = d;
        }
        return res;
    }
    
};