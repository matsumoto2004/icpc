int ok = , ng = ;
auto f = [&](int x) {

};
while(abs(ok-ng) > 1) {
    int mid = (ng+ok)/2;
    if(f(mid)) ok = mid;
    else ng = mid;
}