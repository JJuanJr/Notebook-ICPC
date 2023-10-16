Construye un arbol con los sufijos de una string S.
Sirve para contar ocurrencias o para verificar que un sufijo pertenezca a S.
Para verificar el sufijo, haga lo mismo que en match_str.

struct suffixAutomaton {
    struct node {
        int len, link; bool end;
        map<char, int> next;
        int cnt; ll in, out, cntSubstrs;
    };

    vector<node> sa;
     //ocurrencias de estados, usar encontrar kth pequeña lexico all strings
    vector<ll> cntState; 
    int last; ll substrs = 0;

    suffixAutomaton() {}
    suffixAutomaton(string &s) {
        sa.reserve(sz(s)*2);
        // cntState.reserve(sz(s)*2); 
        last = add_node();
        sa[0].link = -1;
        sa[0].in = 1;
        for (char &c : s) add_char(c);
        for (int p = last; p; p = sa[p].link) sa[p].end = 1;
    }

    int add_node() { sa.pb({}); return sa.size()-1; }

    void add_char(char c) {
        int u = add_node(), p = last;
        // cntState[u] = 1;
        sa[u].len = sa[last].len + 1;
        while (p != -1 && !sa[p].next.count(c)) {
            sa[p].next[c] = u;
            sa[u].in += sa[p].in;
            substrs += sa[p].in;
            p = sa[p].link;
        }
        if (p != -1) {
            int q = sa[p].next[c];
            if (sa[p].len + 1 != sa[q].len) {
                int clone = add_node();
                // cntState[clone] = 0;
                sa[clone] = sa[q];
                sa[clone].len = sa[p].len + 1;
                sa[clone].in = 0;
                sa[q].link = sa[u].link = clone;
                while (p != -1 && sa[p].next[c] == q) {
                    sa[p].next[c] = clone;
                    sa[q].in -= sa[p].in;
                    sa[clone].in += sa[p].in;
                    p = sa[p].link;
                }
            } else sa[u].link = q;
        }
        last = u;
    }
    //Cuenta la cantidad de ocurrencias de una cadena s
    int match_str(string &s) {
        int u = 0, n = sz(s);
        for (int i = 0; i < n; ++i) {
            if (!sa[u].next.count(s[i])) return 0;
            u = sa[u].next[s[i]];
        }
        return count_occ(u);
    }

    int count_occ(int u) {
        if (sa[u].cnt != 0) return sa[u].cnt;
        sa[u].cnt = sa[u].end;
        for (auto &v : sa[u].next)
            sa[u].cnt += count_occ(v.ss);
        return sa[u].cnt;
    }
    
    //Calcular la cantidad de caminos que pertenecen al estado ti, desde ti hasta tn
    ll count_paths(int u) {
        //Out cuenta la cantidad de caminos (cantidad de cadenas distintas)
        if (sa[u].out != 0) return sa[u].out; //sa[u].cntSubstrs != 0 return sa[u].cntSubstrs
        for (auto &v : sa[u].next)
            sa[u].out += count_paths(v.ss); //sa[u].cntSubstrs += count_paths(v.ss)
        return ++sa[u].out; //sa[u].cntSubstrs += cntState[u];
    }
    
    //kth subcadena más pequeña en orden lexicográfico
    //out para cadenas distintas, cntSubstrs para todas las cadenas llamar antes pre
    string kth;
    void dfs_kth(int u, ll &k){ //Antes llamar a count
        if(k == 0) return; // k < cntState[u] para todas las cadenas
        k--; // k -= cntState[u];
        for(auto &v : sa[u].next){
            if(k < sa[v.ss].out){ //k < sa[v.ss].cntSubstrs
                kth += v.ff;
                return dfs_kth(v.ss, k);
            }
            k -= sa[v.ss].out; //k -= sa[v.ss],cntSubstrs
        }
    }
    //calcula la cantidad de ocurrencias de los estados
    void pre(){
        vector<ii> v(sz(sa));
        forn(i, sz(sa)) v[i] = {sa[i].len, i};
        sort(all(v), greater<ii>());
        for(auto &it : v){
            int u = it.ss;
            if(sa[u].link != -1)
                cntState[sa[u].link] += cntState[u];
        }
        cntState[0] = 1;
    }
    //longest common substring
    int lcs(string &t){
        int n = sz(t);
        int u = 0, l = 0, best = 0, bestPosition = 0;
        forn(i, n){
            while(u && !sa[u].next.count(t[i])){
                u = sa[u].link;
                l = sa[u].len;
            }
            if(sa[u].next.count(t[i])) u = sa[u].next[t[i]], l++;
            if(best < l) best = l, bestPosition = i;
        }
        return best;
    }
    vector<int> LCS, match;
    void lcsMatch(string &t){
        match.assign(sz(sa), 0); //usar pivote si toca resetear mucho
        int u = 0, l = 0;
        for(int i = 0 ; i < sz(t) ; ++i){
            while(u && !sa[u].next.count(t[i])){
                u = sa[u].link;
                l = sa[u].len;
            }
            if(sa[u].next.count(t[i])) u = sa[u].next[t[i]], l++;
            match[u] = max(match[u], l);
        }
        for(int i = sz(sa) - 1 ; i > 0 ; --i)
            match[i] = max(match[i], match[sa[i].link]);
        for(int i = 0 ; i < sz(sa) ; ++i)
            LCS[i] = min(LCS[i], match[i]);
    }

    //longest common substring de n cadenas
    int lcs_n(vector<string> &t){
        const int INF = 1e7;
        LCS.assign(sz(sa), INF);
        forn(i, sz(t)) lcsMatch(t[i]);
        return *max_element(all(LCS));
    }

    //longitud desde 1 hasta N, return v donde v[i] = num distintas substr de i longitud
    vector<int> substringDistribution(int lenCadena){
        vector<int> st(lenCadena + 5);
        forn(i, sz(sa)){
            int l = sa[sa[i].link].len + 1; // l minlen subcadena que pertenece al conjunto sa[i]
            int r = sa[i].len; // r maxlen subcadena que pertenece al conjunto s[i]
            if(l > 0) st[l]++, st[r + 1]--;
        }
        forn(i, lenCadena + 1) st[i + 1] += st[i];
        return st;
    }

    node& operator[](int i) { return sa[i]; }
};