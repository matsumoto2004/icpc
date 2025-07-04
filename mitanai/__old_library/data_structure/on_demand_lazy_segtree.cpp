template<class M, class IDX = int>
class lazy_segtree {
    using S = typename M::S;
    using F = typename M::F;
    
    struct Node {
        IDX l, r;
        S d;
        F lz;
        Node *cl, *cr;
        
        Node(int _l, int _r) : l(_l), r(_r), d(M::e), lz(M::id), cl(nullptr), cr(nullptr) {}
    };
    
    IDX n;
    Node *root;
    
    void update(Node *now) {
        S vl = (now->cl == nullptr ? M::e : now->cl->d);
        S vr = (now->cr == nullptr ? M::e : now->cr->d);
        now->d = M::op(vl, vr);
    }
    
    void all_apply(Node *now, F f) {
        now->d = M::mapping(f, now->d);
        if (now->r - now->l > 1) now->lz = M::composition(f, now->lz);
    }
    
    void push(Node *now) {
        if (now->cl != nullptr) all_apply(now->cl, now->lz);
        if (now->cr != nullptr) all_apply(now->cr, now->lz);
        now->lz = M::id;
    }

public:
    constexpr lazy_segtree(IDX _n) : n(_n) {
        root = new Node(0, n);
    }
    
    void set(IDX p, S x) {
        assert(0 <= p and p < n);
        vector < Node * > nodes;
        Node *now = root;
        while (now->r - now->l > 1) {
            IDX m = (now->l + now->r) / 2;
            if (p < m and now->cl == nullptr) now->cl = new Node(now->l, m);
            if (p >= m and now->cr == nullptr) now->cr = new Node(m, now->r);
            nodes.pb(now);
            push(now);
            if (p < m) now = now->cl;
            else now = now->cr;
        }
        now->d = x;
        REV(nodes);
        for (auto i: nodes) update(i);
    }
    
    S get(IDX p) {
        assert(0 <= p and p < n);
        Node *now = root;
        while (now->r - now->l > 1) {
            IDX m = (now->l + now->r) / 2;
            if (p < m and now->cl == nullptr) now->cl = new Node(now->l, m);
            if (p >= m and now->cr == nullptr) now->cr = new Node(m, now->r);
            push(now);
            if (p < m) now = now->cl;
            else now = now->cr;
        }
        return now->d;
    }
    
    S prod(IDX l, IDX r, Node *now = nullptr) {
        assert(l <= r);
        if (now == nullptr) now = root;
        if (now->r <= l or r <= now->l) return M::e;
        if (l <= now->l and now->r <= r) return now->d;
        IDX m = (now->l + now->r) / 2;
        if (now->cl == nullptr) now->cl = new Node(now->l, m);
        if (now->cr == nullptr) now->cr = new Node(m, now->r);
        push(now);
        return M::op(prod(l, r, now->cl), prod(l, r, now->cr));
    }
    
    S all_prod() { return root->d; }
    
    void apply(IDX l, IDX r, F f, Node *now = nullptr) {
        assert(l <= r);
        if (now == nullptr) now = root;
        if (now->r <= l or r <= now->l) return;
        if (l <= now->l and now->r <= r) {
            all_apply(now, f);
            return;
        }
        IDX m = (now->l + now->r) / 2;
        if (now->cl == nullptr) now->cl = new Node(now->l, m);
        if (now->cr == nullptr) now->cr = new Node(m, now->r);
        push(now);
        apply(l, r, f, now->cl);
        apply(l, r, f, now->cr);
        update(now);
    }
    
    template<class F>
    IDX min_left(const F &f, Node *now = nullptr, S s = M::e) {
        if (now == nullptr) now = root;
        if (now->r - now->l == 1) return now->r;
        IDX m = (now->l + now->r) / 2;
        if (now->cl == nullptr) now->cl = new Node(now->l, m);
        if (now->cr == nullptr) now->cr = new Node(m, now->r);
        push(now);
        if (!f(M::op(now->cr->d, s))) return min_left(f, now->cr, s);
        else return min_left(f, now->cl, M::op(now->cr->d, s));
    }
};

class M {
public:
    using S = ;
    
    static constexpr S
    e =;
    
    static constexpr S
    
    op(const S &l, const S &r) {
        return;
    }
    
    using F = ;
    
    static constexpr F
    id =;
    
    static constexpr F
    
    composition(const F &g, const F &f) {
        return;
    }
    
    static constexpr S
    
    mapping(const F &f, const S &x) {
        return;
    }
};

