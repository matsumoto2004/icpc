#include<bits/stdc++.h>

/*
実行時modint:
template<int &mod>
struct Fp{};
int main(){
    static int mod;cin >> mod;
    using mint = Fp<mod>;
}
*/
template<int mod>
struct Fp{
    long long x;
    constexpr Fp(const long long _x=0)noexcept:x((_x%mod+mod)%mod){}
    constexpr Fp operator-()const noexcept{
        return x ? mod-x:0;
    }
    friend constexpr Fp<mod>& operator+=(Fp<mod> &l,const Fp<mod> r)noexcept{
        l.x+=r.x;
        if(l.x>=mod)l.x-=mod;
        return l;
    }
    friend constexpr Fp<mod>& operator-=(Fp<mod> &l,const Fp<mod> r)noexcept{
        l.x-=r.x;
        if(l.x<0)l.x+=mod;
        return l;
    }
    //modが十分小さい場合
    friend constexpr Fp<mod>& operator*=(Fp<mod> &l,const Fp<mod> r)noexcept{
        l.x=l.x*r.x %mod;
        return l;
    }
    //modが巨大な場合
    /*
    friend constexpr Fp<mod> prod(Fp<mod> l,long long r)noexcept{
        if(r==0)return 0;
        Fp<mod> res=prod(l+=l,r>>1);
        if(r&1)res+=l;
        return res;
    }
    friend constexpr Fp<mod>& operator*=(Fp<mod> &l,const Fp<mod> r)noexcept{
        return l=prod(l,r.x);
    }
    */
    
    friend constexpr Fp<mod>& operator/=(Fp<mod> &l,const Fp<mod> r)noexcept{
        long long a=r.x,b=mod,u=1,v=0;
        while(b){
            long long t=a/b;
            a-=t*b;std::swap(a,b);
            u-=t*v;std::swap(u,v);
        }
        l.x=l.x*u%mod;
        if(l.x<0)l.x+=mod;
        return l;
    }
    friend constexpr Fp<mod> operator+(Fp<mod> l,const Fp<mod> r){
        return l+=r;
    }
    friend constexpr Fp<mod> operator-(Fp<mod> l,const Fp<mod> r){
        return l-=r;
    }
    friend constexpr Fp<mod> operator*(Fp<mod> l,const Fp<mod> r){
        return l*=r;
    }
    friend constexpr Fp<mod> operator/(Fp <mod> l,const Fp<mod> r){
        return l/=r;
    }
    #ifdef LOGX
    friend constexpr bool operator==(const Fp<mod> l,const Fp<mod> r){
        return l.x==r.x;
    }
    friend constexpr bool operator!=(const Fp<mod> l,const Fp<mod> r){
        return l.x!=r.x;
    }
    #endif
    friend constexpr std::ostream& operator<<(std::ostream &os,const Fp<mod> &r)noexcept{
        return os << r.x;
    }
    friend constexpr std::istream& operator>>(std::istream &is,Fp<mod> &r)noexcept{
        long long t=0;is >> t;
        r.x=(Fp<mod>(t)).x;
        return is;
    }
    //0^0 = 1
    Fp<mod> pow(int n)const{
        Fp<mod> res = 1;
        mint v = *this;
        while(n){
            if(n&1)res*=v;
            v*=v;
            n/=2;
        }
        return res;
    }
};


//数論変換
template<int mod>
void ntt(std::vector<Fp<mod>> &x, const unsigned bit, bool inverse = false){
	std::size_t n = x.size();
	assert(n == 1 << bit);
	assert(bit <= 23);

	std::size_t mask1 = n - 1;

	mint pv_zeta = mint(3).pow(119);
	for(unsigned i = 0; i < 23 - bit; ++i){
		pv_zeta *= pv_zeta;
	}
	if(!inverse){
		pv_zeta = 1/pv_zeta;
	}
	std::vector<mint> zeta(n, 1);
	for(std::size_t i = 1; i < n; ++i){
		zeta[i] = zeta[i - 1] * pv_zeta;
	}
	for(unsigned i = 0; i < bit; ++i){
		std::size_t mask2 = mask1 >> i + 1;
		std::vector<mint> tmp(n);
		for(std::size_t j = 0; j < n; ++j){
			std::size_t lower = j & mask2;
			std::size_t upper = j ^ lower;
			std::size_t shifted = upper << 1 & mask1;
			tmp[j] = x[shifted | lower] + zeta[upper] * x[shifted | mask2 + 1 | lower];
		}
		x = std::move(tmp);
	}
    if(inverse)for(mint &v:x)v/=n;
}

template<int mod>
std::vector<Fp<mod>> prod_mint(std::vector<Fp<mod>> &a,std::vector<Fp<mod>> &b){
    int bit=1;
    while((1<<bit)<a.size()+b.size())bit++;
    auto A=a,B=b;
    A.resize(1<<bit);
    B.resize(1<<bit);
    ntt(A,bit);
    ntt(B,bit);
    for(size_t i = 0;i < A.size(); i++)A[i]*=B[i];
    ntt(A,bit,true);
    A.resize(a.size()+b.size()-1);
    return A;
}