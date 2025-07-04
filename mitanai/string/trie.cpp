template<int char_size>
struct Node {
    vi next;
    int accept;
    int c;
    
    Node(int c) : next(char_size, -1), accept(0), c(c) {}
};

template<int char_size, int base>
class trie {
    using node = Node<char_size>;
    vector<node> nodes;

public:
    trie() { nodes.pb(node(0)); }
    
    void insert(const string &s) {
        int pos = 0;
        rep(i, s.size()) {
            int c = (int) s[i] - base;
            int &next = nodes[pos].next[c];
            if (next == -1) {
                next = nodes.size();
                nodes.pb(node(c));
            }
            pos = next;
        }
        nodes[pos].accept++;
    }
    
    int count(const string &s) {
        int pos = 0;
        rep(i, s.size()) {
            int c = (int) s[i] - base;
            int &next = nodes[pos].next[c];
            if (next == -1) {
                return 0;
            }
            pos = next;
        }
        return nodes[pos].accept;
    }
};