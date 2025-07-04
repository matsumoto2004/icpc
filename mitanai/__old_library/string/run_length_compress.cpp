template<class T>
vector <pair<T, int>> run_length_compress(const vector <T> &v) {
    if (v.empty()) return {};
    vector <pair<T, int>> res;
    T now = v[0];
    int cnt = 1;
    rep(i, 1, v.size())
    {
        if (now != v[i]) {
            res.eb(now, cnt);
            now = v[i];
            cnt = 0;
        }
        cnt++;
    }
    res.eb(now, cnt);
    return res;
}

vector <pair<char, int>> run_length_compress(const string &s) {
    if (s.empty()) return {};
    vector <pair<char, int>> res;
    char now = s[0];
    int cnt = 1;
    rep(i, 1, s.size())
    {
        if (now != s[i]) {
            res.eb(now, cnt);
            now = s[i];
            cnt = 0;
        }
        cnt++;
    }
    res.eb(now, cnt);
    return res;
}