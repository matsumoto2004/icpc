// https://noshi91.hatenablog.com/entry/2021/06/29/044225#2
// formulation :
//      minimize \sum_i \theta_i(x_i) + \sum_{i<j} \phi_{i,j}(x_i,x_j)
//      subject to x \in {0,...,k-1}^n
// constraint :
//      \phi_{i,j} satisfies monge property.
// time complexity :
//      |V| (of flow graph) = O(Nk)
//      |E| (of flow graph) = O(N^2k^2)
//      dinic algorithm : O(N^4k^4)
template<class T>
T min_cut_k(int n, int k, const vector <vector<T>> &theta, const vector <vector<vector < vector < T>>

>> &phi) {
assert(k
>= 2);

assert (SZ(theta)

== n);
rep(i, n
)

assert (SZ(theta[i])

== k);

assert (SZ(phi)

== n);
rep(i, n
)

assert (SZ(phi[i])

== n);
rep(i, n
)
rep(j, i
+ 1, n) {
assert (SZ(phi[i][j])

== k);
rep(p, k
)

assert (SZ(phi[i][j][p])

== k);
}

dinic <T> dc(n * (k - 1) + 2);
int s = n * (k - 1), t = s + 1;
auto toId = [&](int i, int j) {
    return i * (k - 1) + j;
};
T add = 0;
vector <vector<T>> v(n * (k - 1), vector<T>(2));
rep(i, n
)
rep(j, i
+ 1, n) {
const vector <vector<T>> &now = phi[i][j];
add += now[0][0];
rep(p, k
- 1) {
v[
toId(i, p
)][0] += now[p + 1][0] - now[p][0];
v[
toId(j, p
)][0] += now[0][p + 1] - now[0][p];
}
rep(p, k
- 1)
rep(q, k
- 1) {
T tmp = now[p][q] + now[p + 1][q + 1] - now[p][q + 1] - now[p + 1][q];
assert(tmp
<= 0);
add +=
tmp;
v[
toId(i, p
)][1] += -
tmp;
dc.
add_edge(toId(i, p), toId(j, q),
-tmp);
}
}
rep(i, n
) {
rep(j, k
- 2) dc.
add_edge(toId(i, j + 1), toId(i, j), numeric_limits<T>::max()
);
add += theta[i][k - 1];
rep(j, k
- 1) {
v[
toId(i, j
)][1] += theta[i][j] - theta[i][j + 1];
T mn = min(v[toId(i, j)][0], v[toId(i, j)][1]);
add +=
mn;
dc.
add_edge(s, toId(i, j), v[toId(i, j)][1]
- mn);
dc.
add_edge(toId(i, j), t, v[toId(i, j)][0]
- mn);
}
}
return add + dc.
max_flow(s, t
);
}
