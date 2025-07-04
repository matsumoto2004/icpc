#include<atcoder/modint>

// 階乗とその逆元を前計算する
template<unsigned N, unsigned P>
class fact_inv {
public:
    unsigned fact[N];
    unsigned ifact[N];
    constexpr fact_inv() : fact{}, ifact{} {
        fact[0] = 1;
        for (unsigned i{1}; i < N; ++i)
            fact[i] = static_cast<unsigned long>(fact[i - 1]) * i % P;
        ifact[N - 1] = atcoder::internal::inv_gcd(fact[N - 1], P).second;
        for (unsigned i{N}; --i;)
            ifact[i - 1] = static_cast<unsigned long>(ifact[i]) * i % P;
    }
};

constexpr int MOD=998244353;
//constexpr int MOD=1000000007;

constexpr fact_inv<1000001,MOD> precalc{};