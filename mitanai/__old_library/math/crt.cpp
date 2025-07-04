// solve x = r[i] (mod m[i])
// return (R, M), when the answer is x = R (mod M)
// return (0, 0), when there is no answer
// condition: lcm(m[i]) <= LLONG_MAX
LP crt(const vl &r, const vl &m) {
    assert(r.size() == m.size());
    int n = r.size();
    ll R = 0, M = 1;
    rep(i, n)
    {
        assert(m[i] >= 1);
        ll p, q;
        ll g = ext_gcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
        if ((r[i] - R) % g != 0) return P(0, 0);
        ll tmp = (r[i] - R) / g * p % (m[i] / g);
        R += M * tmp;
        M *= m[i] / g;
        R = (R % M + M) % M;
    }
    return {R, M};
}