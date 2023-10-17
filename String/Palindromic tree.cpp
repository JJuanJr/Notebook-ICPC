// Permite calcular la cantidad de diferentes palindromos de S online
// sz(ns) - 2 = numero de substrings palindromos diferentes 
struct palindromic_tree{
    static const int SIGMA=26; static const char L = 'a';
    struct Node{
        int len, link, to[SIGMA];
        ll cnt;
        Node(int len, int link=0, ll cnt=1):len(len),link(link),cnt(cnt){
            memset(to,0,sizeof(to));
        }
    };
    vector<Node> ns;
    int last, longString;
    palindromic_tree():last(0){ns.pb(Node(-1));ns.pb(Node(0));}
    void add(int i, string &s){
        int p=last, c=s[i]-L;
        while(s[i-ns[p].len-1]!=s[i])p=ns[p].link;
        if(ns[p].to[c]){
            last=ns[p].to[c];
            ns[last].cnt++;
        }else{
            int q=ns[p].link;
            while(s[i-ns[q].len-1]!=s[i])q=ns[q].link;
            q=max(1,ns[q].to[c]);
            last=ns[p].to[c]=sz(ns);
            ns.pb(Node(ns[p].len+2,q,1));
            longString = max(longString, ns[p].len+2);
        }
    }
    void countOcurrences(){
      for(int i = sz(ns) - 1 ; i >= 2 ; --i)
        if(ns[i].link >= 2) ns[ns[i].link].cnt += ns[i].cnt;
      for(int i  = 2 ; i < sz(ns) ; ++i)
        if(ns[i].link >= 2)  ns[i].cnt += ns[ns[i].link].cnt;
    }
    //numero comun subcadenas palindromas de S and T
    //Construir tree con S y consultar con T.
    ll query(string &t){ //Llamar antes countOcurrences
      int u  = 0; ll ans = 0;
      for(int i = 0 ; i < sz(t) ; ++i){
        while((t[i - ns[u].len - 1] != t[i] || !ns[u].to[t[i]-L]) && u)
          u = ns[u].link;
        u = ns[u].to[t[i]-L];
        if(u) ans += ns[u].cnt;
      }
      return ans;
    }
};