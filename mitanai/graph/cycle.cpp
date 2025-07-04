// find cycle of functional graph
pair <vb, vvi> find_cycle(const vi &to) {
    int n = to.size();
    vb res(n);
    vi seen(n);
    vvi cycles;
    rep(i, n)
    {
        if (seen[i]) continue;
        vi ls;
        int now = i;
        while (true) {
            ls.pb(now);
            seen[now] = 1;
            now = to[now];
            if (seen[now] == 2) break;
            if (seen[now] == 1) {
                rrep(j, SZ(ls))
                {
                    if (ls[j] == now) {
                        cycles.pb({});
                        rep(k, j, SZ(ls))
                        {
                            res[ls[k]] = true;
                            cycles.back().pb(ls[k]);
                        }
                        break;
                    }
                }
                break;
            }
        }
        for (int j: ls) seen[j] = 2;
    }
    return {res, cycles};
}