struct BiConn {
  int n, timer;
  vector<bool> vis;
  vector<int> tin, low;
  stack<ii> stk;
  vector<vector<ii>> bcc;

  BiConn(int m) : 
    n(m), timer(0), vis(n), tin(n, -1),
    low(n, -1) {
    forn(i, n) if (!vis[i]) dfs(i);
  }

  void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for (int &u : g[v]) {
      if(u == p) continue;
      if(vis[u]) {
        low[v] = min(low[v], tin[u]);
        if(tin[u] < tin[v]) stk.push({v, u});
      } else {
        stk.push({v, u});
        dfs(u, v);
        low[v] = min(low[v], low[u]);
        if(low[u] >= tin[v]) {
          vector<ii> comp;
          ii edge;
          do {
            edge = stk.top(); stk.pop();
            comp.pb(edge);
          } while(edge != make_pair(v, u));
          bcc.pb(comp);
        }
      }
    }
  }
};