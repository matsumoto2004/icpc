
template<class T>
T random(T low, T high)
{
    std::uniform_int_distribution<T> dist(low, high);
    return dist(gen);
}
