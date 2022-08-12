int n; cin >> n;
int ady[n][n];
const int INF = int(1e9);

forn (i, n) {
  forn (j, n) {
    ady[i][j] = (i == j ? 0 : INF);
  }
}

forn (i, n) {
  int v, u, w; cin >> v >> u >> w;
  v--, u--;
  ady[v][u] = ady[u][v] = w;
}

forn (k, n) {
  forn (i, n) {
    forn (j, n) {
      ady[i][j] = min(ady[i][j], ady[i][k] + ady[k][j]);
    }
  }
}
