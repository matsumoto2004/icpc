template<typename T>
struct Compress{
    vl origin;
    vl v;
    vl rev;//id -> 元の数字
    map<ll,ll> mp;//元の数字 -> id
    
    Compress(vector<T> v_) : origin(v_) ,rev(v_) {
        sort(all(rev));
        rev.erase(unique(all(rev)),rev.end());
        rep(i,rev.size()) mp[rev[i]]=i;
        rep(i,origin.size()) v.pb(mp[origin[i]]);
    }

};