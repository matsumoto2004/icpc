template<typename T>
class BIT {
    int n;
    vector <T> val;

    T sum(int i) const {
        T ret = 0;
        while (i > 0) {
            ret += val[i];
            i -= i & -i;
        }
        return ret;
    }

public:
    BIT(int n) : n(n), val(n + 1, 0) {}

    BIT(const vector <T> &init) : n(init.size()) {
        vector <T> sum(n + 1);
        rep(i, n)
        sum[i + 1] = sum[i] + init[i];
        val.resize(n + 1);
        rep(i, 1, n + 1)
        val[i] = sum[i] - sum[i - (i & -i)];
    }

    void add(int i, T x = 1) {
        assert(0 <= i and i < n);
        i++;
        while (i <= n) {
            val[i] += x;
            i += i & -i;
        }
    }

    // [l, r)
    T sum(int l, int r) const {
        assert(0 <= l and l <= r and r <= n);
        return sum(r) - sum(l);
    }

    // return        max x s.t. sum(0, x) <= w
    // constraint    e >= 0 for all elements e
    int max_right(T w) const {
        assert(w >= 0);
        int x = 0, r = 1;
        while (r < n) r <<= 1;
        for (int len = r; len > 0; len = len >> 1) {
            if (x + len <= n && val[x + len] <= w) {
                w -= val[x + len];
                x += len;
            }
        }
        return x;
    }
};