struct fraction {
    ll first, second;
    
    fraction& normalize() {
        if (second < 0) {
            first *= -1;
            second *= -1;
        }
        ll g = gcd(abs(first), abs(second));
        first /= g;
        second /= g;
        return *this;
    }
    fraction(ll first = 0, ll second = 1) : first(first), second(second) {
        assert(second != 0);
        this->normalize();
    }
    fraction operator-() const { return fraction(-first,second);}
    fraction& operator+=(const fraction &a) {
        first = first * a.second + second * a.first;
        second *= a.second;
        return this->normalize();
    }
    fraction& operator-=(const fraction &a) {
        first = first * a.second - second * a.first;
        second *= a.second;
        return this->normalize();
    }
    fraction& operator*=(const fraction &a) {
        first *= a.first;
        second *= a.second;
        return this->normalize();
    }
    fraction& operator/=(const fraction &a) {
        first *= a.second;
        second *= a.first;
        return this->normalize();
    }
    fraction operator+(const fraction &a) const { fraction res(*this); return res += a; }
    fraction operator-(const fraction &a) const { fraction res(*this); return res -= a; }
    fraction operator*(const fraction &a) const { fraction res(*this); return res *= a; }
    fraction operator/(const fraction &a) const { fraction res(*this); return res /= a; }
    bool isInteger() const { return second == 1; }
    ll toInteger() const {
        assert(this->isInteger());
        return first;
    }
};
bool operator==(const fraction &a,const ll &b) { return a.isInteger() and a.first == b; }
bool operator!=(const fraction &a,const ll &b) { return !(a == b); }
bool operator<(const fraction &a,const ll &b) { return a.first < a.second * b; }
bool operator<=(const fraction &a,const ll &b) { return a < b or a == b; }
bool operator>(const fraction &a,const ll &b) { return a.first > a.second*b; }
bool operator>=(const fraction &a,const ll &b) { return a > b or a == b; }
bool operator==(const fraction &a,const fraction &b) { return a - b == 0; }
bool operator!=(const fraction &a,const fraction &b) { return !(a == b); }
bool operator<(const fraction &a,const fraction &b) { return a - b < 0; }
bool operator<=(const fraction &a,const fraction &b) { return a - b <= 0; }
bool operator>(const fraction &a,const fraction &b) { return a - b > 0; }
bool operator>=(const fraction &a,const fraction &b) { return a - b >= 0; }
ostream& operator<<(ostream &os,const fraction &a) { return os << a.first << '/' << a.second; }
