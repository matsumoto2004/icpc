template<class T>
class slope_trick;

template<class T>
ostream &operator<<(ostream &, const slope_trick<T> &);

template<class T>
class slope_trick {
    T mn;
    priority_queue <T> l;
    priority_queue <T, vector<T>, greater<T>> r;
    T lz_l, lz_r;
public:
    slope_trick() : slope_trick(0, vector<T>(), vector<T>()) {}
    
    slope_trick(T _mn, const vector <T> &_l, const vector <T> &_r) : mn(_mn) {
        rep(i, _l.size() - 1)
        assert(_l[i] >= _l[i + 1]);
        rep(i, _r.size() - 1)
        assert(_r[i] <= _r[i + 1]);
        assert(_l.empty() or _r.empty() or _l[0] <= _r[0]);
        l = priority_queue<T>(all(_l));
        r = priority_queue < T, vector < T >, greater < T >> (all(_r));
        lz_l = lz_r = 0;
    }
    
    T eval(T x) {
        T res = mn;
        auto tmp_l = l;
        auto tmp_r = r;
        while (tmp_l.size()) {
            res += max<T>(0, tmp_l.top() + lz_l - x);
            tmp_l.pop();
        }
        while (tmp_r.size()) {
            res += max<T>(0, x - (tmp_r.top() + lz_r));
            tmp_r.pop();
        }
        return res;
    }
    
    T get_min() { return mn; }
    
    void add(T a) { mn += a; }
    
    // + max(0, a - x)
    void add_l(T a) {
        T r0 = (r.empty() ? numeric_limits<T>::max() : r.top() + lz_r);
        mn += max<T>(0, a - r0);
        if (a <= r0) {
            l.push(a - lz_l);
        } else {
            r.pop();
            r.push(a - lz_r);
            l.push(r0 - lz_l);
        }
    }
    
    // + max(0, x - a)
    void add_r(T a) {
        T l0 = (l.empty() ? numeric_limits<T>::min() : l.top() + lz_l);
        mn += max<T>(0, l0 - a);
        if (a >= l0) {
            r.push(a - lz_r);
        } else {
            l.pop();
            l.push(a - lz_l);
            r.push(l0 - lz_r);
        }
    }
    
    // + abs(x - a)
    void add_lr(T a) {
        add_l(a);
        add_r(a);
    }
    
    // f <- g, where g(x) = min[y <= x] f(y)
    void cum_min_l() {
        l.clear();
        lz_l = 0;
    }
    
    // f <- g, where g(x) = min[y >= x] f(y)
    void cum_min_r() {
        r.clear();
        lz_r = 0;
    }
    
    // f <- g, where g(x) = f(x - a)
    void translation(T a) {
        lz_l += a;
        lz_r += a;
    }
    
    // f <- g, where g(x) = min[x + a <= y <= x + b] f(y)
    void slide_min(T a, T b) {
        assert(a <= b);
        lz_l -= b;
        lz_r -= a;
    }
    
    friend ostream &operator
    <<<T>(ostream &, const slope_trick<T> &);
};

template<class T>
ostream &operator<<(ostream &os, const slope_trick<T> &sl) {
    priority_queue <T> l = sl.l;
    priority_queue <T, vector<T>, greater<T>> r = sl.r;
    vector <T> vl, vr;
    while (l.size()) vl.pb(l.top() + sl.lz_l), l.pop();
    while (r.size()) vr.pb(r.top() + sl.lz_r), r.pop();
    reverse(all(vl));
    os << vl << ", " << sl.mn << ", " << vr;
    return os;
}