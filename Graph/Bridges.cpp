int n, m;
vector<vector<int>> ady;
vector<int> tin, low;
vector<ii> bridges;
int timer;

void dfs(int v, int p = -1) {
  tin[v] = low[v] = timer++;
  for (int &u : ady[v]) {
    if (p == u) continue;
    if (tin[u] != -1) {
      low[v] = min(low[v], low[u]);
    } else {
      dfs(u, v);
      low[v] = min(low[v], low[u]);
      if (low[u] > tin[v]) {
        bridges.emplace_back(v, u);
      }
    }
  }
}


cin >> n >> m;
ady.resize(n);
while (m--) {
  int v, u; cin >> v >> u;
  ady[v].pb(u);
  ady[u].pb(v);
}

timer = 0;
tin.assign(n, -1);
low.assign(n, -1);

forn (i, n) if (tin[i] == -1) dfs(i);    
