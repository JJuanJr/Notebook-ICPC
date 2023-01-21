struct Tarjan {
  vector<int> low, num, comp;
  stack<int> st;
  int n, scc, cont;
  const int INF = int(1e9);
  
  Tarjan(int n) {
    this->n = n;
    low.resize(n);
    num.assign(n, -1);
    comp.resize(n);
    scc = cont = 0;
  }
  
  void dfs(int v) {
    low[v] = num[v] = cont++;
    st.push(v);
    for (int &u : g[v]) {
      if (num[u] == -1) dfs(u);
      low[v] = min(low[v], low[u]);
    }
    if (low[v] == num[v]) {
      int u;
      do {
        u = st.top(); st.pop();
        low[u] = INF;
        comp[u] = scc;
      } while (u != v);
      scc++;
    }
  };
  
  void go() {
    forn (i, n)
      if (num[i] == -1) dfs(i);
  }
};