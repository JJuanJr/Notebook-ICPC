struct Blossom { // O(E * V^2)
  struct struct_edge { int v; struct_edge * n; };
  typedef struct_edge* edge;
  int n;
  struct_edge pool[MAXE]; // 2 * n * n;
  edge top;
  vector<edge> g;
  queue<int> q;
  vector<int> f, base, inq, inb, inp, match;
  vector<vector<int>> ed;
  
  Blossom(int n):
    n(n), match(n, -1), g(n), top(pool),
    f(n), base(n), inq(n), inb(n), inp(n),
    ed(n, vector<int>(n)) {}

  void add_edge(int u, int v) {
    if (ed[u][v]) return;
    ed[u][v] = 1;
    top->v = v, top->n = g[u], g[u] = top++;
    top->v = u, top->n = g[v], g[v] = top++;
  }

  int get_lca(int root, int u, int v) {
    fill(all(inp), 0);
    while (1) {
      inp[u = base[u]] = 1;
      if (u == root) break;
      u = f[match[u]];
    }
    while (1) {
      if (inp[v = base[v]]) return v;
      else v = f[match[v]];
    }
  }

  void mark(int lca, int u) {
    while (base[u] != lca) {
      int v = match[u];
      inb[base[u]] = 1;
      inb[base[v]] = 1;
      u = f[v];
      if (base[u] != lca) f[u] = v;
    }
  }

  void blossom_contraction(int s, int u, int v) {
    int lca = get_lca(s, u, v);
    fill(all(inb), 0);
    mark(lca, u); mark(lca, v);
    if (base[u] != lca) f[u] = v;
    if (base[v] != lca) f[v] = u;
    forn (u, n) {
      if (inb[base[u]]) {
        base[u] = lca;
        if (!inq[u]) {
          inq[u] = 1;
          q.push(u);
        }
      }
    }
  }

  int bfs(int s) {
    fill(all(inq), 0);
    fill(all(f), -1);
    forn (i, n) base[i] = i;
    q = queue<int>();
    q.push(s);
    inq[s] = 1;
    while (sz(q)) {
      int u = q.front(); q.pop();
      for (edge e = g[u]; e; e = e->n) {
        int v = e->v;
        if (base[u] != base[v] && match[u] != v) {
          if ((v == s) || (match[v] != -1 && f[match[v]] != -1))
            blossom_contraction(s, u, v);
          else if (f[v] == -1) {
            f[v] = u;
            if (match[v] == -1) return v;
            else if (!inq[match[v]]) {
              inq[match[v]] = 1;
              q.push(match[v]);
            }
          }
        }
      }
    }
    return -1;
  }

  int doit(int u) {
    if (u == -1) return 0;
    int v = f[u];
    doit(match[v]);
    match[v] = u; match[u] = v;
    return u != -1;
  }

  int matching() {
    int ans = 0;
    forn (u, n)
      ans += (match[u] == -1) && doit(bfs(u));
    return ans;
  }

  // (i < net.match[i]) => means match
  vector<ii> get_edges() {
    vector<ii> ans;
    forn (u, n) if (u < match[u])
      ans.pb({u, match[u]});
    return ans;
  }
};