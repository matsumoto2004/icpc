constexpr long long primetest[]={2,3,61};
constexpr long long primetest_big[]={2,325,9375,28178,450775,9780504,1795265022};
//O(N^(1/4))
//N>2^32では__int128_tが使える環境に限る
bool isprime(const long long x){
    if(x==0 || x==1)return false;
    const long long d=(x-1)/((x-1)&-(x-1));
    if(x<(1LL<<32)){
        if(x==2 || x==3 || x==61)return true;
        for(long long e:primetest){
            long long t=d;
            long long y=expm(e,t,x);
            if(y==1)continue;//とりあえずテスト通過.
            while(y!=x-1){//y=-1になったらその時点でテスト通過.
                y=(y*y)%x;//y=e^2t modx.
                if(y==1 || t==x-1)return false;//y==1:1の平方根に1,-1以外が存在.t==x-1:e^t!=1.
                t<<=1;
            }
        }
        return true;
    }
    else{
        for(__int128_t e:primetest_big){
            long long t=d;
            __int128_t y=expm(e,t,x);
            if(y==1)continue;//とりあえずテスト通過.
            while(y!=x-1){//y=-1になったらその時点でテスト通過.
                y=(y*y)%x;//y=e^2t modx.
                if(y==1 || t==x-1)return false;//y==1:1の平方根に1,-1以外が存在.t==x-1:e^t!=1.
                t<<=1;
            }
        }
        return true;
    }
}