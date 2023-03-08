struct edge {
  int v; ll w;

  bool operator < (const edge &x) const {
    return x.w < w;
  }
};

vector<ll> dist(n, LONG_LONG_MAX);

auto dijkstra = [&](edge v) {
  priority_queue<edge> pq;
  pq.push(v);
  dist[v.v] = 0;
  while (sz(pq)) {
    v = pq.top();
    pq.pop();
    if (v.w > dist[v.v]) continue;
    for (edge &u : g[v.v]) {
      if (dist[u.v] > dist[v.v] + u.w) {
        dist[u.v] = dist[v.v] + u.w;
        pq.push({u.v, dist[u.v]});
      }
    }
  }
};