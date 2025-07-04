template<typename T>
class BIT {
    int n;
    vector <T> val;
public:
    BIT(int n) : n(n), val(n + 1, 0) {}
    
    void add(int i, T x = 1) {
        i++;
        while (i <= n) {
            val[i] += x;
            i += i & -i;
        }
    }
    
    T sum(int i) {
        T ret = 0;
        i++;
        while (i > 0) {
            ret += val[i];
            i -= i & -i;
        }
        return ret;
    }
    
    // [l, r)
    T sum(int l, int r) { return sum(r - 1) - sum(l - 1); }
};