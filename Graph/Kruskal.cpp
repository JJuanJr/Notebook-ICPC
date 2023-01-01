struct edge {
  int v, u, w;

  bool operator < (const edge &x) const {
    return w < x.w;
  }
};

vector<edge> edges;
int n, m; cin >> n >> m;
forn (i, m) {
  int v, u, w; cin >> v >> u >> w;
  v--, u--;
  edges.push_back({v, u, w});
}
sort(all(edges));
dsu UF(n);
int nodes = 0, mst = 0;
for (edge &i : edges) {
  if (!UF.same(i.v, i.u)) {
    mst += i.w;
    UF.unite(i.v, i.u);
    nodes++;
  }
  if (nodes == n - 1) break;
}
