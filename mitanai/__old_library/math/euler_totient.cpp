int euler_totient(int n) {
    prime<int> pr(n);
    auto fac = pr.unique_factor();
    int phi = n;
    for (int p : fac) {
        phi /= p;
        phi *= p - 1;
    }
    return phi;
}