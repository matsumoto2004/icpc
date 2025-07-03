template<typename T,T (*op)(T,T),T e>
struct segtree{
    int n;
    int sz;
    std::vector<T> v;
    constexpr segtree(){}
    constexpr segtree(const int n_,const T x)noexcept:segtree(vector<T>(n_,x)){}
    constexpr segtree(const int n_)noexcept:segtree(vector<T>(n_,e)){}
    constexpr segtree(const vector<T> &a_)noexcept:n(a_.size()),sz(1){
        while(n>sz)sz<<=1;
        v.resize(sz*2);
        for(int i=sz;i<sz+n;i++)v[i]=a_[i-sz];
        for(int i=sz-1;i>0;i--){
            v[i]=op(v[2*i] , v[2*i+1]);
        }
    }
    constexpr void change(int i,const T x)noexcept{
        v[i+sz]=x;
        i=(i+sz)>>1;
        while(i){
            v[i]=op(v[2*i] , v[2*i+1]);
            i>>=1;
        }
        return;
    }
    //右からxをかける
    constexpr void prod_from_right(int i,const T x)noexcept{
        change(i,op(v[i+sz] , x));
        return;
    }
    //左からxをかける
    constexpr void prod_from_left(int i,const T x)noexcept{
        change(i,op(x , v[i+sz]));
        return;
    }
    constexpr T get(const int i)noexcept{return v[i+sz];}
    constexpr T get(int l,int r)noexcept{
        l+=sz;
        r+=sz;
        T res_l=e;
        T res_r=e;
        while(l<r){
            if(l&1){
                res_l=op(res_l , v[l++]);
            }
            l>>=1;
            if(r&1){
                res_r=op(v[--r] , res_r);
            }
            r>>=1;
        }
        return op(res_l , res_r);
    }
};

/*
結合則が成り立てば良い.(非可換でも構わない.)
単位元がないなら適当な元を単位元と見なすことが必要.
*/