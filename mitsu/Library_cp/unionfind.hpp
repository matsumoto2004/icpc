#include<bits/stdc++.h>

struct unionfind{
    int n;
    std::vector<int> par;
    unionfind(const int _):n(_),par(_,-1){}
    int find(const int x){
        if(par[x]<0)return x;
        return par[x]=find(par[x]);
    }
    bool same(const int x,const int y){
        return find(x)==find(y);
    }
    void unite(int x,int y){
        x=find(x);
        y=find(y);
        if(x==y)return;
        if(par[x]<par[y])std::swap(x,y);
        int t=par[y]+par[x];
        par[y]=t;
        par[x]=y;
        n--;
        return;
    }
    int getsize(int i){
        i=find(i);
        return -par[i];
    }
};

//Tには可換群が載る.
template<typename T,T (*op)(T,T),T (*op_inv)(T,T)>
struct weight_uf{
    int n;
private:
    std::vector<int> par;
    std::vector<T> diff;
public:
    weight_uf(const int _):n(_),par(_,-1),diff(_,T(0)){}
    int find(const int x){
        if(par[x]<0)return x;
        int r=find(par[x]);//根 この時に先祖のdiffの値も更新がかかる
        diff[x]=op(diff[x],diff[par[x]]);
        return par[x]=r;
    }
private:
    T weight(const int x){
        find(x);
        return diff[x];
    }
public:
    //!same(x,y)なる(x,y)に対しては動かない.
    //[y]-[x](=op_inv(y,x))を返す.
    T diff_query(const int x,const int y){
        return op_inv(weight(y),weight(x));
    }
    contsexpr bool same(const int x,const int y){
        return find(x)==find(y);
    }
    /*
    既にある情報と矛盾する場合はreturn falseする.
    [y]-[x](=op_inv(y,x))=wとなるようにunite.
    */
    bool unite(int x,int y,T w){
        if(same(x,y)){
            //矛盾する
            if(diff_query(x,y)!=w)return false;
            //矛盾しない
            else return true;
        }
        w=op(w,op_inv(weight(x),weight(y)));
        x=find(x);
        y=find(y);
        if(par[x]>par[y])swap(x,y),w=op_inv(T(0),w);
        int t=par[y]+par[x];
        par[x]=t;
        par[y]=x;
        diff[y]=w;
        n--;
        return true;
    }
    int getsize(int i){
        i=find(i);
        return -par[i];
    }
};
/*
e.g.
int op(int a,int b){
    return a+b;
}
int op_inv(int a,int b){
    return a-b;
}
*/