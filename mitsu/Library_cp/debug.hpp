#include<iostream>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

#ifndef LOGX
struct{
    constexpr operator int(){return -int(1e9)-10;}
    constexpr operator long long(){return -(long long)(1e18)-10;}
}neginf;
struct{
    constexpr operator int(){return int(1e9)+10;}
    constexpr operator long long(){return (long long)(1e18)+10;}
    constexpr auto operator -(){return neginf;}
}inf;
#endif

#define overload6(_1,_2,_3,_4,_5,_6,name,...) name

#define dbgnewl {std::cout << newl;}
#define dbg1(x) {std::cout << #x << ':',_prt(x);std::cout << ' ';dbgnewl;}
#define dbg2(x,y) {std::cout << #x << ':',_prt(x);std::cout << ' ';dbg1(y);}
#define dbg3(x,...) {std::cout << #x << ':',_prt(x);std::cout << ' ';dbg2(__VA_ARGS__);}
#define dbg4(x,...) {std::cout << #x << ':',_prt(x);std::cout << ' ';dbg3(__VA_ARGS__);}
#define dbg5(x,...) {std::cout << #x << ':',_prt(x);std::cout << ' ';dbg4(__VA_ARGS__);}
#define dbg6(x,...) {std::cout << #x << ':',_prt(x);std::cout << ' ';dbg5(__VA_ARGS__);}

//#define dbg(...) {overload6(__VA_ARGS__,dbg6,dbg5,dbg4,dbg3,dbg2,dbg1)(__VA_ARGS__)}
#define dbg(...) {overload6(__VA_ARGS__,dbg6,dbg5,dbg4,dbg3,dbg2,dbg1)(__VA_ARGS__)}{std::cout.flush();}


template<typename T> inline void prt(T a_);
template<typename T> inline void _prt(T a_);
template<typename A,typename B> inline void _prt(std::map<A,B> a_);
template<typename A,typename B> inline void _prt(std::unordered_map<A,B> a_);
template<typename T> inline void _prt(std::set<T> a_);
template<typename T> inline void _prt(std::unordered_set<T> a_);
template<typename A,typename B> inline void _prt(std::pair<A,B> a_);
template<typename T> inline void _prt(std::vector<T> a_);
template<typename T> inline void _prt(std::vector<std::vector<T>> a_);
//template<typename Head,typename... Tail> void _prt(std::tuple<Head,Tail...> a_);

#ifdef ATCODER_MODINT_HPP
template<int m>
inline void _prt(atcoder::static_modint<m> _a){
    std::cout << _a.val();
}
template<int id>
inline void _prt(atcoder::dynamic_modint<id> _a){
    std::cout << _a.val();
}
#endif
//_prtでは改行しない.
inline void _prt(bool a_){
    if(a_)std::cout<<1;
    else std::cout<<0;
}
inline void _prt(int a_){
    if(a_>=(int)inf)std::cout << "inf";
    else if(a_<=-(int)inf)std::cout << "-inf";
    else std::cout << a_;
}
inline void _prt(long long a_){
    if(a_>=(long long)inf)std::cout << "INF";
    else if(a_<=-(long long)inf)std::cout << "-INF";
    else std::cout << a_;
}
template<typename T> inline void _prt(T a_){std::cout << a_;}
template<typename A,typename B>
inline void _prt(std::map<A,B> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt((*it).first);
        std::cout<<':';
        _prt((*(it++)).second);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename A,typename B>
inline void _prt(std::unordered_map<A,B> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt((*it).first);
        std::cout<<':';
        _prt((*(it++)).second);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename A,typename B>
inline void _prt(std::multimap<A,B> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt((*it).first);
        std::cout<<':';
        _prt((*(it++)).second);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename A,typename B>
inline void _prt(std::unordered_multimap<A,B> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt((*it).first);
        std::cout<<':';
        _prt((*(it++)).second);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename T>
inline void _prt(std::set<T> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt(*it++);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename T>
inline void _prt(std::unordered_set<T> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt(*it++);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename T>
inline void _prt(std::multiset<T> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt(*it++);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename T>
inline void _prt(std::unordered_multiset<T> a_){
    std::cout<<'{';
    auto it=a_.begin();
    while(it!=a_.end()){
        _prt(*it++);
        std::cout<<(it==a_.end() ? "":",");
    }
    std::cout<<'}';
}
template<typename A,typename B>
inline void _prt(std::pair<A,B> a_){
    std::cout << '(';
    _prt(a_.first);
    std::cout << ',';
    _prt(a_.second);
    std::cout << ')';
}
template<typename T>
inline void _prt(std::vector<T> a_){
    std::cout<<'{';
    for(size_t i=0;i<a_.size();i++){
        _prt(a_[i]);
        if(i+1<a_.size())std::cout<<',';
    }
    std::cout<<'}';
}
template<typename T>
inline void _prt(std::vector<std::vector<T>> a_){
    std::cout<<"{\n";
    for(size_t i=0;i<a_.size();i++){
        _prt(a_[i]);
        if(i+1<a_.size())std::cout<<",\n";
        else std::cout<<"\n}";
    }
}
template<typename T,size_t L>
inline void _prt(std::array<T,L> a_){
    std::cout<<'{';
    for(size_t i=0;i<L;i++){
        _prt(a_[i]);
        if(i+1<L)std::cout<<',';
    }
    std::cout<<'}';
}
template<typename T,size_t L1,size_t L2>
inline void _prt(std::array<std::array<T,L2>,L1> a_){
    std::cout<<"{\n";
    for(size_t i=0;i<L1;i++){
        _prt(a_[i]);
        if(i+1<L1)std::cout<<",\n";
        else std::cout<<"\n}";
    }
}
//tuple どうしようね
/*
template<typename Head,typename... Tail>
void _prt(std::tuple<Head,Tail...> a_){
    auto [x,y]=a_;
    std::cout << sizeof...(y) << '\n';
    return;
}
*/

template<typename T> inline void prt(T a_){_prt(a_);std::cout<<'\n';};