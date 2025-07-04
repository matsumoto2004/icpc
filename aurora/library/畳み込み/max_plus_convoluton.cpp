void dft_for_fft(vector<complex<long double>> &func, int inverse){
    int len = func.size();
    if(len == 1) return;
    vector<complex<long double>> A,B;
    rep(i,len/2){
      A.push_back(func[2*i]);
      B.push_back(func[2*i+1]);
    }
    dft_for_fft(A,inverse);
    dft_for_fft(B,inverse);
    complex<long double> now = 1,zeta = polar((long double)1.0,inverse*2.0*pi/(long double)len);
    rep(i,len){
      func[i] = A[i%(len/2)]+now*B[i%(len/2)];
      now *= zeta;
    }
  }
  
  template<typename T>
  vector<long double> multiply(vector<T> f, vector<T> g){
    int len = 1;
    while(len < f.size()+g.size()) len *= 2;
    vector<complex<long double>> nf(len),ng(len);
    rep(i,len){
      if(i < f.size()) nf[i] = f[i];
      if(i < g.size()) ng[i] = g[i];
    }
    dft_for_fft(nf,1);
    dft_for_fft(ng,1);
    rep(i,len) nf[i] *= ng[i];
    dft_for_fft(nf,-1);
    vector<long double> res;
    rep(i,len) res.push_back(nf[i].real()/len);
    return res;
  }
  
  ll depth_cnt(ll N,ll u,int d){
    vector<ll> res(61,0);
    res[0] = 1;
    ll l = 2LL*u,r=2LL*u+1;
    rep2(i,1,61){
      if(l > N) break;
      else if(r <= N) res[i] = r-l+1;
      else{
        res[i] = N-l+1;
        break;
      }
      l *= 2LL;
      r *= 2LL;
      r++;
    }
    if(d < 0 || d > 60) return 0;
    return res[d];
  }
  
  
  
  template <class F>
  vector<ll> monotone_maxima(F &f, int h, int w) {
      vector<ll> ret(h);
      auto sol = [&](auto &&self, const int l_i, const int r_i, const int l_j, const int r_j) -> void {
          const int m_i = (l_i + r_i) / 2;
          int max_j = l_j;
          ll max_val = -INF;
          for (int j = l_j; j <= r_j; ++j) {
              const ll v = f(m_i, j);
              if (v > max_val) {
                  max_j = j;
                  max_val = v;
              }
          }
          ret[m_i] = max_val;
  
          if (l_i <= m_i - 1) {
              self(self, l_i, m_i - 1, l_j, max_j);
          }
          if (m_i + 1 <= r_i) {
              self(self, m_i + 1, r_i, max_j, r_j);
          }
      };
      sol(sol, 0, h - 1, 0, w - 1);
      return ret;
  }
  
  vector<ll> max_plus_convolution(const vector<ll> &a, const vector<ll> &b) {
      const int n = (int)a.size(), m = (int)b.size();
      auto f = [&](int i, int j) {
          if (i < j or i - j >= m) {
              return -INF;
          }
          return a[j] + b[i - j];
      };
  
      return monotone_maxima(f, n + m - 1, n);
  }