int n, m; cin >> n >> m;

vector<int> ady[n], rady[n];
vector<int> grado(n);

forn (i, m) {
    int a, b; cin >> a >> b;
    a--, b--;
    ady[a].pb(b);
    rady[b].pb(a);
}

vector<int> order;
vector<bool> vis(n);
vector<vector<int>> comp;

function<void(int)> dfs1 = [&](int v) {
  vis[v] = true;
  for (int &u : ady[v]) {
    if (!vis[u]) {
      dfs1(u);
    }
  }
  order.pb(v);
};

forn (i, n) (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i);

vis.assign(n, false);

function<void(int)> dfs2 = [&](int v) {
  vis[v] = true;
  comp.back().pb(v);
  for (int &u : rady[v]) {
    if (!vis[u]) {
      dfs2(u);
    }
  }
};

rforn (i, n - 1) {
  if (!vis[order[i]]) {
    comp.pb({});
    dfs2(order[i]);
  }
}

forn (i, sz(comp)) {
  cout << "Component #" << i + 1 << ":";
  for (int &j : comp[i]) {
    cout << " " << j + 1;
  }
  cout << endl;
}
