long long int modpow(long long int a,long long int n,long long int mod){
    long long int res = 1;
    while(n>0){
        if(n&1) res = res*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return res;
}