template<typename T>
class weighted_unionfind {
    int n;
    vi par, rank;
    vector <T> diff_weight;
public:
    weighted_unionfind(int n) : n(n), par(n, -1), rank(n, 0), diff_weight(n, 0) {}
    
    int root(int x) {
        if (par[x] < 0) return x;
        else {
            int r = root(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }
    
    T weight(int x) {
        root(x);
        return diff_weight[x];
    }
    
    bool is_root(int x) { return root(x) == x; }
    
    bool same(int x, int y) { return root(x) == root(y); }
    
    bool merge(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y), w = -w;
        if (rank[x] == rank[y]) rank[x]++;
        par[x] += par[y];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }
    
    T diff(int x, int y) {
        assert(same(x, y));
        return weight(y) - weight(x);
    }
    
    vi roots() {
        vi res;
        rep(i, n)
        if (root(i) == i) res.pb(i);
        return res;
    }
    
    bool connected() {
        return roots().size() == 1;
    }
};