class dynamic_modint {
    ll x;
    static int mod;
public:
    static void set_mod(int _mod) { mod = _mod; }
    
    dynamic_modint(ll x = 0) : x((x % mod + mod) % mod) { assert(mod > 0); }
    
    static int get_mod() { return mod; }
    
    constexpr int val() const { return x; }
    
    dynamic_modint operator-() const { return dynamic_modint(-x); }
    
    dynamic_modint &operator+=(const dynamic_modint &a) {
        if ((x += a.val()) >= mod) x -= mod;
        return *this;
    }
    
    dynamic_modint &operator++() { return *this += 1; }
    
    dynamic_modint &operator-=(const dynamic_modint &a) {
        if ((x += mod - a.val()) >= mod) x -= mod;
        return *this;
    }
    
    dynamic_modint &operator--() { return *this -= 1; }
    
    dynamic_modint &operator*=(const dynamic_modint &a) {
        (x *= a.val()) %= mod;
        return *this;
    }
    
    dynamic_modint operator+(const dynamic_modint &a) const {
        dynamic_modint res(*this);
        return res += a;
    }
    
    dynamic_modint operator-(const dynamic_modint &a) const {
        dynamic_modint res(*this);
        return res -= a;
    }
    
    dynamic_modint operator*(const dynamic_modint &a) const {
        dynamic_modint res(*this);
        return res *= a;
    }
    
    dynamic_modint pow(ll t) const {
        dynamic_modint res = 1, a(*this);
        while (t > 0) {
            if (t & 1) res *= a;
            t >>= 1;
            a *= a;
        }
        return res;
    }
    
    friend istream &operator>>(istream &is, dynamic_modint &a);
    
    // for prime mod
    dynamic_modint inv() const { return pow(mod - 2); }
    
    dynamic_modint &operator/=(const dynamic_modint &a) { return *this *= a.inv(); }
    
    dynamic_modint operator/(const dynamic_modint &a) const {
        dynamic_modint res(*this);
        return res /= a;
    }
};

int dynamic_modint::mod = 0;//ここいじるといいかも

ostream &operator<<(ostream &os, const dynamic_modint &a) { return os << a.val(); }

bool operator==(const dynamic_modint &a, const dynamic_modint &b) { return a.val() == b.val(); }

bool operator!=(const dynamic_modint &a, const dynamic_modint &b) { return a.val() != b.val(); }

dynamic_modint &operator++(dynamic_modint &a) { return a += 1; }

dynamic_modint &operator--(dynamic_modint &a) { return a -= 1; }

using mint = dynamic_modint;

using vm = vector<mint>;
using vvm = vector<vm>;