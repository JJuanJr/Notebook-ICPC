struct Bridges {
  int n, timer;
  vector<bool> vis;
  vector<int> tin, low;
  vector<ii> bridges;

  Bridges(int m) {
    n = m;
    timer = 0;
    vis.resize(n);
    tin.assign(n, -1);
    low.assign(n, -1);
    forn(i, n)
      if (!vis[i]) dfs(i);
  }

  void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for (int &u : g[v]) {
      if (u == p) continue;
      if (vis[u]) {
        low[v] = min(low[v], tin[u]);
      } else {
        dfs(u, v);
        low[v] = min(low[v], low[u]);
        if (low[u] > tin[v])
          is_bridge(v, u);
      }
    }
  }

  void is_bridge(int v, int u) {
    bridges.pb(ii(v, u));
  }
};