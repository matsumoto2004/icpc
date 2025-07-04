template<class D>
class rerooting {
    using T = typename D::T;

    int n;
    vvi tree;
    vector<vector<T>> dp;
    vector<T> ans;

    T dfs(int u = 0, int p = -1) {
        T sum = D::id;
        dp[u].resize(tree[u].size());
        rep(i, tree[u].size()) {
            int v = tree[u][i];
            if (v == p) continue;
            dp[u][i] = dfs(v, u);
            sum = D::merge(sum, D::add_root(dp[u][i], v, u));
        }
        return sum;
    }

    void dfs2(T dpP, int u = 0, int p = -1) {
        int sz = tree[u].size();
        rep(i, sz) if (tree[u][i] == p) dp[u][i] = dpP;
        vector<T> sumL(sz + 1, D::id), sumR(sz + 1, D::id);
        rep(i, sz) sumL[i + 1] = D::merge(sumL[i], D::add_root(dp[u][i], tree[u][i], u));
        rrep(i, sz) sumR[i] = D::merge(sumR[i + 1], D::add_root(dp[u][i], tree[u][i], u));
        ans[u] = D::add_root(sumL[sz], u, -1);
        rep(i, sz) {
            int v = tree[u][i];
            if (v == p) continue;
            T t = D::merge(sumL[i], sumR[i + 1]);
            dfs2(t, v, u);
        }
    }

public:
    explicit rerooting(const vvi &tree) : n(tree.size()), tree(tree), dp(n), ans(n) {
        dfs();
        dfs2(D::id);
    };

    T get_ans(int i) {
        return ans[i];
    }
};

struct D {
    using T = ;

    static const T id = ;

    static T merge(const T &a, const T &b) {
        return ;
    }

    // u : root, p : parent of u
    static T add_root(const T &a, [[maybe_unused]] int u, [[maybe_unused]] int p) {
        return ;
    }
};