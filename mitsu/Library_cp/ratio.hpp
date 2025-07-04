bool reduction=true;//計算量等考えて変える.
template<typename T>
struct frac{
    T a;
    T b;
    bool neg;
    frac(const string x):a(0),b(1),neg(false){
        bool dot=false;
        for(char c:x){
            if(c=='.')dot=true;
            else if(c=='-')neg=true;
            else{
                if(dot)b=b*10;
                a=a*10+c-'0';
            }
        }
        if(reduction){
            T g=gcd(a,b);
            a/=g;
            b/=g;
        }
    }
    template<typename S>
    frac(const S x):frac(x,S(1)){}
    template<typename S>
    frac(const S x,const S y):a(x),b(y),neg(false){
        assert(y!=0);
        if(x<0){
            a=-x;
            neg=!neg;
        }
        if(y<0){
            b=-y;
            neg=!neg;
        }
        if(reduction){
            S g=gcd(x,y);
            a/=g;
            b/=g;
        }
    }
    constexpr operator T(){return (neg ? -a/b : a/b);}
    constexpr frac<T> operator -(){neg=!neg;return *this;}
    friend constexpr frac<T>& operator*=(frac<T> &l,const frac<T> r){
        if(l.a==0 || r.a==0){
            l.a=0;
            l.b=1;
            l.neg=false;
            return l;
        }
        T g=1;
        if(reduction)g=gcd(l.a , r.b);
        T g2=1;
        if(reduction)g2=gcd(l.b , r.a);
        l.a=(l.a/g)*(r.a/g2);
        l.b=(l.b/g2)*(r.b/g);
        l.neg^=r.neg;
        return l;
    }
    friend constexpr frac<T>& operator*=(frac<T> &l,const T r){
        return l*=frac<T>(r);
    }
    friend constexpr frac<T>& operator/=(frac<T> &l,frac<T> r){
        assert(r.a!=0);
        if(l.a==0){
            return l;
        }
        swap(r.a , r.b);
        T g=1;
        if(reduction)g=gcd(l.a , r.b);
        T g2=1;
        if(reduction)g2=gcd(l.b , r.a);
        l.a=(l.a/g)*(r.a/g2);
        l.b=(l.b/g2)*(r.b/g);
        l.neg^=r.neg;
        return l;
    }
    friend constexpr frac<T>& operator/=(frac<T> &l,const T r){
        return l/=frac<T>(r);
    }
    friend constexpr frac<T>& operator+=(frac<T> &l,frac<T> r){
        if(l.neg)l.a*=-1;
        if(r.neg)r.a*=-1;
        l=frac<T>(l.a*r.b + r.a*l.b , l.b*r.b);
        return l;
    }
    friend constexpr frac<T>& operator+=(frac<T> &l,const T r){
        return l+=frac<T>(r);
    }
    friend constexpr frac<T>& operator-=(frac<T> &l,frac<T> r){
        if(l.neg)l.a*=-1;
        if(!r.neg)r.a*=-1;
        l=frac<T>(l.a*r.b + r.a*l.b , l.b*r.b);
        return l;
    }
    friend constexpr frac<T>& operator-=(frac<T> &l,const T r){
        return l-=frac<T>(r);
    }
    template<typename S>
    friend constexpr frac<T> operator*(frac<T> l,const S r){
        return l*=r;
    }
    template<typename S>
    friend constexpr frac<T> operator/(frac<T> l,const S r){
        return l/=r;
    }
    template<typename S>
    friend constexpr frac<T> operator+(frac<T> l,const S r){
        return l+=r;
    }
    template<typename S>
    friend constexpr frac<T> operator-(frac<T> l,const S r){
        return l-=r;
    }
    friend constexpr ostream& operator<<(ostream& os,const frac<T> r){
        if(r.neg)os << '-';
        if(r.b==1)cout << r.a;
        else os << r.a << '/' << r.b;
        return os;
    }

    friend constexpr bool operator<(const frac<T> l,const frac<T> r){
        T L=l.a*r.b;
        if(l.neg)L=-L;
        T R=l.b*r.a;
        if(r.neg)R=-R;
        return L<R;
    }
    friend constexpr bool operator>(const frac<T> l,const frac<T> r){
        return r<l;
    }
    friend constexpr bool operator>=(const frac<T> l,const frac<T> r){
        return !(l<r);
    }
    friend constexpr bool operator<=(const frac<T> l,const frac<T> r){
        return !(r<l);
    }
    friend constexpr bool operator==(const frac<T> l,const frac<T> r){
        return l<=r && l>=r;
    }
    friend constexpr bool operator!=(const frac<T> l,const frac<T> r){
        return (l>r || l<r);
    }
};