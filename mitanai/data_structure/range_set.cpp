template<class T>
class range_set {
    set <pair<T, T>> st;
    using iter = typename set<pair < T, T>>::
    iterator;

    iter find_first(T p) {
        auto it = st.lower_bound({p, p});
        if (it != st.begin() and prev(it)->second >= p) return prev(it);
        return it;
    }

public:
    range_set() {}

    vector <pair<T, T>> insert(T l, T r) {
        if (l >= r) return {};
        vector <pair<T, T>> del;
        iter it = find_first(l);
        T nl = l, nr = r;
        while (it != st.end() and it->first <= r) {
            nl = min(nl, it->first);
            nr = max(nr, it->second);
            del.push_back(*it);
            it = st.erase(it);
        }
        st.insert({nl, nr});
        if (del.empty()) return {{nl, nr}};
        vector <pair<T, T>> res;
        if (nl < del[0].first) res.emplace_back(nl, del[0].first);
        rep(i, SZ(del) - 1)
        {
            res.emplace_back(del[i].second, del[i + 1].first);
        }
        if (nr > del.back().second) res.emplace_back(del.back().second, nr);
        return res;
    }

    vector <pair<T, T>> erase(T l, T r) {
        if (l >= r) return {};
        vector <pair<T, T>> res, add;
        iter it = find_first(l + 1);
        while (it != st.end() and it->first < r) {
            if (l <= it->first and it->second <= r) {
                res.push_back(*it);
            } else if (l > it->first) {
                assert(l < it->second);
                res.emplace_back(l, min(r, it->second));
                add.emplace_back(it->first, l);
                if (r < it->second) add.emplace_back(r, it->second);
            } else {
                res.emplace_back(it->first, r);
                add.emplace_back(r, it->second);
            }
            it = st.erase(it);
        }
        for (auto p: add) st.insert(p);
        return res;
    }
};