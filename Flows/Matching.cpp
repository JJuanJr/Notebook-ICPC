struct mbm { // O(V * E)
  int l, r;
  vector<int> mat;
  vector<bool> vis;
  vector<vector<int>> g;

  mbm(int l, int r) : l(l), r(r), mat(r), vis(l), g(l) {}

  bool match(int v) {
    if (vis[v]) return false;
    vis[v] = true;
    for (int &u : g[v]) {
      if (mat[u] == -1 || match(mat[u])) {
        mat[u] = v;
        return true;
      }
    }
    return false;
  }

  vector<ii> matching() {
    vector<ii> ans;
    fill(all(mat), -1);
    forn (i, l) {
      fill(all(vis), false);
      match(i);
    }
    forn (i, r) if (~mat[i]) ans.pb({mat[i], i});
    return ans;
  }
};