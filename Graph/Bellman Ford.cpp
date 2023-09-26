struct Edge { int v, u; ll w; };

const ll INF = 1e18;
vector<Edge> edges;
vector<ll> d;
vector<int> p;

vector<int> BellmanFord(int n, int src = -1) {
  d.assign(n, ~src ? INF : 0);
  if (~src) d[src] = 0;
  p.assign(n, -1);
  int x = -1;
  forn (i, n) {
    x = -1;
    for (Edge &e : edges)
      if (d[e.v] < INF)
        if (d[e.u] > d[e.v] + e.w) {
          d[e.u] = max(-INF, d[e.v] + e.w);
          p[e.u] = e.v;
          x = e.u;
        }
  }
  if (x == -1) return {};
  forn (i, n) x = p[x];
  vector<int> path;
  for (int cur = x;; cur = p[cur]) {
    path.pb(cur);
    if (cur == x && sz(path) > 1)
      break;
  }
  reverse(all(path));
  return path;
}

vector<int> BellmanFord(int n, int s, int t) {
  d.assign(n, INF);
  d[s] = 0;
  p.assign(n, -1);
  while (1) {
    bool any = false;
    for (Edge &e : edges)
      if (d[e.v] < INF)
        if (d[e.u] > d[e.v] + e.w) {
          d[e.u] = d[e.v] + e.w;
          p[e.u] = e.v;
          any = true;
        }
    if (!any) break;
  }
  if (d[t] == INF) return {};
  vector<int> path;
  for (int cur = t; cur != -1; cur = p[cur])
    path.pb(cur);
  reverse(all(path));
  return path;
}