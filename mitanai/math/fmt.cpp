// Fast Mobius Transform
// inverse fzt
template<class T>
void fmt(vector<T> &v) {
    int n = v.size();
    assert(n == 1 << __builtin_ctz(n));
    for (int i = 1; i < n; i <<= 1) {
        rep(j, n) {
            if ((j & i) == 0) {
//                convolve subset
                v[j | i] -= v[j];
//                convolve superset
//                v[j] -= v[j | i];
            }
        }
    }
}