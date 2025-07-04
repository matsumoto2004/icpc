vector<int> diameter_of_tree(vector<vector<int>> G){
    int N = G.size();
    int a = 0;
    vector<int> dista(N,-1);
    dista[a] = 0;
    queue<int> que;
    que.push(a);
    while(!que.empty()){
      int v = que.front();
      que.pop();
      for(auto nv:G[v]){
        if(dista[nv] == -1){
          dista[nv] = dista[v]+1;
          que.push(nv);
        }
      }
    }
    int dmaxa = 0;
    for(int i=0;i<N;i++) dmaxa = max(dmaxa,dista[i]);
    int b;
    for(int i=0;i<N;i++) if(dmaxa == dista[i]) b = i;
    vector<int> distb(N,-1);
    distb[b] = 0;
    que.push(b);
    while(!que.empty()){
      int v = que.front();
      que.pop();
      for(auto nv:G[v]){
        if(distb[nv] == -1){
          distb[nv] = distb[v]+1;
          que.push(nv);
        }
      }
    }
    int dmaxb = 0;
    for(int i=0;i<N;i++) dmaxb = max(dmaxb,distb[i]);
    int c;
    for(int i=0;i<N;i++) if(dmaxb == distb[i]) c = i;
    vector<int> res(1,c);
    int nowv = c;
    while(nowv != b){
      for(auto nv:G[nowv]){
        if(distb[nv] == distb[nowv]-1){
          res.push_back(nv);
          nowv = nv;
          break;
        }
      }
    }
    return res;
  }