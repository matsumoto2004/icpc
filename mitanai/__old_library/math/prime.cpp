template<typename T>
class prime {
    T n;
public:
    prime(T n) : n(n) {}
    
    map<T, int> factor_list() {//int -> T ちょっと書き換えた
        if (n == 1) return {};
        T nn = n;
        map<T, int> ret;
        for (int i = 2; (ll) i * i <= n; i++) {
            if (nn % i != 0) continue;
            int cnt = 0;
            while (nn % i == 0) {
                cnt++;
                nn /= i;
            }
            ret[i] = cnt;
        }
        if (nn != 1) ret[nn]++;
        return ret;
    }
    vi unique_factor() {
        map<int, int> m = factor_list();
        vi ret;
        for (P p : m) ret.pb(p.first);
        return ret;
    };
    
    bool is_prime() {
        auto v = factor_list();
        return v.size() == 1 && (*v.begin()).second == 1;//v[0].second==1ではないと思う
    }
    
    int count_divisor() {
        int ret = 1;
        map<int, int> fl = factor_list(n);
        for (auto p : fl) ret *= p.second + 1;
        return ret;
    }; 
    
    vector <T> enum_divisors() {
        vector <T> res;
        for (T i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                res.pb(i);
                if (n / i != i) res.pb(n / i);
            }
        }
        sort(all(res));
        return res;
    }
};