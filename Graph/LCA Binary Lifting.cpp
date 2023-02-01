struct LCA {
  int timer, l, n;
  vector<int> tin, tout;
  vector<vector<int>> up;
  
  LCA(int n, int root = 0) {
    timer = 0;
    this->n = n;
    tin.resize(n);
    tout.resize(n);
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
  }
  
  void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    forn (i, l) up[v][i + 1] = up[up[v][i]][i];
    for (int &u : g[v]) if (u != p) dfs(u, v);
    tout[v] = ++timer;
  }
  
  bool is_ancestor(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
  }
  
  int lca(int v, int u) {
    if (is_ancestor(v, u)) return v;
    if (is_ancestor(u, v)) return u;
    rforn (i, l)
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    return up[u][0];
  }
};