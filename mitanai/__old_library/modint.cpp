template<int mod>
class modint {
    ll x;
public:
    constexpr modint(ll x = 0) : x((x % mod + mod) % mod) {}
    
    static constexpr int get_mod() { return mod; }
    
    constexpr int val() const { return x; }
    
    constexpr modint operator-() const { return modint(-x); }
    
    constexpr modint &operator+=(const modint &a) {
        if ((x += a.val()) >= mod) x -= mod;
        return *this;
    }
    
    constexpr modint &operator++() { return *this += 1; }
    
    constexpr modint &operator-=(const modint &a) {
        if ((x += mod - a.val()) >= mod) x -= mod;
        return *this;
    }
    
    constexpr modint &operator--() { return *this -= 1; }
    
    constexpr modint
    &
    
    operator*=(const modint &a) {
        (x *= a.val()) %= mod;
        return *this;
    }
    
    constexpr modint
    
    operator+(const modint &a) const {
        modint res(*this);
        return res += a;
    }
    
    constexpr modint
    
    operator-(const modint &a) const {
        modint res(*this);
        return res -= a;
    }
    
    constexpr modint
    
    operator*(const modint &a) const {
        modint res(*this);
        return res *= a;
    }
    
    constexpr modint
    pow(ll
    t) const {
        modint res = 1, a(*this);
        while (t > 0) {
            if (t & 1) res *= a;
            t >>= 1;
            a *= a;
        }
        return res;
    }
    
    template<int m>
    friend istream &operator>>(istream &, modint<m> &);
    
    // for prime mod
    constexpr modint
    
    inv() const { return pow(mod - 2); }
    
    constexpr modint
    &
    
    operator/=(const modint &a) { return *this *= a.inv(); }
    
    constexpr modint
    
    operator/(const modint &a) const {
        modint res(*this);
        return res /= a;
    }
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

template<int mod>
istream &operator>>(istream &is, modint<mod> &a) { return is >> a.x; }

template<int mod>
constexpr ostream
&
operator<<(ostream
&os,
const modint<mod> &a
) {
return os << a.

val();

}

template<int mod>
constexpr bool operator==(const modint<mod> &a, const modint<mod> &b) { return a.val() == b.val(); }

template<int mod>
constexpr bool operator!=(const modint<mod> &a, const modint<mod> &b) { return a.val() != b.val(); }

template<int mod>
constexpr modint<mod>
&
operator++(modint<mod>
&a) {
return a += 1; }

template<int mod>
constexpr modint<mod>
&
operator--(modint<mod>
&a) {
return a -= 1; }

using mint = ;

using vm = vector<mint>;
using vvm = vector<vm>;