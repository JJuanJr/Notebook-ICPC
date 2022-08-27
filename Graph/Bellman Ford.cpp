auto BellmanFord = [&](int src) -> void {
  dist.assign(n, INF);
  dist[src] = 0;
  forn (i, n - 1)
    forn (v, n) if (dist[v] != INF)
      for (ill &u : g[v]) dist[u.ff] = min(dist[u.ff], dist[v] + u.ss);
};

auto Cycle = [&]() -> vector<int> {
  vector<int> ans;
  forn (u, n) if (dist[u] != INF)
    for (ill &v : g[u]) if (dist[v.ff] > dist[u] + v.ss)
      dist[v.ff] = -INF, ans.pb(v.ff);
  return ans;
};