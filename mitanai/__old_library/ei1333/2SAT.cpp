template <typename T = int>
struct Edge {
  int from, to;
  T cost;
  int idx;

  Edge() = default;

  Edge(int from, int to, T cost = 1, int idx = -1)
      : from(from), to(to), cost(cost), idx(idx) {}

  operator int() const { return to; }
};

template <typename T = int>
struct Graph {
  vector<vector<Edge<T> > > g;
  int es;

  Graph() = default;

  explicit Graph(int n) : g(n), es(0) {}

  size_t size() const { return g.size(); }

  void add_directed_edge(int from, int to, T cost = 1) {
    g[from].emplace_back(from, to, cost, es++);
  }

  void add_edge(int from, int to, T cost = 1) {
    g[from].emplace_back(from, to, cost, es);
    g[to].emplace_back(to, from, cost, es++);
  }

  void read(int M, int padding = -1, bool weighted = false,
            bool directed = false) {
    for (int i = 0; i < M; i++) {
      int a, b;
      cin >> a >> b;
      a += padding;
      b += padding;
      T c = T(1);
      if (weighted) cin >> c;
      if (directed)
        add_directed_edge(a, b, c);
      else
        add_edge(a, b, c);
    }
  }

  inline vector<Edge<T> > &operator[](const int &k) { return g[k]; }

  inline const vector<Edge<T> > &operator[](const int &k) const { return g[k]; }
};

template <typename T = int>
using Edges = vector<Edge<T> >;

//

template <typename T = int>
struct StronglyConnectedComponents : Graph<T> {
 public:
  using Graph<T>::Graph;
  using Graph<T>::g;
  vector<int> comp;
  Graph<T> dag;
  vector<vector<int> > group;

  void build() {
    rg = Graph<T>(g.size());
    for (size_t i = 0; i < g.size(); i++) {
      for (auto &e : g[i]) {
        rg.add_directed_edge(e.to, e.from, e.cost);
      }
    }
    comp.assign(g.size(), -1);
    used.assign(g.size(), 0);
    for (size_t i = 0; i < g.size(); i++) dfs(i);
    reverse(begin(order), end(order));
    int ptr = 0;
    for (int i : order)
      if (comp[i] == -1) rdfs(i, ptr), ptr++;
    dag = Graph<T>(ptr);
    for (size_t i = 0; i < g.size(); i++) {
      for (auto &e : g[i]) {
        int x = comp[e.from], y = comp[e.to];
        if (x == y) continue;
        dag.add_directed_edge(x, y, e.cost);
      }
    }
    group.resize(ptr);
    for (size_t i = 0; i < g.size(); i++) {
      group[comp[i]].emplace_back(i);
    }
  }

  int operator[](int k) const { return comp[k]; }

 private:
  vector<int> order, used;
  Graph<T> rg;

  void dfs(int idx) {
    if (exchange(used[idx], true)) return;
    for (auto &to : g[idx]) dfs(to);
    order.push_back(idx);
  }

  void rdfs(int idx, int cnt) {
    if (comp[idx] != -1) return;
    comp[idx] = cnt;
    for (auto &to : rg.g[idx]) rdfs(to, cnt);
  }
};

//

struct TwoSatisfiability : StronglyConnectedComponents<bool> {
 public:
  using StronglyConnectedComponents<bool>::g;
  using StronglyConnectedComponents<bool>::comp;
  using StronglyConnectedComponents<bool>::add_edge;
  size_t sz;

  explicit TwoSatisfiability(size_t v)
      : StronglyConnectedComponents<bool>(v + v), sz(v) {}

  void add_if(int u, int v) {
    // u -> v <=> !v -> !u
    add_directed_edge(u, v);
    add_directed_edge(rev(v), rev(u));
  }

  void add_or(int u, int v) {
    // u or v <=> !u -> v
    add_if(rev(u), v);
  }

  void add_nand(int u, int v) {
    // u nand v <=> u -> !v
    add_if(u, rev(v));
  }

  void set_true(int u) {
    // u <=> !u -> u
    add_directed_edge(rev(u), u);
  }

  void set_false(int u) {
    // !u <=> u -> !u
    add_directed_edge(u, rev(u));
  }

  inline int rev(int x) {
    if (x >= (int)sz) return x - sz;
    return x + sz;
  }

  vector<int> solve() {
    StronglyConnectedComponents<bool>::build();
    vector<int> ret(sz);
    for (size_t i = 0; i < sz; i++) {
      if (comp[i] == comp[rev(i)]) return {};
      ret[i] = comp[i] > comp[rev(i)];
    }
    return ret;
  }
};