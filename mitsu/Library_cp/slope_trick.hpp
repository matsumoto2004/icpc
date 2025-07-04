#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct slope_trick{
    T min_val;
    T infty;
    //slide_minや平行移動がないなら無視して良い
    T add_l;
    T add_r;
    priority_queue<T> l;
    priority_queue<T,vector<T>,greater<T>> r;
    slope_trick(const T _infty):min_val(0),infty(_infty),add_l(0),add_r(0){
        l.push(-infty);
        r.push(infty);
    }
    void add_constval(T a){
        min_val+=a;
    }
    //max(a-x,0)
    void add_max_left(T a){//傾きの最小値は-1、最大値は不変 => |L|は1増え、|R|は不変  r.top()はl.top()かr.top()の何れかに移る
        min_val+=max(a-r.top()-add_r,T(0));
        r.push(a-add_r);
        l.push(r.top()+add_r-add_l);
        r.pop();
    }
    //max(x-a,0)
    void add_max_right(T a){//傾きの最小値は不変、最大値は+1 => |L|は不変、|R|は1増える  l.top()はl.top()かr.top()の何れかに移る
        min_val+=max(l.top()+add_l-a,T(0));
        l.push(a-add_l);
        r.push(l.top()+add_l-add_r);
        l.pop();
    }
    void add_abs(T a){
        add_max_left(a);
        add_max_right(a);
    }
    //左から累積minをとる
    void min_left(){
        r=priority_queue<T,vector<T>,greater<T>>();
        r.push(infty);
    }
    //右から累積minをとる
    void min_right(){
        l=priority_queue<T>();
        l.push(-infty);
    }
    //f(x):=min(f(y)),x-a<=y<=x-b a>=bが必要
    void slide_min(T a,T b){
        add_l+=b;
        add_r+=a;
    }
};

/*
初期状態を
f(x)=inf (x>=t)
としたい場合、関数の加算クエリの回数をN回として、N+1回 max(x-t,0) を加算しておけば良い。
これは「x>=tでの傾きが常に正になるようにする」という操作に相当。
f(x)=inf (x<=t) も同様。
*/