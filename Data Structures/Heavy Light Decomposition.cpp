struct HLD {
  int n, timer;
  vector<int> in, out, nxt, tam;
  
  HLD(int v, int n) {
    this->n = n;
    timer = 0;
    in.resize(n);
    out.resize(n);
    nxt.resize(n);
    tam.resize(n);
    dfs_sz(v);
    nxt[v] = v;
    dfs_hld(v);
  }
  
  void dfs_sz(int v) {
    tam[v] = 1;
    for (auto &u : g[v]) {
      dfs_sz(u);
      tam[v] += tam[u];
      if (tam[u] > tam[g[v][0]])
        swap(u, g[v][0]);
    }
  }
  
  void dfs_hld(int v) {
    in[v] = timer++;
    for (auto &u : g[v]) {
      nxt[u] = u == g[v][0] ? nxt[v] : u;
      dfs_hld(u);
    }
    out[v] = timer;
  }
};