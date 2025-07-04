struct Mo {
  int n;
  vector< pair< int, int > > lr;

  explicit Mo(int n) : n(n) {}

  void add(int l, int r) { /* [l, r) */
    lr.emplace_back(l, r);
  }

  template< typename AL, typename AR, typename EL, typename ER, typename O >
  void build(const AL &add_left, const AR &add_right, const EL &erase_left, const ER &erase_right, const O &out) {
    int q = (int) lr.size();
    int bs = n / min< int >(n, sqrt(q));
    vector< int > ord(q);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&](int a, int b) {
      int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
      if(ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
    });
    int l = 0, r = 0;
    for(auto idx : ord) {
      while(l > lr[idx].first) add_left(--l);
      while(r < lr[idx].second) add_right(r++);
      while(l < lr[idx].first) erase_left(l++);
      while(r > lr[idx].second) erase_right(--r);
      out(idx);
    }
  }

  template< typename A, typename E, typename O >
  void build(const A &add, const E &erase, const O &out) {
    build(add, add, erase, erase, out);
  }
};

/*
  1<=Ai<=NでAの[l,r]でいくつペアを作れるかという問題
  int N;
    cin >> N;
    vl A(N);
    rep(i,N) cin >> A[i];
    Mo mo(N);
    int Q;
    cin >> Q;
    rep(i,Q){
        int l,r;
        cin >> l >> r;
        mo.add(l-1,r);
    }
    vector<int> cnt(N+1,0),ans(Q);
    int pair = 0;
    auto add = [&](int i) {
        cnt[A[i]]++;
        if(cnt[A[i]]%2 == 0) pair++;
    };
    auto erase = [&](int i) {
        cnt[A[i]]--;
        if(cnt[A[i]]%2 == 1) pair--;
    };
    auto out = [&](int q) {
        ans[q] = pair;
    };
    mo.build(add, erase, out);
    rep(i,Q) cout << ans[i] << endl;
*/