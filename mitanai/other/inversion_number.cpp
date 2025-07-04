ll inversion_number(int n,const vi& v) {
    ll ret = 0;
    BIT<int> bt(n);
    rep(i,n) {
        ret += i-bt.sum(v[i]);
        bt.add(v[i]);
    }
    return ret;
}