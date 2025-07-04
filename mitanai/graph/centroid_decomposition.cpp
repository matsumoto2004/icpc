// ref : https://kopricky.github.io/code/GraphDecomposition/centroid_decomposition.html
class centroid_decomposition {
private:
    int n;
    vector <vector<int>> G;
    // sz : 重心分解後の最大部分木に含まれる頂点の数(自分を含める)
    vector<int> sz;

    // 部分木のサイズを計算
    void calcSize(int u, int p) {
        sz[u] = 1;
        for (int v: G[u]) {
            if (dep[v] == -1 && v != p) {
                calcSize(v, u);
                sz[u] += sz[v];
            }
        }
    }

    void cdBuild(int u, int p, int d) {
        calcSize(u, -1);
        int tot = sz[u];
        bool ok = false;
        int pp = -1;
        // いま見ている部分木での重心を見つける
        while (!ok) {
            ok = true;
            for (int v: G[u]) {
                if (dep[v] == -1 && v != pp && 2 * sz[v] > tot) {
                    pp = u, u = v, ok = false;
                    break;
                }
            }
        }
        par[u] = p;
        dep[u] = d;
        //深さ優先でたどる
        for (int v: G[u]) {
            if (dep[v] == -1) {
                cdBuild(v, u, d + 1);
            }
        }
    }

public:
    centroid_decomposition(const vvi &G) : n(SZ(G)), G(G), sz(n), par(n, -1), dep(n, -1) {
        cdBuild(0, -1, 0);
    }

    // par : 重心分解後の親の頂点
    vector<int> par;
    // dep : cdtree 上での深さ
    vector<int> dep;

    // 重心分解の過程を表す根付き木
    // return {Graph, Root}
    pair<vvi, int> cdtree() {
        vvi res(n);
        int r;
        rep(i, n)
        {
            if (par[i] != -1) res[par[i]].pb(i);
            else r = i;
        }
        return {res, r};
    }
};