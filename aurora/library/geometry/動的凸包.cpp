template<typename F>
struct FixPoint : F {
  explicit FixPoint(F &&f) : F(forward<F>(f)) {}

  template<typename... Args>
  decltype(auto) operator()(Args &&...args) const {
    return F::operator()(*this, forward<Args>(args)...);
  }
};

template<typename F>
inline decltype(auto) MFP(F &&f) {
  return FixPoint<F>{forward<F>(f)};
}

template<typename T>
struct Point {
  T x, y;
  Point(const T &x, const T &y) : x{x}, y{y} {}
  Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
  Point operator-() const { return {-x, -y}; }

  bool operator<(const Point &p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }

  T det(const Point &p) const { return x * p.y - y * p.x; }
};

template<typename T, bool strict = true>
struct IncrementalLowerConvexHull {
  using P = Point<T>;
  set<P> S;
  template<typename ADD_V, typename RM_V, typename ADD_E, typename RM_E>
  void add_point(const P &p, ADD_V add_v, RM_V rm_v, ADD_E add_e, RM_E rm_e) {
    int s = side(p);
    if (strict && s >= 0) return;
    if (not strict && s > 0) return;

    add_v(p);
    S.insert(p);
    vector<P> left, right;
    
    for (auto it = S.find(p); it != S.begin();) {
      --it;
      if (left.empty()) {
        left.emplace_back(*it);
      } else {
        auto a = *it;
        auto b = left.back();
        auto det = (b - a).det(p - a);
        if (strict && det > 0) break;
        if (!strict && det >= 0) break;
        left.emplace_back(a);
      }
    }

    for (auto it = S.upper_bound(p); it != S.end(); ++it) {
      if (right.empty()) {
        right.emplace_back(*it);
      } else {
        auto a = right.back();
        auto b = *it;
        auto det = (a - p).det(b - p);
        if (strict && det > 0) break;
        if (!strict && det >= 0) break;
        right.emplace_back(b);
      }
    }

    if (left.size() > 1) {
      S.erase(next(S.find(left.back())), S.find(p));
    }
    if (right.size() > 1) {
      S.erase(next(S.find(p)), S.find(right.back()));
    }
    for (int i = 0; i + 1 < left.size(); i++) {
      rm_v(left[i]);
    }
    for (int i = 0; i + 1 < right.size(); i++) {
      rm_v(right[i]);
    }

    if (not left.empty() && not right.empty()) {
      auto a = left[0], b = right[0];
      rm_e(a, b);
      a.det(b);
    }
    for (int i = 0; i + 1 < left.size(); i++) {
      auto a = left[i + 1], b = left[i];
      rm_e(a, b);
    }
    for (int i = 0; i + 1 < right.size(); i++) {
      auto a = right[i], b = right[i + 1];
      rm_e(a, b);
    }

    if (not left.empty()) {
      add_e(left.back(), p);
    }
    if (not right.empty()) {
      add_e(p, right.back());
    }
  }

  int side(const P &p) const {
    auto r = S.lower_bound(p);
    if (r == S.begin() or r == S.end()) {
      return -1;
    }
    auto l = prev(r);
    auto p1 = *l, p2 = *r;
    auto det = (p - p1).det(p2 - p1);
    return det == 0 ? 0 : (det > 0 ? -1 : 1);
  }
};

template<typename T, bool strict = true>
struct IncrementalConvexHull {
  using P = Point<T>;
  IncrementalLowerConvexHull<T, strict> LOWER, UPPER;
  int cnt_V, cnt_E;
  T det_sum;

  IncrementalConvexHull() : cnt_V(-2), cnt_E(0), det_sum(0) {}

  int size() const {
    return V();
  }

  bool empty() const { return cnt_V == -2; }

  int V() const {
    if (det_sum == 0) return 2;
    return cnt_V - 2;
  }

  int E() const {
    return cnt_E;
  }

  template<typename REAL>
  REAL area() {
    return det_sum * 0.5;
  }

  template<enable_if_t<is_integral<T>::value, int> = 0>
  bool area_2() {
    return det_sum;
  }

  template<typename ADD_V, typename RM_V, typename ADD_E, typename RM_E>
  void add_point(const P &p, ADD_V add_v, RM_V rm_v, ADD_E add_e, RM_E rm_e) {
    LOWER.add_point(
        p,
        [&](const P &p) {
          add_v(p);
          ++cnt_V;
        },
        [&](const P &p) {
          rm_v(p);
          --cnt_V;
        },
        [&](const P &a, const P &b) {
          add_e(a, b);
          ++cnt_E;
          det_sum += a.det(b);
        },
        [&](const P &a, const P &b) {
          rm_e(a, b);
          --cnt_E;
          det_sum -= a.det(b);
        });
    UPPER.add_point(
        -p,
        [&](const P &p) {
          add_v(-p);
          ++cnt_V;
        },
        [&](const P &p) {
          rm_v(-p);
          --cnt_V;
        },
        [&](const P &a, const P &b) {
          add_e(-a, -b);
          ++cnt_E;
          det_sum += a.det(b);
        },
        [&](const P &a, const P &b) {
          rm_e(-a, -b);
          --cnt_E;
          det_sum -= a.det(b);
        });
  }

  void add_point(const P &p) {
    add_point(p, [](const P &p) {}, [](const P &p) {}, [](const P &s, const P &t) {},
              [](const P &s, const P &t) {});
  }

  int side(const P &p) const {
    int a = LOWER.side(p);
    int b = UPPER.side(-p);
    if (a == 0 || b == 0) return 0;
    return min(a, b);
  }
};

/*
int main() {
  IncrementalConvexHull<int64> X;
  int N;
  cin >> N;
  while (N--) {
    string S;
    cin >> S;
    int64 x, y;
    cin >> x >> y;
    Point<int64> p(x, y);
    if (S == "TARGET") {
      cout << (X.side(p) == -1 ? "SAFE" : "DANGER") << "\n";
    } else {
      X.add_point(p);
    }
  }
}*/