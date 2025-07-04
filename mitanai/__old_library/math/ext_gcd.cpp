// return gcd(a, b)
// solve  ax + by = gcd(a, b)
// |x| <= b, |y| <= a (if a*b != 0)
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}