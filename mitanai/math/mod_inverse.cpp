// composite_mod
// gcd(a, mod) must be 1
ll mod_inverse(ll a, ll mod) {
    ll x, y;
    ext_gcd(a, mod, x, y);
    return (x % mod + mod) % mod;
}

template<class T,class U>
T mod_pow(T x,U y,const ll mod){T res=1;while(y){if(y&1)(res*=x)%=mod;(x*=x)%=mod;y>>=1;}return res;}
