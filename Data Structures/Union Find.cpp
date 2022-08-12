struct dsu {
  vector<int> pad, tam;
  int size;

  dsu(int n): pad(n), tam(n, 1), size(n) {
    iota(all(pad), 0);
  }

  void make() {
    pad.pb(sz(pad));
    tam.pb(1);
    size++;
  }

  int find(int v) {
    if (v == pad[v]) return v;
    return pad[v] = find(pad[v]);
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      if (tam[a] < tam[b]) swap(a, b);
      pad[b] = a;
      tam[a] += tam[b];
      size--;
    }
  }

  int same(int a, int b) {
    return find(a) == find(b);
  }

  int count(int v) {
    return tam[find(v)];
  }
};