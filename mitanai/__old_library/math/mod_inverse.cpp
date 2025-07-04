// composite_mod
// gcd(a, mod) must be 1
ll mod_inverse(ll a, ll mod) {
    ll x, y;
    extGCD(a, mod, x, y);
    return (x % mod + mod) % mod;
}