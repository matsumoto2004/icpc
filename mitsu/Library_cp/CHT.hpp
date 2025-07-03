#include<vector>
#include<tuple>

//追加直線の傾きには単調性を課す
//追加償却O(1)、最大値クエリO(logN)
//クエリにも単調性を課すと償却O(1)
//整数型想定なのでdoubleはよしなに。
template<typename T>
struct CHT{
    //{s,t,l} : sx+t, [l,?)で最大
    T min_val;
    std::size_t last_idx;
    std::vector<std::tuple<T,T,T>> lines;
    //変数xのとりうる最小値を渡しておく
    CHT(T min_val=0):min_val(min_val),last_idx(0){}
    //sx+t
    void add(T s,T t){
        while(!lines.empty()){
            auto [s0,t0,l0]=lines.back();
            //s0<s
            //x=(t0-t)/(s-s0)が交点
            //整数点しかみないので切り上げをみる：doubleの場合気をつける
            if((t0-t +s-s0-1)/(s-s0)<=l0){
                lines.pop_back();
            }
            else{
                lines.push_back(std::make_tuple(s,t,(t0-t +s-s0-1)/(s-s0)));
                break;
            }
        }
        if(lines.empty())lines.push_back(std::make_tuple(s,t,min_val));
        return;
    }
    // 最大値
    T calc(T x){
        std::size_t l=0,r=lines.size();
        while(r>l+1){
            std::size_t mid=(l+r)/2;
            (std::get<2>(lines[mid]) > x ? r:l)=mid;
        }
        auto [s,t,ignore]=lines[l];
        return s*x+t;
    }
    //クエリに単調性
    T calc_incl(T x){
        while(last_idx+1<lines.size() && std::get<2>(lines[last_idx+1])<=x)last_idx++;
        auto [s,t,ignore]=lines[last_idx];
        return s*x+t;
    }
};