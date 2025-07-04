struct UnionFind{ //グラフの連結性を管理
    vector<int> par,siz;
    UnionFind(int n):par(n,-1),siz(n,1){}
    
    int root(int x){ //頂点xが属する連結成分の代表点を求める
      if(par[x] == -1) return x;
      else return par[x] = root(par[x]);
    }
    bool issame(int x,int y){ //頂点x,yが同じ連結成分に属しているか
      if(root(x) == root(y)) return true;
      else return false;
    }
    bool unite(int x,int y){ //頂点x,yを辺で結ぶ
      x = root(x);
      y = root(y);
      if(x == y) return false;
      if(siz[x] < siz[y]) swap(x,y);
      par[y] = x;
      siz[x] += siz[y];
      return true;
    }
    int size(int x){ //頂点xが属する連結成分の大きさを求める
      return siz[root(x)];
    }
  };