#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define all(x) (x).begin(),(x).end()


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
    reverse(all(ver));

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