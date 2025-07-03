#include<vector>
#include<string>
#include<random>
#include<cmath>

const unsigned long long MOD=(1LL<<61)-1;
const unsigned long long MASK31=(1LL<<31)-1;
const unsigned long long MASK30=(1LL<<30)-1;
const unsigned long long MASK61=MOD;

unsigned long long CalcMod(const unsigned long long x){
    unsigned long long xu=x>>61;
    unsigned long long xd=(x&MASK61);
    xu+=xd;
    if(xu>=MOD)xu-=MOD;
    return xu;
}
unsigned long long prod_61(const unsigned long long a,const unsigned long long b){
    unsigned long long au=a>>31;
    unsigned long long ad=a&MASK31;
    unsigned long long bu=b>>31;
    unsigned long long bd=b&MASK31;
    unsigned long long mid=ad*bu+au*bd;
    unsigned long long mu=mid>>30;
    unsigned long long md=mid&MASK30;
    return au*bu*2 + mu + (md<<31) + ad*bd;//RollingHash用なのでここでmodを取っていない 注意
}
unsigned long long exp_61(unsigned long long a,unsigned long long b){
    if(b==0)return 1;
    if(b==1)return a;
    if(b&1)return CalcMod(prod_61(exp_61(a,b-1),a));
    unsigned long long t=exp_61(a,b/2);
    return CalcMod(prod_61(t,t));
}

struct rolling_hash{
    std::string s;
    std::vector<unsigned long long> hashes;
    unsigned long long base;
    std::vector<unsigned long long> base_pow;
    rolling_hash(const std::string _,unsigned long long now_base=0):s(_),hashes(_.size()+1,0),base(now_base),base_pow(_.size()+1,1){
        if(!base)init();
        CalcHash();
        for(int i=0;i<(int)s.size();i++){
            base_pow[i+1]=CalcMod(prod_61(base_pow[i] , base));
        }
    }
    void init(){
        std::random_device seed_gen;
        std::mt19937_64 rnd(seed_gen());
        std::uniform_int_distribution<unsigned long long> for_base(1UL,MOD-2);
        while(1){
            unsigned long long _r=for_base(rnd);
            if(std::gcd(_r,MOD-1)!=1)continue;
            base=exp_61(3UL,_r);
            if(base<=30)continue;///適宜書き換える.s_MAXより大きければ良い
            break;
        }
        return;
    }
    void CalcHash(){
        for(int i=0;i<(int)s.size();i++){
            hashes[i+1]=CalcMod(prod_61(hashes[i],base) + (s[i]-'a'+1));//適宜書き換える
        }
        return;
    }
    unsigned long long hash(int i,int j){//s[i..j-1]のhash=h[0..j-1] - h[0..i-1]*base^(j-i+1).
        unsigned long long res=MOD + hashes[j] - CalcMod(  prod_61(hashes[i], base_pow[j-i])  );
        if(res>=MOD)res-=MOD;
        return res;
    }
};