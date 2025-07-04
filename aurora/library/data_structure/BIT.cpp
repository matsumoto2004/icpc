struct Binary_Indexed_Tree{ //i番目の要素にxを加算することができ、区間[i,j](1≦i≦j≦n)の和が求められる
    ll n;
    vl bit;
    Binary_Indexed_Tree(int N):bit(N+1,0){}
    
    void build(int N,vl A){ //BITの大きさと初期値を設定する
      n = N;
      rep2(j,1,n+1){
        int i = j;
        while(i <= n){
          bit[i] += A[j-1];
          i += i&-i;
        }
      }
    }
    
    ll sum(int i){ //区間[1,i]の和を求める
      ll s = 0;
      while(i > 0){
        s += bit[i];
        i -= i&-i;
      }
      return s;
    }
    
    ll sum2(int i,int j){ //区間[i,j]の和を求める
      return sum(j)-sum(i-1);
    }
    
    void add(int i,ll x){ //A_iにxを加える
      while(i <= n){
        bit[i] += x;
        i += i&-i;
      }
    }
  };