struct edge {
  int v, u, w;
};

const int INF = int(1e6);
int n, m;
vector<edge> edges;

vector<int> bellman(int v) {
  vector<int> dist(n, INF);
  dist[v] = 0;
  forn (i, n - 1) {
    for (edge &j : edges) {
      if (dist[j.v] < INF) {
        dist[j.u] = min(dist[j.u], dist[j.v] + j.w);
      }
    }
  }
  return dist;
}

cin >> n >> m;

forn (i, m {
  int v, u, w; cin >> v >> u >> w;
  v--, u--;
  edges.pb({v, u, w});
}

vector<int> dist = bellman(0);
