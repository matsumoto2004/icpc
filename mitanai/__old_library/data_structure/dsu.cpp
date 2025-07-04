class dsu {
    int n;
    vector<int> par, rank;
public:
    dsu(int n) : n(n), par(n, -1), rank(n, 0) {}
    
    int leader(int x) {
        if (par[x] < 0) return x;
        else return par[x] = leader(par[x]);
    }
    
    bool is_leader(int x) { return leader(x) == x; }
    
    bool same(int x, int y) { return leader(x) == leader(y); };
    
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y);
        if (rank[x] == rank[y]) rank[x]++;
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) { return -par[leader(x)]; };
    
    vi leaders() {
        vi res;
        rep(i, n) if (leader(i) == i) res.pb(i);
        return res;
    }
    
    bool connected() {
        return leaders().size() == 1;
    }
};
