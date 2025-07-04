template<class T>
void resemble(vector <T> &v) {}

template<class T, class... Tail>
void resemble(vector <T> &v, vector <T> &head, Tail &...tail) {
    for (T &e : head) v.pb(e);
    resemble(v, tail...);
}

template<class T>
void renumber(vector <T> &v) {}

template<class T, class... Tail>
void renumber(vector <T> &v, vector <T> &head, Tail &...tail) {
    for (T &e : head) e = lower_bound(all(v), e) - v.begin();
    renumber(v, tail...);
}

template<class T, class... Tail>
vector <T> zip(vector <T> &head, Tail &... tail) {
    vector <T> v;
    resemble(v, head, tail...);
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    renumber(v, head, tail...);
    return v;
}
