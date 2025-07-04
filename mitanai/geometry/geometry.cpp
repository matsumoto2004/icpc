const double eps = 1e-9;
const double PI = acos(-1);

int sgn(double a) { return a < -eps ? -1 : (a > eps ? 1 : 0); }

double to_rad(double deg) { return deg * PI / 180; }

double to_deg(double rad) { return rad * 180 / PI; }

struct point {
    double x, y;

    point(double x = 0, double y = 0) : x(x), y(y) {}

    point operator+(const point &p) const { return {x + p.x, y + p.y}; }

    point operator-(const point &p) const { return {x - p.x, y - p.y}; }

    point operator*(double a) const { return {x * a, y * a}; }

    point operator*(const point &p) const { return point(x * p.x - y * p.y, x * p.y + y * p.x); }

    point operator/(double a) const { return {x / a, y / a}; }

    point operator-() const { return *this * (-1); }

    bool operator==(const point &p) const { return !sgn(x - p.x) && !sgn(y - p.y); }

    bool operator!=(const point &p) const { return !(*this == p); }

    bool operator<(const point &p) const { return sgn(x - p.x) ? x < p.x : sgn(y - p.y) == -1; }

    bool operator>(const point &p) const { return sgn(x - p.x) ? x > p.x : sgn(y - p.y) == 1; }

    double norm() const { return x * x + y * y; }

    double abs() const { return sqrt(norm()); }

    point rot(double rad) const { return point(cos(rad) * x - sin(rad) * y, sin(rad) * x + cos(rad) * y); }

    point rot90() const { return point(-y, x); }

    double arg() const {
        double res = atan2(y, x);
        if (sgn(res) < 0) res += 2 * PI;
        return res;
    }
};

istream &operator>>(istream &is, point &p) { return is >> p.x >> p.y; }

ostream &operator<<(ostream &os, const point &p) { return os << '(' << p.x << "," << p.y << ')'; }

double dist(const point &a, const point &b) { return (a - b).abs(); }

double dot(const point &a, const point &b) { return a.x * b.x + a.y * b.y; }

double cross(const point &a, const point &b) { return a.x * b.y - a.y * b.x; }

point mid(const point &a, const point &b) { return (a + b) / 2; }

int ccw(const point &a, const point &b, const point &c) {
    // 1 -> c is upper than line(a,b)
    // -1 -> c is lower than line(a,b)
    // 2 -> in order [a,b,c]
    // -2 -> in order [c,a,b]
    // 0 -> in order [a,c,b]
    point nb = b - a, nc = c - a;
    if (sgn(cross(nb, nc))) return sgn(cross(nb, nc));
    if (sgn(dot(nb, nc)) < 0) return -2;
    if (sgn(nc.abs() - nb.abs()) > 0) return 2;
    return 0;
}

struct line {
    point a, b;

    line(point a = point(), point b = point()) : a(a), b(b) {}

    bool online(const point &p) const { return abs(ccw(a, b, p)) != 1; }
};

ostream &operator<<(ostream &os, const line &l) { return os << '{' << l.a << ',' << l.b << '}'; }

struct segment {
    point a, b;

    segment(point a = point(), point b = point()) : a(a), b(b) {}

    bool online(const point &p) const { return !ccw(a, b, p); }

    line vertical_bisector() const { return line(mid(a, b), mid(a, b) + (b - a).rot90()); }
};

ostream &operator<<(ostream &os, const segment &l) { return os << '{' << l.a << ',' << l.b << '}'; }

bool vertical(const line &l, const line &m) { return !sgn(dot(l.a - l.b, m.a - m.b)); }

bool vertical(const segment &l, const segment &m) { return !sgn(dot(l.a - l.b, m.a - m.b)); }

bool parallel(const line &l, const line &m) { return !sgn(cross(l.a - l.b, m.a - m.b)); }

bool parallel(const segment &l, const segment &m) { return !sgn(cross(l.a - l.b, m.a - m.b)); }

bool operator==(const line &l, const line &m) { return parallel(l, m) && l.online(m.a); }

bool operator!=(const line &l, const line &m) { return !(l == m); }

bool operator==(const segment &l, const segment &m) { return l.a == m.a && l.b == m.b || l.a == m.b && l.b == m.a; }

bool operator!=(const segment &l, const segment &m) { return !(l == m); }

// intersect at one point
bool intersect(const line &l, const line &m) { return !parallel(l, m); }

bool intersect(const line &l, const segment &m) {
    return sgn(cross(l.b - l.a, m.a - l.a) * cross(l.b - l.a, m.b - l.a)) <= 0;
}

bool intersect(const segment &l, const segment &m) {
    return ccw(l.a, l.b, m.a) * ccw(l.a, l.b, m.b) <= 0 &&
           ccw(m.a, m.b, l.a) * ccw(m.a, m.b, l.b) <= 0;
}

point intersection(const line &l, const line &m) {
    assert(intersect(l, m));
    return l.a + (l.b - l.a) * cross(m.b - m.a, m.a - l.a) / cross(m.b - m.a, l.b - l.a);
}

point intersection(const line &l, const segment &m) {
    assert(intersect(l, m));
    return l.a + (l.b - l.a) * cross(m.b - m.a, m.a - l.a) / cross(m.b - m.a, l.b - l.a);
}

point intersection(const segment &l, const segment &m) {
    assert(intersect(l, m));
    return l.a + (l.b - l.a) * cross(m.b - m.a, m.a - l.a) / cross(m.b - m.a, l.b - l.a);
}

double dist(const line &l, const point &p) { return abs(cross(l.b - l.a, p - l.a)) / (l.b - l.a).abs(); }

double dist(const segment &l, const point &p) {
    if (sgn(dot(l.b - l.a, p - l.a)) < 0) return dist(p, l.a);
    if (sgn(dot(l.a - l.b, p - l.b)) < 0) return dist(p, l.b);
    return dist(line(l.a, l.b), p);
}

double dist(const line &l, const line &m) {
    if (parallel(l, m)) return dist(l, m.a);
    return 0;
}

double dist(const line &l, const segment &m) {
    if (intersect(l, m)) return 0;
    return min(dist(l, m.a), dist(l, m.b));
}

double dist(const segment &l, const segment &m) {
    if (intersect(l, m)) return 0;
    return min({dist(l, m.a), dist(l, m.b), dist(m, l.a), dist(m, l.b)});
}

point projection(const line &l, const point &p) {
    double d = dot(p - l.a, l.b - l.a) / (l.b - l.a).norm();
    return l.a + (l.b - l.a) * d;
}

point circumcenter(const point &a, const point &b, const point &c) {
    return intersection(segment(a, b).vertical_bisector(), segment(b, c).vertical_bisector());
}

struct circle {
    point o;
    double r;

    circle(point o = point(), double r = 0) : o(o), r(r) {}

    bool inside(const point &p) const { return sgn(r - dist(o, p)) >= 0; }

    double area() const { return r * r * PI; }
};

ostream &operator<<(ostream &os, const circle &c) { return os << '{' << c.o << ',' << c.r << '}'; }

bool intersect(const circle &c, const line &l) { return sgn(dist(l, c.o) - c.r) <= 0; }

bool intersect(const circle &c, const segment &l) {
    if (sgn(dist(l, c.o) - c.r) > 0) return false;
    return sgn(max((c.o - l.a).abs(), (c.o - l.b).abs()) - c.r) >= 0;
}

vector <point> intersection(const circle &c, const line &l) {
    point p = projection(l, c.o);
    if (!intersect(c, l)) return {};
    if (sgn(dist(l, c.o) - c.r) == 0) return {p};
    point e = (l.b - l.a) / (l.b - l.a).abs();
    double d = sqrt(c.r * c.r - (p - c.o).norm());
    return {p - e * d, p + e * d};
}

vector <point> intersection(const circle &c, const segment &l) {
    auto v = intersection(c, line(l.a, l.b));
    vector <point> ret;
    for (point p: v) if (l.online(p)) ret.pb(p);
    return ret;
}

vector <point> intersection(const circle &a, const circle &b) {
    double d = dist(a.o, b.o);
    if (!sgn(a.r + b.r - d)) return {a.o + (b.o - a.o) * a.r / d};
    if (!sgn(a.r - b.r - d)) return {a.o + (b.o - a.o) * a.r / d};
    if (!sgn(b.r - a.r - d)) return {b.o + (a.o - b.o) * b.r / d};
    if (sgn(abs(a.r - b.r) - d) > 0 || sgn(a.r + b.r - d) < 0) return {};
    double x = (a.r * a.r + d * d - b.r * b.r) / (2 * d);
    double y = sqrt(a.r * a.r - x * x);
    point p = (b.o - a.o).rot90() * y / d;
    point to_mid = a.o + (b.o - a.o) * x / d;
    return {to_mid - p, to_mid + p};
}

vector <circle> circle_with_two_points_and_radius(const point &a, const point &b, const double &r) {
    if (sgn(dist(a, b) - 2 * r) > 0) return {};
    circle A(a, r), B(b, r);
    auto v = intersection(A, B);
    vector <circle> ret;
    for (point p: v) ret.eb(p, r);
    return ret;
};

vector <point> tangent_point(const circle &c, const point &p) {
    int s = sgn(dist(c.o, p) - c.r);
    if (s < 0) return {};
    if (s == 0) return {p};
    double d = (p - c.o).norm() - c.r * c.r;
    return intersection(c, circle(p, sqrt(d)));
}

vector <line> tangent_line(const circle &c, const point &p) {
    vector <point> v = tangent_point(c, p);
    if (v.empty()) return {};
    if (v.size() == 1) return {line(p, p + (c.o - p).rot90())};
    vector <line> res;
    for (auto tp: v) res.eb(p, tp);
    return res;
}

vector <line> tangent_line(const circle &a, const circle &b) {
    if (sgn(a.r - b.r) < 0) return tangent_line(b, a);
    double ar = a.r, br = b.r, d = dist(a.o, b.o);
    if (sgn(d - (ar - br)) < 0) return {};
    else if (sgn(d - (ar - br)) == 0) {
        point p = (a.o * (-br) + b.o * ar) / (ar - br);
        return {line(p, p + (a.o - p).rot90())};
    } else {
        vector <line> res;
        {
            double theta = acos((ar - br) / d);
            {
                point p = a.o + ((b.o - a.o) / d * ar).rot(-theta);
                res.eb(p, p + (a.o - p).rot90());
            }
            {
                point p = a.o + ((b.o - a.o) / d * ar).rot(theta);
                res.eb(p, p + (a.o - p).rot90());
            }
        }
        if (sgn(d - (ar + br)) >= 0) {
            point p = (a.o * br + b.o * ar) / (ar + br);
            vector <line> lines = tangent_line(a, p);
            for (line l: lines) res.pb(l);
        }
        return res;
    }
}

vector <point> convex_hull(vector <point> v) {
    sort(all(v));
    int n = v.size(), k = 0;
    vector <point> res(2 * n);
    for (int i = 0; i < n; res[k++] = v[i++])
        while (k > 1 && ccw(res[k - 2], res[k - 1], v[i]) <= 0) k--;
    for (int i = n - 2, t = k; i >= 0; res[k++] = v[i--])
        while (k > t && ccw(res[k - 2], res[k - 1], v[i]) <= 0) k--;
    res.resize(k - 1);
    return res;
}