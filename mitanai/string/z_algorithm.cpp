vi z_algorithm(const string &s) {
    if (s.empty()) return {};
    vi res(s.size());
    res[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
        while (i + j < s.size() and s[j] == s[i + j]) j++;
        res[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < s.size() and k + res[k] < j) res[i + k] = res[k], k++;
        i += k, j -= k;
    }
    return res;
}