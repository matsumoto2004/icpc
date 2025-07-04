const long long int zero = 0;
 
struct Slope_Trick{
  priority_queue<long long int,vector<long long int>,less<long long int>> L;
  priority_queue<long long int,vector<long long int>,greater<long long int>> R;
  long long int addL,addR,miny;
  Slope_Trick():addL(0),addR(0),miny(0){}
  pair<long long int,pair<long long int,long long int>> query(){ //最小値とそれを与える区間
    return make_pair(miny,make_pair(L.top()+addL,R.top()+addR));
  }
  void add_all(long long int a){ //全体に定数を加算
    miny += a;
  }
  void add_maxx(long long int a){ //max(0,x-a)を加える
    if(!L.empty()){
      long long int l = L.top()+addL;
      miny += max(zero,l-a);
    }
    L.push(a-addL);
    R.push(L.top()+addL-addR);
    L.pop();
  }
  void add_maxa(long long int a){ //max(0,a-x)を加える
    if(!R.empty()){
      long long int r = R.top()+addR;
      miny += max(zero,a-r);
    }
    R.push(a-addR);
    L.push(R.top()+addR-addL);
    R.pop();
  }
  void add_abs(long long int a){ //|x-a|を加える
    add_maxx(a);
    add_maxa(a);
  }
  void acu_min(){ //g(x)=minf(y)(y<=x)
    while(!R.empty()) R.pop();
  }
  void right_acu_min(){ //g(x)=minf(y)(y>=x)
    while(!L.empty()) L.pop();
  }
  void shift(long long int a){ //g(x)=f(x-a)
    addL += a;
    addR += a;
  }
  void slide_min(long long int a,long long int b){ //g(x)=minf(y)(x-b<=y<=x-a)
    addL += a;
    addR += b;
  }
};