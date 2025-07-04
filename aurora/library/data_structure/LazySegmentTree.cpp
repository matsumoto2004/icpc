/*遅延セグメントツリー
X:セグメントに入れる値の型
M:作用させるものの型
fx:セグメントどうしの結合
fa:XにMを作用させるとき
fm:Mが追加されたとき
ex:Xの単位元
em:Mの単位元

RSQだったらこうする
using X = long long;
using M = long long;
auto fx = [](X x1, X x2) -> X { return x1 + x2; };
auto fa = [](X x, M m) -> X { return x + m; };
auto fm = [](M m1, M m2) -> M { return m1 + m2; };
long long ex = 0;
long long em = 0;
SegTreeLazy<X, M> rsq(n,fx,fa,fm,ex,em);
*/
template <typename X, typename M>
struct SegTreeLazy {
  using FX = function<X(X,X)>;
  using FA = function<X(X,M)>;
  using FM = function<M(M,M)>;
  int n;
  FX fx;
  FA fa;
  FM fm;
  const X ex;
  const M em;
  vector<X> dat;
  vector<M> lazy;
  SegTreeLazy(int n_,FX fx_,FA fa_, FM fm_, X ex_, M em_)
    : n(), fx(fx_), fa(fa_), fm(fm_), ex(ex_), em(em_), dat(n_ * 4, ex), lazy(n_ * 4, em) {
    int x = 1;
    while(n_ > x) x *= 2;
    n = x;
  }
  void set(int i, X x) { dat[i+n-1] = x; }
  void build(){
    for(int k=n-2;k>=0;k--) dat[k] = fx(dat[2*k+1],dat[2*k+2]);
  }
  void eval(int k){
    if(lazy[k] == em) return;
    if(k < n-1){
      lazy[k*2+1] = fm(lazy[k*2+1],lazy[k]);
      lazy[k*2+2] = fm(lazy[k*2+2],lazy[k]);
    }
    dat[k] = fa(dat[k],lazy[k]);
    lazy[k] = em;
  }
  void update(int a,int b,M x,int k,int l,int r){
    eval(k);
    if(a <= l && r <= b){
      lazy[k] = fm(lazy[k],x);
      eval(k);
    } 
    else if(a < r && l < b){
      update(a,b,x,k*2+1,l,(l+r)/2);
      update(a,b,x,k*2+2,(l+r)/2,r);
      dat[k] = fx(dat[k*2+1],dat[k*2+2]);
    }
  }
  void update(int a,int b,M x) { update(a,b,x,0,0,n); }
  X query_sub(int a,int b,int k,int l,int r) {
    eval(k);
    if(r <= a || b <= l){
      return ex;
    } 
    else if(a <= l && r <= b){
      return dat[k];
    } 
    else{
      X vl = query_sub(a,b,k*2+1,l,(l+r)/2);
      X vr = query_sub(a,b,k*2+2,(l+r)/2,r);
      return fx(vl, vr);
    }
  }
  X query(int a,int b){ return query_sub(a,b,0,0,n); }
};