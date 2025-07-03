#include<bits/stdc++.h>
using namespace std;
const int inf=1000000009;
#define all(x) (x).begin(),(x).end()

struct mf_graph{
    int n;
    struct edge2{
        int to,rev;
        int cap;
    };
    struct edge{
        int from;
        int to;
        int cap,flow;
    };
    vector<pair<int,int>> pos;
    vector<vector<edge2>> g;

    mf_graph(int n):n(n),g(n){}

    void add_edge(int from,int to,int cap){
        pos.push_back({from,{int(g[from].size())}});
        int f_id=int(g[from].size());
        int to_id=int(g[to].size());
        if(from==to)to_id++;
        g[from].push_back(edge2{to,to_id,cap});
        g[to].push_back(edge2{from,f_id,0});
        return;
    }

    int flow(int s,int t,int flow_lim=inf){
        vector<int> lev(n),iter(n);
        queue<int> q;
        auto bfs=[&](){
            fill(all(lev),-1);
            lev[s]=0;
            q=queue<int>();
            q.push(s);
            while(!q.empty()){
                int v=q.front();
                q.pop();
                for(auto e:g[v]){
                    if(e.cap==0 || lev[e.to]>=0)continue;
                    lev[e.to]=lev[v]+1;
                    if(e.to==t)return;
                    q.push(e.to);
                }
            }
        };
        auto dfs=[&](auto self,int v,int up){
            if(v==s)return up;
            int res=0;
            int lev_v=lev[v];
            for(int &i=iter[v];i<int(g[v].size());i++){
                edge2& e=g[v][i];
                if(lev_v<=lev[e.to] || g[e.to][e.rev].cap==0)continue;
                int d=self(self,e.to,min(up-res,g[e.to][e.rev].cap));
                if(d<=0)continue;
                g[v][i].cap+=d;
                g[e.to][e.rev].cap-=d;
                res+=d;
                if(res==up)return res;
            }
            lev[v]=n;
            return res;
        };

        int flow=0;
        while(flow<flow_lim){
            bfs();
            if(lev[t]==-1)break;
            fill(all(iter),0);
            int f=dfs(dfs,t,flow_lim-flow);
            if(!f)break;
            flow+=f;
        }
        return flow;
    }
};
