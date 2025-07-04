/*
  BECC becc(G);
  Graph tree = becc.to_tree();
  というように使う
*/

using Graph = std::vector<std::vector<int>>;
using Edge = std::pair<int, int>;

class BridgeHelper {
  const Graph& graph;
  std::vector<int> ord, low;
  int k = 0;

public:
  std::vector<Edge> bridges;

  BridgeHelper(const Graph& graph) : graph(graph), ord(graph.size(), -1), low(graph.size()) {
    for (int u = 0; u < graph.size(); ++u) {
      if (ord[u] >= 0) continue;
      dfs(u);
    }
  }
  bool is_bridge(int u, int v) const {
    if (ord[u] > ord[v]) std::swap(u, v);
    return ord[u] < low[v];
  }

private:
  void dfs(int u, int p = -1) {
    ord[u] = low[u] = k;
    ++k;
    for (int v : graph[u]) {
      if (v == p) continue;
      if (ord[v] >= 0) {
        low[u] = std::min(low[u], ord[v]);
      } else {
        dfs(v, u);
        low[u] = std::min(low[u], low[v]);
      }
      if (is_bridge(u, v)) bridges.emplace_back(u, v);
    }
  }
};

struct BECC {
  std::vector<std::vector<int>> comps;
  std::vector<int> belongs;
  const BridgeHelper bridge_helper;

private:
  const Graph& graph;

public:
  BECC(const Graph& graph) : graph(graph), bridge_helper(graph), belongs(graph.size(), -1) {
    for (const auto& bridge : bridge_helper.bridges) {
      add_component(bridge.first);
      add_component(bridge.second);
    }
    add_component(0);
  }
  Graph to_tree() const {
    Graph tree(comps.size());
    for (const auto& bridge : bridge_helper.bridges) {
      int u = belongs[bridge.first], v = belongs[bridge.second];
      tree[u].emplace_back(v);
      tree[v].emplace_back(u);
    }
    return tree;
  }

private:
  void fill_component(int c, int u) {
    comps[c].emplace_back(u);
    belongs[u] = c;
    for (int v : graph[u]) {
      if (belongs[v] >= 0) continue;
      if (bridge_helper.is_bridge(u, v)) continue;
      fill_component(c, v);
    }
  }
  void add_component(int u) {
    if (belongs[u] >= 0) return;
    comps.emplace_back();
    fill_component(comps.size() - 1, u);
  }
};