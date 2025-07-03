#ifndef LOGX
#include<bits/stdc++.h>
#endif

//辺を陽に持っているので重いことに注意.
template<typename T>
struct graph{
    struct edge{
        int to;
        T cost;
    };
    
    int n;
    std::vector<std::vector<edge>> g;
    std::vector<T> d;
    std::vector<int> prev;
    
    graph(const int n_) : n(n_) , g(n_) , d(n_,inf){}/////////適宜変えること！！
    
    void addedge(const int s,const int t,const T cost){
        edge e;
        e.to=t;
        e.cost=cost;
        g[s].emplace_back(e);
    }
    //ElogV
    void dijkstra(const int s,bool NEW=false,bool const_cost=false,bool need_prev=false){//sからstartのdijkstra
        if(NEW)for(auto &e:d)e=inf;
        d[s]=0;
        if(need_prev)prev.resize(n,-1)
        if(!const_cost){
            std::priority_queue<std::pair<T,int>,std::vector<std::pair<T,int>>,std::greater<std::pair<T,int>>> que;
            que.push(std::pair<T,int>(0,s));
            while(!que.empty()){
                std::pair<T,int> pa=que.top();que.pop();
                long long k=pa.second;
                if(d[k]<pa.first)continue;
                for(edge e:g[k]){
                    if(d[e.to]>d[k]+e.cost){
                        d[e.to]=d[k]+e.cost;
                        que.push(std::pair<T,int>(d[e.to],e.to));
                        if(need_prev)prev[e.to]=k;
                    }
                }
            }
        }
        else{
            std::queue<std::pair<T,int>> que;
            que.push(std::pair<T,int>(0,s));
            while(!que.empty()){
                std::pair<T,int> pa=que.front();que.pop();
                long long k=pa.second;
                if(d[k]<pa.first)continue;
                for(edge e:g[k]){
                    if(d[e.to]>d[k]+e.cost){
                        d[e.to]=d[k]+e.cost;
                        que.push(std::pair<T,int>(d[e.to],e.to));
                        if(need_prev)prev[e.to]=k;
                    }
                }
            }
        }
    }
    vector<int> get_path(int t){
        std::vector<int> path;
        for(int now=t;now!=-1;now=prev[now])path.emplace_back(now);
        std::reverse(path.begin(),path.end());
        return std::move(path);
    }
};