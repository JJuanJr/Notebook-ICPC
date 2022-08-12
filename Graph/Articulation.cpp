int n, m; cin >> n >> m;
vector<int> ady[n];
while (m--) {
  int a, b; cin >> a >> b;
  a--, b--;
  ady[a].pb(b);
  ady[b].pb(a);
}

int t = 0;
vector<int> tin(n, -1), low(n);
function<void(int, int)> dfs = [&](int u,  int p) {
  tin[u] = low[u] = t++;
  int children = 0;
  for (int &v : ady[u]) {
    if (p == v) continue;
    if (tin[v] == -1) {
      children++;
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (tin[u] <= low[v] && p != -1) {
        cout << "Articulation " << u + 1 << endl;
      }
    } else {
      low[u] = min(low[u], low[v]);
    }
  }
  if (p == -1 && children > 1) {
    cout << "Articulation " << u + 1 << endl;
  }
};

forn (i, n) if (tin[i] == -1) dfs(i, -1);
