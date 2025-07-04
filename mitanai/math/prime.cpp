// reference : https://nyaannyaan.github.io/library/prime/fast-factorize.hpp.html
template<typename T>
class prime {
    vector<T> as;

    constexpr T add(T a, T b, T m) {
        return (a + b >= m ? a + b - m : a + b);
    }

    constexpr T sub(T a, T b, T m) {
        return (a - b < 0 ? a - b + m : a - b);
    }

    constexpr T mul(T a, T b, T m) {
        return T((__int128) a * (__int128) b % m);
    }

    constexpr T mod_pow(T a, T t, T m) {
        T res = 1;
        while (t > 0) {
            if (t & 1) res = mul(res, a, m);
            t >>= 1;
            a = mul(a, a, m);
        }
        return res;
    }

    constexpr bool miller_rabin(T n) {
        T d = n - 1;
        while (~d & 1) d >>= 1;
        for (T a: as) {
            a %= n;
            if (!a) return true;
            T t = d;
            T y = mod_pow(a, t, n);
            while (t != n - 1 and y != 1 and y != n - 1) {
                y = mul(y, y, n);
                t *= 2;
            }
            if (y != n - 1 and t % 2 == 0) return false;
        }
        return true;
    }

    // reference : https://nyaannyaan.github.io/library/misc/rng.hpp
    // [0, 2^64 - 1)
    uint64_t rng() {
        static uint64_t x_ =
                uint64_t(chrono::duration_cast<chrono::nanoseconds>(
                        chrono::high_resolution_clock::now().time_since_epoch())
                                 .count()) *
                10150724397891781847ULL;
        x_ ^= x_ << 7;
        return x_ ^= x_ >> 9;
    }

    T pollard_rho(T n) {
        assert(n >= 2);
        if (~n & 1) return 2;
        if (miller_rabin(n)) return n;
        T R;
        auto f = [&](T x) { return add(mul(x, x, n), R, n); };
        auto rnd_ = [&]() { return rng() % (n - 2) + 2; };
        while (true) {
            T x = 0, y = 0, ys = 0, q = 1;
            R = rnd_(), y = rnd_();
            T g = 1;
            constexpr int m = 128;
            for (int r = 1; g == 1; r <<= 1) {
                x = y;
                rep(i, r) y = f(y);
                for (int k = 0; g == 1 and k < r; k += m) {
                    ys = y;
                    for (int i = 0; i < m and i < r - k; ++i) q = mul(q, sub(x, y = f(y), n), n);
                    g = gcd(q, n);
                }
            }
            if (g == n) {
                do {
                    g = gcd(sub(x, ys = f(ys), n), n);
                } while (g == 1);
            }
            if (g != n) return g;
        }
        assert(false);
    }

    vector<T> factorize(T n) {
        assert(n >= 2);
        T p = pollard_rho(n);
        if (p == n) return {p};
        auto l = factorize(p);
        auto r = factorize(n / p);
        copy(all(r), back_inserter(l));
        return l;
    }

public:
    constexpr prime() {
        static_assert(is_same<T, int>::value or is_same<T, ll>::value);
        if (is_same<T, int>::value) as = {2, 7, 61};
        else as = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    }

    constexpr bool is_prime(T n) {
        assert(n >= 1);
        if (n == 1) return false;
        if (~n & 1) return n == 2;
        return miller_rabin(n);
    }

    map<T, int> factor_list(T n) {
        assert(n >= 1);
        if (n == 1) return {};
        map<T, int> mp;
        for (T x: factorize(n)) ++mp[x];
        return mp;
    }

    vector<T> unique_factor(T n) {
        assert(n >= 1);
        if (n == 1) return {};
        auto res = factorize(n);
        sort(all(res));
        res.erase(unique(all(res)), res.end());
        return res;
    };

    T count_divisor(T n) {
        assert(n >= 1);
        T res = 1;
        for (auto p: factor_list(n)) res *= p.second + 1;
        return res;
    };

    vector<T> enum_divisors(T n) {
        assert(n >= 1);
        vector<pair<T, int>> v;
        for (auto p: factor_list(n)) v.pb(p);
        vector<T> res;
        auto f = [&](auto &f, int i, T x) -> void {
            if (i == SZ(v)) {
                res.pb(x);
                return;
            }
            rep(j, v[i].second + 1) {
                f(f, i + 1, x);
                if (j == v[i].second) break;
                x *= v[i].first;
            }
        };
        f(f, 0, 1);
        sort(all(res));
        return res;
    }
};
