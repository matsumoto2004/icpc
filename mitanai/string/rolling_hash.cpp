using ull = unsigned long long;
const ull mod = (1ull << 61) - 1;
const ull mask30 = (1ull << 30) - 1;
const ull mask31 = (1ull << 31) - 1;
const ull mask61 = mod;

ull calc_mod(ull x) {
    ull xu = x >> 61;
    ull xd = x & mask61;
    ull res = xu + xd;
    if (res >= mod) res -= mod;
    return res;
}

// a*b mod 2^61-1
ull mul(ull a,ull b) {
    ull au = a>>31;
    ull ad = a&mask31;
    ull bu = b>>31;
    ull bd = b&mask31;
    ull mid = ad*bu+au*bd;
    ull midu = mid>>30;
    ull midd = mid&mask30;
    return au*bu*2+midu+(midd<<31)+ad*bd;
}

class rolling_hash {
    ull base1;
    ull base2;
    int n;
    string s;
    vector<ull> hash1,hash2,pow1,pow2;

    void init() {
        random_device rnd;
        mt19937_64 mt(rnd());
        uniform_int_distribution<ull> dist(2,mod-2);
        base1 = dist(mt);
        base2 = dist(mt);
//        base1 = calc_mod(mt());
//        base2 = calc_mod(mt());
//        while(base1 < 2 || base1 > mod-2) base1 = calc_mod(mt());
//        while(base2 < 2 || base2 > mod-2) base2 = calc_mod(mt());
        hash1.assign(n+1,0);
        hash2.assign(n+1,0);
        pow1.assign(n+1, 1);
        pow2.assign(n+1,1);
        rep(i,n) {
            hash1[i+1] = calc_mod(mul(hash1[i],base1)+s[i]);
            hash2[i+1] = calc_mod(mul(hash2[i],base2)+s[i]);
            pow1[i+1] = calc_mod(mul(pow1[i], base1));
            pow2[i+1] = calc_mod(mul(pow2[i], base2));
        }
    }

public:
    rolling_hash(string s):s(s),n(s.size()) {
        init();
    }
    // return hash of [l,r) of S
    pair<ull,ull> get(int l,int r) {
        ll res1 = calc_mod(hash1[r]+mod*4-mul(hash1[l], pow1[r-l]));
        ll res2 = calc_mod(hash2[r]+mod*4-mul(hash2[l], pow2[r-l]));
        return make_pair(res1,res2);
    }
    // return hash of T
    pair<ull,ull> get(string t) {
        ull ht1 = 0,ht2 = 0;
        rep(i,t.size()) {
            ht1 = calc_mod(mul(ht1,base1)+t[i]);
            ht2 = calc_mod(mul(ht2,base2)+t[i]);
        }
        return make_pair(ht1,ht2);
    }
    int count(string t) {
        if(t.size() > n) return 0;
        pair<ull,ull> ht = get(t);
        int res = 0;
        rep(i,n-t.size()+1) {
            if(get(i,i+t.size()) == ht) res++;
        }
        return res;
    }
};

