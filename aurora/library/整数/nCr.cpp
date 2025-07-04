const long long int MAX = 510000; //最大値
const long long int MOD = 998244353;

long long int fac[MAX], finv[MAX], inv[MAX];

void COMinit() {
  fac[0] = fac[1] = 1;
  finv[0] = finv[1] = 1;
  inv[1] = 1;
  for(int i=2;i<MAX;i++){
    fac[i] = fac[i-1]*i%MOD;
    inv[i] = MOD-inv[MOD%i]*(MOD/i)%MOD;
    finv[i] = finv[i-1]*inv[i]%MOD;
  }
}

long long int COM(long long int n,long long int k){
  if(n<k) return 0;
  if(n<0||k<0) return 0;
  return fac[n]*(finv[k]*finv[n-k]%MOD)%MOD;
}