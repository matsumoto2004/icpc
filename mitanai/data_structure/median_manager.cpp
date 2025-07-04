template<class T>
class median_manager {
    int even_mode;
    multiset <T> l, r;
    int sz = 0;

    void adjust() {
        if (int(l.size()) > int(r.size()) + 1) {
            r.insert(*l.rbegin());
            l.erase(prev(l.end()));
        }
        if (int(r.size()) > int(l.size()) + 1) {
            l.insert(*r.begin());
            r.erase(r.begin());
        }
    }

public:
    // median of (a_1, a_2,..., a_{2*n}) =
    // a_n                   if even_mode = 1
    // (a_n + a_{n+1}) / 2   if           = 2
    // a_{n+1}               if           = 3
    median_manager(int even_mode) : even_mode(even_mode) {
        assert(1 <= even_mode and even_mode <= 3);
        l.insert(numeric_limits<T>::min());
        r.insert(numeric_limits<T>::max());
    }

    void insert(T x) {
        ++sz;
        if (x < *r.begin()) l.insert(x);
        else r.insert(x);
        adjust();
    }

    void erase(T x) {
        --sz;
        if (x < *r.begin()) {
            auto it = l.find(x);
            assert(it != l.end());
            l.erase(it);
        } else {
            auto it = r.find(x);
            assert(it != r.end());
            r.erase(it);
        }
        adjust();
    }

    T get() {
        assert(sz > 0);
        T vl = *l.rbegin();
        T vr = *r.begin();
        if (sz & 1) {
            if (l.size() > r.size()) return vl;
            else return vr;
        } else {
            if (even_mode == 1) {
                return vl;
            } else if (even_mode == 2) {
                return (vl + vr) / 2;
            } else {
                return vr;
            }
        }
    }
};