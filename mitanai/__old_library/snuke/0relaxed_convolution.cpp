struct RelaxedConvolution {
  vector<mint> a, b, c;
  int k;
  RelaxedConvolution(int n): a(n), b(n), c(n), k(0) {}
  mint operator()(mint na, mint nb) {
    a[k] = na; b[k] = nb;
    int s = k+2;
    for (int w = 1; s%w == 0 && w < s; w <<= 1) {
      rep(ri,2) {
        if (ri == 0 || w*2 != s) {
          vector<mint> f(w), g(w);
          rep(i,w) f[i] = a[w-1+i], g[i] = b[k-w+1+i];
          f = convolution(f,g);
          for (int i = 0, j = k; i < f.size() && j < c.size(); i++, j++) c[j] += f[i];
        }
        swap(a,b);
      }
    }
    return c[k++];
  }
};