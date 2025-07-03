#include<vector>
#include<algorithm>
using namespace std;

template<typename T,typename Tx=int,typename Ty=int>
struct range_tree{
    //「(x,y)に重みv」
    //矩形和を求める

    int sz;
    //x座標をsortedにして保管
    vector<Tx> x;
    //セグ木の要領で管理　最下段ではy[i+sz]はi番目のx座標を持つy座標を管理、sumも同様（yでソートして累積和を取っておく）
    //yやsumもセグ木の要領で管理すれば、オーダーを変えずに可換モノイドまで扱えるようになる。
    vector<vector<Ty>> y;
    vector<vector<T>> sum;

    range_tree(vector<pair<pair<Tx,Ty>,T>> vec):sz(1){
        sort(vec.begin(),vec.end());
        for(auto p:vec)x.emplace_back(p.first.first);
        x.erase(unique(x.begin(),x.end()),x.end());
        while(sz<(int)x.size())sz*=2;
        y.resize(sz*2);
        sum.resize(sz*2);
        int idx=0;
        for(auto [p,v]:vec){
            auto [px,py]=p;
            if(x[idx]!=px)idx++;
            assert(x[idx]==px);
            y[idx+sz].emplace_back(py);
            sum[idx+sz].emplace_back(v);
        }
        for(int i=sz-1;i;i--){
            //y[2*i],y[2*i+1]のマージ
            int l=0,r=0;
            while(l+r<int(y[2*i].size()+y[2*i+1].size())){
                int v=2*i;
                if(l<int(y[2*i].size()) && r<int(y[2*i+1].size())){
                    if(y[2*i][l]>y[2*i+1][r])v=2*i+1;
                }
                else if(l==int(y[2*i].size()))v=2*i+1;
                y[i].emplace_back(y[v][(v==2*i ? l:r)]);
                sum[i].emplace_back(sum[v][(v==2*i ? l:r)]);
                (v==2*i ? l:r)++;
            }
        }
        for(int i=1;i<2*sz;i++){
            sum[i].insert(sum[i].begin(),0);
            for(int j=0;j+1<int(sum[i].size());j++)sum[i][j+1]+=sum[i][j];
        }
    }

    T query_inner(int i,Ty ly,Ty ry){
        int l=lower_bound(y[i].begin(),y[i].end(),ly)-y[i].begin();
        int r=lower_bound(y[i].begin(),y[i].end(),ry)-y[i].begin();
        return sum[i][r]-sum[i][l];
    }

    T query(Tx lx,Ty ly,Tx rx,Ty ry){
        int l=lower_bound(x.begin(),x.end(),lx)-x.begin()+sz;
        int r=lower_bound(x.begin(),x.end(),rx)-x.begin()+sz;
        T ans=0;
        while(l!=r){
            if(l&1)ans+=query_inner(l++,ly,ry);
            if(r&1)ans+=query_inner(--r,ly,ry);
            l/=2;
            r/=2;
        }
        return ans;
    }
};