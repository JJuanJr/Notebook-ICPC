struct ArtiBridges {
  int n, timer;
  vector<bool> vis, is_articulation;
  vector<int> tin, low;
  vector<ii> bridges;

  ArtiBridges(int m) : 
    n(m), timer(0), vis(n), tin(n, -1),
    low(n, -1), is_articulation(n) {
    forn(i, n) if (!vis[i]) dfs(i);
  }

  void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for(int &u : g[v]) {
      if(u == p) continue;
      if(vis[u]) {
        low[v] = min(low[v], tin[u]);
      } else {
        dfs(u, v);
        low[v] = min(low[v], low[u]);
        if(low[u] >= tin[v] && p != -1)
          is_articulation[v] = true;
        ++children;
        
        if(low[u] > tin[v])
          bridges.pb({v, u});
      }
    }
    if(p == -1 && children > 1)
      is_articulation[v] = true;
  }
};