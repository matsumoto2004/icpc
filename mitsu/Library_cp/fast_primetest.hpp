using ll=long long;
using bigll=__int128_t;

ll primetest[]={2,3,61};
ll primetest_big[]={2,325,9375,28178,450775,9780504,1795265022};
//O(x^(1/4))

template<typename T>
T mypow(T x,ll y,ll mod){
    T res=1;
    while(y){
        if(y&1)res*=x, res%=mod;
        x*=x, x%=mod;
        y>>=1;
    }
    return res;
}

bool isprime(ll x){
    if(x==0 || x==1)return false;
    ll d=(x-1)/((x-1)&-(x-1));
    if(x<(1LL<<32)){
        if(x==2 || x==3 || x==61)return true;
        for(ll e:primetest){
            ll t=d;
            ll y=mypow(e,t,x);
            if(y==1)continue;
            while(y!=x-1){
                y=(y*y)%x;
                if(y==1 || t==x-1)return false;
                t<<=1;
            }
        }
        return true;
    }
    else{
        for(bigll e:primetest_big){
            ll t=d;
            bigll y=mypow(e,t,x);
            if(y==1)continue;
            while(y!=x-1){
                y=(y*y)%x;
                if(y==1 || t==x-1)return false;
                t<<=1;
            }
        }
        return true;
    }
}