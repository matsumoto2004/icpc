// v[i] = {a_i, r_i}
//     where sequence i is a_i / (1 - r_i * x)
// calc [x^i] (sum of sequences) for i in [0, m)
// time complexity : O(n log^2 n + m log m)
fps sum_of_geometric_sequences(const vector <pair<mint, mint>> &v, int m) {
    int n = SZ(v);
    vector <pair<fps, fps>> q;
    rep(i, n)
    q.eb(fps({v[i].first}), fps({1, -v[i].second}));
    while (SZ(q) > 1) {
        vector <pair<fps, fps>> nq;
        nq.reserve((SZ(q) + 1) / 2);
        rep(i, 0, SZ(q), 2)
        {
            if (i + 1 < SZ(q)) {
                nq.eb(q[i].first * q[i + 1].second + q[i + 1].first * q[i].second, q[i].second * q[i + 1].second);
            } else {
                nq.pb(q[i]);
            }
        }
        swap(q, nq);
    }
    return q[0].first.divide(q[0].second, m);
}
