int n, m; cin >> n >> m;
vector<int> ady[n];
forn (i, m) {
  int v, u; cin >> v >> u;
  v--, u--;
  ady[v].pb(u);
}

vector<int> topo;
vector<bool> vis(n);

function<void(int)> dfs = [&](int v) {
  vis[v] = true;
  for (int &u : ady[v]) {
    if (!vis[u]) dfs(u);
  }
  topo.pb(v);
};

forn (i, n) if (!vis[i]) dfs(i);
