template<typename T>
struct matrix{
    size_t H,W;
    std::vector<std::vector<T>> val;
    matrix(){}
    matrix(size_t H,size_t W):H(H),W(W),val(H,std::vector<T>(W)){}
    matrix(size_t H,size_t W,const T x):H(H),W(W),val(H,std::vector<T>(W)){
        assert(H==W);
        for(size_t i=0;i<H;i++)val[i][i]=x;
    }
    matrix<T> &operator+=(const matrix<T>& r){
        assert(H==r.H && W==r.W);
        for(size_t i=0;i<H;i++)for(size_t j=0;j<W;j++)val[i][j]+=r.val[i][j];
        return *this;
    }
    matrix<T> &operator-=(const matrix<T>& r){
        assert(H==r.H && W==r.W);
        for(size_t i=0;i<H;i++)for(size_t j=0;j<W;j++)val[i][j]-=r.val[i][j];
        return *this;
    }
    matrix<T> &operator*=(const matrix<T>& r){
        assert(W==r.H);
        matrix<T> res(H,r.W);
        for(size_t i=0;i<H;i++)for(size_t j=0;j<r.W;j++){
            for(size_t k=0;k<W;k++)res.val[i][j]+=val[i][k]*r.val[k][j];
        }
        return *this=res;
    }
    friend matrix<T> operator+(const matrix<T> l,const matrix<T>& r){
        l+=r;
        return l;
    }
    friend matrix<T> operator-(const matrix<T> l,const matrix<T>& r){
        l-=r;
        return l;
    }
    friend matrix<T> operator*(const matrix<T> l,const matrix<T>& r){
        l*=r;
        return l;
    }
    friend std::vector<T> operator*(const matrix<T>& l,const std::vector<T>& r){
        assert(l.W==r.size());
        std::vector<T> res(l.H);
        for(size_t i=0;i<l.H;i++)for(size_t j=0;j<l.W;j++)res[i]+=l.val[i][j]*r[j];
        return res;
    }
    template<typename U>
    matrix<T> pow(U cnt)const{
        assert(H==W);
        if(!cnt--)return matrix<T>(H,W,T(1));
        auto res=*this;
        auto x=*this;
        while(cnt){
            if(cnt&1){
                res*=x;
            }
            x*=x;
            cnt>>=1;
        }
        return res;
    }
};