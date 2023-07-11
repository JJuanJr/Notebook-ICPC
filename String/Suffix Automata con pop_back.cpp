//codeforces.com/gym/103185/submission/122711694
struct suffixAutomata {
    struct node {
        int len, link, cnt;
        int next[26];
    };

    vector<node> sa;
    vector<int> last, p1, p2, q1, qlink;
    ll ans = 0;
    string s;

    suffixAutomaton(int mx_len) {
        sa.reserve(mx_len*2);
        last.pb(add_node());
        sa[0].link = -1;
    }

    int add_node() { sa.pb({}); return sa.size()-1; }

    void add_char(char ch) {
        s.pb(ch);
        int c = ch-'A';
        int u = add_node(), p = last.back();
        sa[u].len = sa[p].len + 1;
        while (p != -1 && !sa[p].next[c]) {
            sa[p].next[c] = u;
            p = sa[p].link;
        }
        p1.pb(p);
        if (p != -1) {
            int q = sa[p].next[c];
            q1.pb(q);
            if (sa[p].len + 1 != sa[q].len) {
                int clone = add_node();
                sa[clone] = sa[q];
                sa[clone].len = sa[p].len + 1;
                qlink.pb(sa[q].link);
                sa[q].link = sa[u].link = clone;
                while (p != -1 && sa[p].next[c] == q) {
                    sa[p].next[c] = clone;
                    p = sa[p].link;
                }
                p2.pb(p);
            } else sa[u].link = q;
            int v = sa[u].link;
            if (!sa[v].cnt) ans += sa[v].len - sa[sa[v].link].len;
            sa[v].cnt++;
        }
        last.pb(u);
    }

    void pop_back() {
        int c = s.back()-'A'; s.pop_back();
        int u = last.back(); last.pop_back();
        int p = last.back();
        while (p != p1.back()) {
            sa[p].next[c] = 0;
            p = sa[p].link;
        }
        p1.pop_back();
        if (p != -1) {
            int v = sa[u].link;
            sa[v].cnt--;
            if (!sa[v].cnt) ans -= sa[v].len - sa[sa[v].link].len;
            int q = q1.back(); q1.pop_back();
            if (sa[p].len + 1 != sa[q].len) {
                sa[q].link = qlink.back(); qlink.pop_back();
                while (p != p2.back()) {
                    sa[p].next[c] = q;
                    p = sa[p].link;
                }
                p2.pop_back();
                sa.pop_back();
            }
        }
        sa.pop_back();
    }
    
    node& operator[](int i) { return sa[i]; }
};
