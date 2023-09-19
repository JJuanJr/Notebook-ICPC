template<typename T> 
struct Hungarian { // O(V^3)
  int n, m;
  const T inf = 1e18;
  vector<T> u, v; vector<int> p, way;
  vector<vector<T>> g;
  
  Hungarian(int n, int m):
    n(n), m(m), g(n + 1, vector<T>(m+1, inf - 1)),
    u(n + 1), v(m + 1), p(m + 1), way(m + 1) {}

  void set(int u, int v, T w) { g[u + 1][v + 1] = w; }
  
  T assign() {
    forab (i, 1, n + 1) {
      int j0 = 0; p[0] = i;
      vector<T> minv(m + 1, inf);
      vector<char> used(m + 1, false);
      do {
        used[j0] = true;
        int i0 = p[j0], j1; T delta = inf;
        forab (j, 1, m + 1) if (!used[j]) {
          T cur = g[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
        forn (j, m + 1)
          if (used[j]) u[p[j]] += delta, v[j] -= delta;
          else minv[j] -= delta;
        j0 = j1;
      } while (p[j0]);
      do {
        int j1 = way[j0]; p[j0] = p[j1]; j0 = j1;
      } while (j0);
    }
    return -v[0];
  }
};