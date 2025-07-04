#include<vector>

template<typename T>
struct BIT_1{
    int n;
    std::vector<T> v;
    constexpr BIT_1(const int _):n(_),v(_+1,0){}
private:
    //[0,i].
    constexpr T sum_sub(int i){
        T res=0;
        i++;
        for(;i>0;i-=(i&-i))res+=v[i];
        return res;
    }
public:
    //iに加算.
    constexpr void add(int i,const T x){
        i++;
        for(;i<=n;i+=(i&-i))v[i]+=x;
    }
    //[l,r).
    constexpr T sum(const int l,const int r){
        return sum_sub(r-1)-sum_sub(l-1);
    }
    //sum>=wなるindex.条件:a[i]>=0.
    constexpr int lower_bound(T w){
        if(w<=0)return 0;
        int x=0,r=1;//x:1_idxで今見てる箇所の一つ左
        while(r<n)r<<=1;
        for(int len=r;len>0;len>>=1){
            if(x+len<=n && v[x+len]<w){
                w-=v[x+len];
                x+=len;
            }
        }
        return x;
    }
};


template<typename T>
struct BIT{
    int n;
    std::vector<T> v[2];
    constexpr BIT(const int _):n(_){
        v[0].assign(n+1,T(0));
        v[1].assign(n+1,T(0));
    }
private:
    //[0,i].
    constexpr T sum_sub(int i,const int p){
        T res=0;
        i++;
        for(;i>0;i-=(i&-i))res+=v[p][i];
        return res;
    }
    constexpr void add_sub(int i,const int p,const T x){
        i++;
        for(;i<=n;i+=(i&-i))v[p][i]+=x;
    }
public:
    constexpr void add(const int l,const int r,const T x){
        add_sub(l,0,x);
        add_sub(r,0,-x);
        add_sub(l,1,-l*x);
        add_sub(r,1,r*x);
    }
    //[l,r).
    constexpr T sum(const int l,const int r){
        return (sum_sub(r-1,0)*r+sum_sub(r-1,1))-(sum_sub(l-1,0)*l+sum_sub(l-1,1));
    }
};


//need to verify
template<typename T>
struct BIT_2d{
    int n,m;
    std::vector<vector<T>> v;
    constexpr BIT_2d(const int n_,const int m_):n(n_),m(m_){
        v.assign(n+1,vector<T>(m+1,T(0)));
    }
private:
    //[0,i],[0,j].
    constexpr T sum_sub(int i,int j){
        T res=0;
        for(int I=i+1;I>0;I-=(I&-I))for(int J=j+1;J>0;J-=(J&-J)){
            res+=v[I][J];
        }
        return res;
    }
public:
    constexpr void add(const int i,const int j,const T x){
        for(int I=i+1;I<=n;I+=(I&-I))for(int J=j+1;J<=m;J+=(J&-J)){
            v[I][J]+=x;
        }
    }
    //[sx,gx) , [sy,gy).
    constexpr T sum(int sx,int sy,int gx,int gy){
        return sum_sub(gx-1,gy-1)-sum_sub(gx-1,sy-1)-sum_sub(sx-1,gy-1)+sum_sub(sx-1,sy-1);
    }
};