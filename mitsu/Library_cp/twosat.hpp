#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define ALL(x) (x).begin(),(x).end()

vector<int> scc(vector<vector<int>> &g,vector<vector<int>> &ginv){
    const int n=g.size();
    
    vector<bool> seen(n,false);
    vector<int> ver;
    auto dfs=[&](int v,auto &dfs)->void{
        if(seen[v])return;
        seen[v]=true;
        for(int ne:g[v]){
            dfs(ne,dfs);
        }
        ver.emplace_back(v);
        return;
    };
    rep(i,n)dfs(i,dfs);
    seen.assign(n,false);
    reverse(ALL(ver));

    vector<int> ans(n);
    auto revdfs=[&](int v,int k,auto &revdfs)->void{
        if(seen[v])return;
        seen[v]=true;
        ans[v]=k;
        for(int ne:ginv[v]){
            revdfs(ne,k,revdfs);
        }
        return;
    };
    int val=0;
    for(int i:ver)if(!seen[i])revdfs(i,val++,revdfs);
    return ans;
}

struct twosat{
    //[i,false]->[i]
    //[i,true]->[i+n]
    int n;
    vector<vector<int>> g,ginv;
    vector<bool> ans;
    twosat(int sz):n(sz),g(2*sz),ginv(2*sz),ans(sz){}
    void add_edge(int i,int j){
        g[i].emplace_back(j);
        ginv[j].emplace_back(i);
    }
    // i は (x : bool)
    void add(int i,bool x){
        //[i:x] <=> [i:x or i:x]
        add(i,x,i,x);
    }
    // (i が x : bool) or (j が y : bool)
    void add(int i,bool x,int j,bool y){
        //[i:x or j:y] <=> [i:!x => j:y]
        //対偶辺は必ず張る。
        add_edge(i+(!x)*n,j+y*n);
        add_edge(j+(!y)*n,i+x*n);
    }
    bool satisfiable(){
        auto res=scc(g,ginv);
        bool ok=true;
        for(int i=0;i<n;i++){
            if(res[i]==res[i+n])ok=false;
            ans[i]=(res[i]<res[i+n] ? 1:0);
        }
        return ok;
    }
};