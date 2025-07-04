ll ok = , ng = ;
auto f = [&](ll x) -> bool {

};
while(abs(ok-ng) > 1) {
    ll mid = (ng+ok)/2;
    if(f(mid)) ok = mid;
    else ng = mid;
}
