#include<vector>

template<typename T>
struct bellman_ford{
    struct edge{
        int from;
        int to;
        T cost;
    };
    const long long INF=std::numeric_limits<T>::max()/3LL;//大体3e18.
    int n;
    std::vector<edge> graph;
    std::vector<T> d;
    bellman_ford(const int n_):n(n_),graph(n_),d(n_,INF){}
    void add_edge(int from,int to,T cost){
        graph.push_back(edge{from,to,cost});
    }
    bool ans(int s){
        d[s]=0;
        bool ok=true;
        for(int i=0;i<2*n;i++){
            bool update=false;
            for(edge e:graph){
                if(d[e.from]!=INF && d[e.to] > d[e.from] + e.cost){
                    update=true;
                    d[e.to]=d[e.from]+e.cost;
                    if(i+1>=n){
                        d[e.to]=-INF;
                        ok=false;
                    }
                }
            }
            if(ok && !update)return true;
        }
        return ok;
    }
};
/*
負閉路の存在判定は, 上の実装でfalseがreturnされた場合でよい.
各点が始点からの距離を-infにしうるかの判定は,各点のコストが-INFか否かで確認する.
*/