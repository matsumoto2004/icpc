int lis(const vi &v, bool strict = true) {
    int n = v.size();
    vi dp(n, inf);
    dp[0] = v[0];
    int now = 0;
    rep(i, 1, n)
    {
        if (v[i] > dp[now]) {
            dp[now + 1] = v[i];
            now++;
        } else {
            if (strict) {
                auto it = lower_bound(all(dp), v[i]);
                *it = v[i];
            } else {
                auto it = upper_bound(all(dp), v[i]);
                *it = v[i];
            }
        }
    }
    return now + 1;
}