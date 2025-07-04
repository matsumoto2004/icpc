#include<bits/stdc++.h>
using namespace std;
#include "segtree.hpp"

//セグメント木に載せた場合 パス上の積取得以外は idx[頂点番号] を使って頑張ってください。
template<typename T,T (*op)(T,T),T e>
struct HLD{
    int n,root;
    vector<int> par;
    vector<vector<int>> ch;
    vector<int> sz_memo;
    vector<int> depth;
    //(その頂点が属する連結成分の)highest vertexのつもり
    vector<int> hv;
    //idx[頂点番号]でデータ構造におけるインデックスを得る
    vector<int> idx;
    //ver[i]でデータ構造においてi番に対応する頂点番号を得る
    vector<int> ver;
    segtree<T,op,e> seg;/////////////////////////////

    HLD(vector<int> &_par,vector<vector<int>> &_ch,int _root=0):
                    n(_par.size()),root(_root),par(_par),ch(_ch),
                        sz_memo(n),depth(n),hv(n),idx(n),seg(n){
        ver.reserve(n);
        auto decomp=[&](int v,int now_hv,auto &decomp)->void{
            idx[v]=ver.size();
            hv[v]=now_hv;
            ver.emplace_back(v);

            int ne_big=-1,nesz=0;
            for(int ne:ch[v]){
                if(chmax(nesz,sz(ne)))ne_big=ne;
                depth[ne]=depth[v]+1;
            }

            if(ne_big!=-1)decomp(ne_big,now_hv,decomp);
            for(int ne:ch[v])if(ne!=ne_big){
                decomp(ne,ne,decomp);
            }
        };
        decomp(root,root,decomp);
    }

    HLD(vector<vector<int>> &_g,int root=0){
        n=_g.size();
        vector<int> par(n,-1);
        vector<vector<int>> ch(n);
        auto dfs=[&](int v,auto &dfs)->void{
            for(int ne:_g[v])if(ne!=par[v]){
                par[ne]=v;
                ch[v].emplace_back(ne);
                dfs(ne,dfs);
            }
        };
        dfs(root,dfs);
        *this=HLD(par,ch,root);
    }
    int sz(int i){
        if(sz_memo[i])return sz_memo[i];
        for(int ne:ch[i])sz_memo[i]+=sz(ne);
        sz_memo[i]++;
        return sz_memo[i];
    }
    //可換モノイドのみ。
    //セグ木でないならseg.get()を書き換える。
    //パスを変更したければ同様に作る。
    //辺クエリなら、値は子に載せる。
    T query(int s,int t,bool is_vertex=true){
        T ans=e;
        while(hv[s]!=hv[t]){
            if(depth[hv[s]]<depth[hv[t]])swap(s,t);
            ans=op(ans,seg.get(idx[hv[s]],idx[s]+1));
            s=par[hv[s]];
        }
        ans=op(ans,seg.get(min(idx[s],idx[t])+!is_vertex,max(idx[s],idx[t])+1));
        return ans;
    }
    int LCA(int s,int t){
        while(hv[s]!=hv[t]){
            if(depth[hv[s]]<depth[hv[t]])swap(s,t);
            s=par[hv[s]];
        }
        if(depth[s]<depth[t])return s;
        else return t;
    }
};