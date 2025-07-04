using comp = complex<double>;

const double PI = acos(-1);

// Fast Fourier Transform
void fft(vector<comp> &v, bool inverse = false) {
    int n = v.size();
    int h = __builtin_ctz(n);
    assert(1 << h == n);
    rep(i, n) {
        int j = 0;
        rep(k, h) j |= (i >> k & 1) << (h - 1 - k);
        if (i < j) swap(v[i], v[j]);
    }
    // b * 2 -> size of block
    for (int b = 1; b < n; b *= 2) {
        rep(j, b) {
            comp w = polar(1.0, (2 * PI) / (2 * b) * j * (inverse ? 1 : -1));
            for (int k = 0; k < n; k += b * 2) {
                comp s = v[j + k];
                comp t = v[j + k + b] * w;
                v[j + k] = s + t;
                v[j + k + b] = s - t;
            }
        }
    }
    if (inverse) rep(i, n) v[i] /= n;
}

// sum_{i + j = k} {a_i * b_j} = c_k
vd convolution(const vd &a, const vd &b) {
    int s = a.size() + b.size() - 1;
    int t = 1;
    while (t < s) t *= 2;
    vector<comp> A(t), B(t);
    rep(i, a.size()) A[i] = comp(a[i], 0);
    rep(i, b.size()) B[i] = comp(b[i], 0);
    fft(A);
    fft(B);
    rep(i, t) A[i] *= B[i];
    fft(A, true);
    vd res(s);
    rep(i, s) res[i] = A[i].real();
    return res;
}

vl convolution(const vi &f, const vi &g) {
    vd nf(f.size()), ng(g.size());
    rep(i, f.size()) nf[i] = f[i];
    rep(i, g.size()) ng[i] = g[i];
    vd v = convolution(nf, ng);
    vl res(v.size());
    rep(i, v.size()) res[i] = llround(move(v[i]));
    return res;
}

