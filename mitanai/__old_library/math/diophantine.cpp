// solve a + bx = c (mod m)
ll diophantine(ll a, ll b, ll c, ll m) {
    int g = gcd(b, m);
    assert(a % g == c % g);
    b = (b % m + m) % m
    ll res = ((c - a) / g % m + m) % m;
    res *= mod_inverse(b / g, m / g);
    res %= m / g;
    return res;
}