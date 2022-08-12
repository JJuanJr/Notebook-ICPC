int n, m; cin >> n >> m;
vector<int> ady[n];
vector<int> grado(n);
forn (i, m) {
    int v, u; cin >> v >> u;
    v--, u--;
    ady[v].pb(u);
    grado[u]++;
}

vector<int> topo;
queue<int> qu;

forn (i, n) if (!grado[i]) qu.push(i);

while (sz(qu)) {
  int v = qu.front();
  qu.pop();
  topo.pb(v);
  for (int &u : ady[v]) {
    if (--grado[u] == 0) {
      qu.push(u);
    }
  }
}
