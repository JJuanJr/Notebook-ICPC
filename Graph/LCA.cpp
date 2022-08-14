struct LCA {
  vector<int> height, euler, first, segtree;
  int n;

  LCA(vector<vector<int>> &g, int root = 0) {
    n = sz(g);
    height.resize(n);
    first.resize(n);
    dfs(g, root, root);
    int m = sz(euler);
    segtree.resize(m * 4);
    build(1, 0, m - 1);
  }

  void dfs(vector<vector<int>> &g, int v, int p, int h = 0) {
    height[v] = h;
    first[v] = sz(euler);
    euler.pb(v);
    for (int &u : g[v]) {
      if (u == p) continue;
      dfs(g, u, v, h + 1);
      euler.pb(v);
    }
  }

  void build(int node, int b, int e) {
    if (b == e) {
      segtree[node] = euler[b];
    } else {
      int mid = (b + e) / 2;
      build(node << 1, b, mid);
      build(node << 1 | 1, mid + 1, e);
      int l = segtree[node << 1], r = segtree[node << 1 | 1];
      segtree[node] = (height[l] < height[r]) ? l : r;
    }
  }

  int query(int node, int b, int e, int L, int R) {
    if (b > R || e < L) return -1;
    if (b >= L && e <= R) return segtree[node];
    int mid = (b + e) >> 1;
    int left = query(node << 1, b, mid, L, R);
    int right = query(node << 1 | 1, mid + 1, e, L, R);
    if (left == -1) return right;
    if (right == -1) return left;
    return height[left] < height[right] ? left : right;
  }

  int lca(int u, int v) {
    int left = first[u], right = first[v];
    if (left > right) swap(left, right);
    return query(1, 0, sz(euler) - 1, left, right);
  }
};
