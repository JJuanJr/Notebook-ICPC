Permite calcular la cantidad de diferentes palindromos de S online
sz(tree) - 2 = numero de substrings palindromos diferentes 
const int alfa = 26;
const char L = 'a';

struct node {
  int next[alfa], link, len;
  ll cnt;
  node(int x, int l = 0, ll c = 1): len(x), link(l), cnt(c){
    memset(next, 0, sizeof next);
  }
  int& operator[](int i) { return next[i]; }
};

struct palindromic_tree {
  vector<node> tree;
  string s;
  int n, last;
  palindromic_tree(string t = ""){
    n = last = 0;
    tree.pb(node(-1));
    tree.pb(node(0));
    for(auto &c: t)add_char(c);
  }

  int getlink(int p){
    while(s[n - tree[p].len - 1] != s[n])p = tree[p].link;
    return p;
  }

  void add_char(char ch){
    s.pb(ch);
    int p = getlink(last), c = ch - L;
    if(!tree[p][c]){
      int link = getlink(tree[p].link);
      link = max(1, tree[link][c]);
      tree[p][c] = sz(tree);
      tree.pb(node(tree[p].len + 2,link, 0));
    }
    last = tree[p][c];
    tree[last].cnt++;
    n++;
  }

  void countOcurrences(){
    for(int i = sz(tree) - 1; i >= 2 ; --i)
      if(tree[i].link >= 2) tree[tree[i].link].cnt += tree[i].cnt;
    for(int i = 2; i < sz(tree) ; ++i)
      if(tree[i].link >= 2) tree[i].cnt += tree[tree[i].link].cnt;
  }
  //numero comun subcadenas palindromas de S and T
  //Construir tree con S y consultar con T.
  ll query(string &t){//Llamar antes countOcurrences
    int u = 0; ll ans = 0;
    for(int i = 0; i < sz(t) ; ++i){
      while((t[i-tree[u].len-1] != t[i] || !tree[u][t[i]-L]) && u)
        u = tree[u].link;
      u = tree[u][t[i]-L];
      if(u) ans += tree[u].cnt;
    }
    return ans;
  }
  node& operator[](int i) { return tree[i]; }
};
