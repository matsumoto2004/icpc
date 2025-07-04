// -pi to pi
// no (0, 0)
bool arg_cmp(const LP &a, const LP &b) {
    int ua = a.second > 0 or (a.second == 0 and a.first >= 0);
    int ub = b.second > 0 or (b.second == 0 and b.first >= 0);
    if (ua == ub) {
        ll tmp = a.first * b.second - a.second * b.first;
        if (tmp != 0) return tmp > 0;
        else return a.first ? abs(a.first) < abs(b.first) : abs(a.second) < abs(b.second);
    } else return ua < ub;
}