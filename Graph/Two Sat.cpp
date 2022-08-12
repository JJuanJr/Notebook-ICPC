struct two_sat {
  int n, cont, scc;
  vector<vector<int>> ady;
  vector<int> low, num, comp, val;
  stack<int> st;
  const int INF = int(1e9);

  two_sat(int n): n(n), cont(0), scc(0), ady(n << 1), low(n << 1), num(n << 1, -1), comp(n << 1), val(n) {}

  void add_edge(int v, int u) {
    ady[get_inx(-v)].pb(get_inx(u));
    ady[get_inx(-u)].pb(get_inx(v));
  }

  int get_inx(int v) {
    return ((abs(v) - 1) << 1) | (v < 0);
  }

  void tarjan(int v) {
    low[v] = num[v] = cont++;
    st.push(v);
    for (int &u : ady[v]) {
      if (num[u] == -1) tarjan(u);
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
  }

  bool check() {
    for (int i = 0; i < (n << 1); ++i) {
      if (num[i] == -1) {
        tarjan(i);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (comp[i << 1] == comp[(i << 1) | 1]) return false;
      val[i] = comp[i << 1] < comp[(i << 1) | 1];
    }
    return true;
  }
};
