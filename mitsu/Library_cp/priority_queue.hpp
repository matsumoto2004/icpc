#include<vector>

template<typename T>
struct my_priority_queue{
    struct ans{
        int idx;
        T val;
        ans():idx(-1),val(T(0)){}
        ans(int idx,T val):idx(idx),val(val){}
    };
    int n;
    //いまi番目がどういう状況か持つ配列
    std::vector<ans> now;
    //ヒープ　ただしindexを持つ
    std::vector<int> que;
    my_priority_queue(const int n):n(n),now(n),que(1){}
    bool empty(){
        return que.size()==1ul;
    }
    size_t size(){
        return que.size()-1;
    }
    //まだ存在していないならpush
    void change(int i,T val){
        assert(0<=i && i<n);
        int j;
        if(now[i].idx==-1){
            j=que.size();
            que.resize(que.size()+1);
        }
        else{
            j=now[i].idx;
        }

        while(j>1 && now[que[j/2]].val>val){
            now[que[j/2]].idx=j;
            que[j]=que[j/2];
            j/=2;
        }

        que[j]=i;
        now[i].idx=j;
        now[i].val=val;
        return;
    }
    //番号と値のペアを返す
    std::pair<int,T> pop_front(){
        int res=que[1];
        int tmp=que.back();
        que.pop_back();
        if(que.size()>1ul){
            int j=1;
            while((size_t)j*2<que.size()){
                int chi=j*2;
                //j(now[tmp].val),chi(now[que[chi]].val),chi+1で最も小さい値を持つものを上に持ってくる　あとはswap相当の操作
                if((size_t)chi+1<que.size() && now[que[chi+1]].val<now[tmp].val){
                    //必ずswap操作が発生する　右の子(chi+1)の方が小さいならchi+1とjをswapするので、chi++する
                    chi+=(now[que[chi]].val>now[que[chi+1]].val);
                }
                else if((size_t)chi>que.size() || now[que[chi]].val>=now[tmp].val){
                    break;
                }
                //chiとjをswap
                que[j]=que[chi];
                now[que[j]].idx=j;
                j=chi;
            }
            que[j]=tmp;
            now[tmp].idx=j;
        }
        return {res,now[res].val};
    }
    void print(int i=1,int depth=0){
        if(i==1)std::cout << "queue:" << '\n';
        if((size_t)i*2<que.size())print(i*2,depth+1);
        for(int i=0;i<depth;i++)std::cout << "  ";
        std::cout << now[que[i]].val << '\n';
        if((size_t)i*2+1<que.size())print(i*2+1,depth+1);
        return;
    }
};