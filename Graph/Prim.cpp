struct edge {
  int v, w;

  bool operator < (const edge &x) const {
    return w > x.w;
  }
};

int n, m; cin >> n >> m;
vector<edge> ady[n];
forn (i, m) {
  int v, u, w; cin >> v >> u >> w;
  v--, u--;
  ady[v].pb({u, w});
  ady[u].pb({v, w});
}

priority_queue<edge> pq;
bool vis[n];
memset(vis, false, sizeof vis);

vis[0] = true;
for (edge &i : ady[0]) if (!vis[i.v]) pq.push(i);

int mst = 0;
while (sz(pq)) {
  edge v = pq.top();
  pq.pop();

  if (!vis[v.v]) {
    mst += v.w;
    vis[v.v] = true;
    for (edge &i : ady[v.v]) {
      if (!vis[i.v]) {
        pq.push(i);
      }
    }
  }
}
