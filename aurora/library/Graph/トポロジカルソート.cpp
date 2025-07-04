vector<int> topso(int N,vector<vector<int>> G){ //トポロジカルソートされた配列を返す
    vector<int> order;
  
    vector<int> deg(N);
    for(int v=0;v<N;v++) for(auto nv:G[v]) deg[nv]++;
    
    queue<int> que;
    for(int i=0;i<N;i++) if(deg[i] == 0) que.push(i);
    
    while(!que.empty()){
      int v = que.front();
      que.pop();
      order.push_back(v);
      for(auto nv:G[v]){
        deg[nv]--;
        if(deg[nv] == 0){
          que.push(nv);
        }
      }
    }
    
    return order;
  }