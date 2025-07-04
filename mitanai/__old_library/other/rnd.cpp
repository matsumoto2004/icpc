random_device seed_gen;
mt19937_64 engine(seed_gen());

template<class T>
T rnd(T min_val, T max_val) {
    assert(min_val <= max_val);
    uniform_int_distribution <T> dist(min_val, max_val);
    return dist(engine);
}

template<>
double rnd(double min_val, double max_val) {
    assert(min_val - 1e8 <= max_val);
    uniform_real_distribution<double> dist(min_val, max_val);
    return dist(engine);
}