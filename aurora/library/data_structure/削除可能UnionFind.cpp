template <class S, S (*op)(S, S), S (*e)()>
struct UndoableUnionFind{
  int num;
  vector<int> data;
  vector<S> val;
  stack<tuple<int,int,S>> hist;
  UndoableUnionFind() = default;
  explicit UndoableUnionFind(int N) : num(N), data(N, -1), val(N, e()){}
  explicit UndoableUnionFind(const vector<S>& v) : num(v.size()), data(num, -1), val(v){}
  int root(int x){ return data[x] < 0 ? x : root(data[x]); }
  bool unite(int x,int y){
    x = root(x); y = root(y);
    hist.emplace(-1, num, e());
    hist.emplace(x, data[x], val[x]);
    hist.emplace(y, data[y], val[y]);
    if(x==y) return false;
    if(data[x] > data[y]) swap(x, y);
    data[x] += data[y];
    data[y] = x;
    val[x] = op(val[x], val[y]);
    return true;
  }
  int size(int x){ return -data[root(x)]; }
  bool same(int x,int y){ return root(x) == root(y); }
  bool undo(){
    if(!hist.size()) return false;
    while(1){
      auto [x, y, z] = hist.top();
      hist.pop();
      if(x < 0){
        num = y;
        break;
      }
      data[x] = y, val[x] = z;
    }
    return true;
  }
  S prod(int x){ return val[root(x)]; }
  void update(int x, const S& v){
    x = root(x);
    hist.emplace(-1, num, e());
    hist.emplace(x, data[x], val[x]);
    val[x] = op(val[x], v);
  }
};

template <class S, S (*op)(S, S), S (*e)(), class T = int>
struct OfflineDynamicConnectivity{
  int time = 0;
  bool exist_edge = true;
  map<pair<int,int>, pair<int,T>> contain_edge;
  map<pair<int,int>, T> lazy_edge;
  vector<tuple<int,int,int,int>> edge_range; // u, v, [l, r)
  vector<pair<int, int>> query;
  vector<tuple<int, S, int>> query_update; // v, x, l
  vector<int> until_query;
  vector<S> val;

  OfflineDynamicConnectivity() = default;
  explicit OfflineDynamicConnectivity(int N) : val(N, e()){}
  explicit OfflineDynamicConnectivity(const vector<S>& v) : val(v){}

  void traversal_edge(){
    if(!exist_edge) return;
    exist_edge = false;
    for(auto& [p,q]:lazy_edge){
      if(!contain_edge.count(p)){
        if(q>0) contain_edge[p] = {time, q};
      }
      else{
        auto& x = contain_edge[p];
        x.second += q;
        if(x.second<=0){
          edge_range.emplace_back(p.first, p.second, x.first, time);
          contain_edge.erase(p);
        }
      }
    }
    lazy_edge.clear();
  }
  void traversal_query(){
    if(exist_edge) return;
    exist_edge = true;
    until_query.emplace_back(query.size());
    ++time;
  }
  void edge_sub(int u, int v, T x){
    if(!x) return;
    traversal_query();
    lazy_edge[minmax(u,v)] += x;
  }
  void add_edge(int u, int v){ edge_sub(u, v, 1); }
  void erase_edge(int u, int v){ edge_sub(u, v, -1); }
  void update(int v, S x){
    if(x==e()) return;
    traversal_query();
    query_update.emplace_back(v, x, time);
  }

  // same:(u,v) size:(-1,v) num:(-1,-1) prod:(-2,v)
  void same(int u, int v){
    traversal_edge();
    query.emplace_back(u, v);
  }
  void size(int v){
    traversal_edge();
    query.emplace_back(-1, v);
  }
  void num(){
    traversal_edge();
    query.emplace_back(-1, -1);
  }
  void prod(int v){
    traversal_edge();
    query.emplace_back(-2, v);
  }

  // first:same,size,num second:prod
  vector<pair<int, S>> run(){
    ++time;
    until_query.emplace_back(query.size());
    for(auto& [p,q]:contain_edge) edge_range.emplace_back(p.first, p.second, q.first, time);
    int size = bit_ceil((unsigned int)time);
    vector<vector<pair<int, int>>> edges(2*size);
    vector<vector<pair<int, S>>> updates(2*size);
    for(auto [u,v,l,r]:edge_range){
      for(l+=size,r+=size;l<r;l>>=1,r>>=1){
        if(l&1) edges[l++].emplace_back(u,v);
        if(r&1) edges[--r].emplace_back(u,v);
      }
    }
    for(auto [v,x,l]:query_update){
      int r = size;
      for(l+=size,r+=size;l<r;l>>=1,r>>=1){
        if(l&1) updates[l++].emplace_back(v,x);
        if(r&1) updates[--r].emplace_back(v,x);
      }
    }
    UndoableUnionFind<S, op, e> uf(val);
    vector<pair<int, S>> res;
    int now = 0;
    auto dfs = [&](const auto& self, int k) -> void {
      for(auto [u,v]:edges[k]){ uf.unite(u,v); }
      for(auto [v,x]:updates[k]){ uf.update(v,x); }
      if(k < size){
        self(self, 2*k);
        self(self, 2*k+1);
      }
      else{
        int m = k - size;
        if(m < (int)until_query.size()){
          for(;now<until_query[m];++now){
            auto [u,v] = query[now];
            if(u==-1) res.emplace_back(v<0?uf.num:uf.size(v), e());
            else if(u==-2) res.emplace_back(-1, uf.prod(v));
            else res.emplace_back(uf.same(u,v), e());
          }
        }
      }
      int m = edges[k].size() + updates[k].size() + 1;
      while(--m) uf.undo();
    };
    dfs(dfs, 1);
    return res;
  }
};

ll op(ll a, ll b){ return a+b; }
ll e(){ return 0; }

/*OfflineDynamicConnectivity<ll,op,e> dc(A); //Aは配列(重み)
dc.add_edge(x,y)辺追加
dc.erase_edge(x,y)辺削除
dc.prod(x)連結成分重み計算
最後にこれしてprodの答え列挙
auto ans = dc.run();
for(auto [p,q]:ans) cout << q << endl; */