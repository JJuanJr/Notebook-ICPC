template<typename T>
struct STree {
  struct node {
    int lt, rt;
    T val;
  };

  int curr, n;
  vector<int> ver;
  vector<node> seg;
  const T nuetro = T(0);

  STree(vector<T> &a) {
    curr = 1;
    n = sz(a);
    ver.pb(0);
    seg.resize(n * 80); // 4N + Q * LOG
    forn (i, n) upd(0, i, a[i]);
  }

  inline T oper(T a, T b) { return a + b; }

  void upd(int &root, int idx, T val, int l, int r) {
    seg[curr].lt = seg[root].lt;
    seg[curr].rt = seg[root].rt;
    seg[curr].val = seg[root].val + val;
    root = curr++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (idx <= mid) upd(seg[root].lt, idx, val, l, mid);
    else upd(seg[root].rt, idx, val, mid + 1, r);
  }

  T qry(int root, int a, int b, int l, int r) {
    if (a <= l && r <= b) return seg[root].val;
    int mid = (l + r) >> 1;
    T L = a <= mid ? qry(seg[root].lt, a, b, l, mid) : nuetro;
    T R = mid < b ? qry(seg[root].rt, a, b, mid + 1, r) : nuetro;
    return oper(L, R);
  }

  void upd(int root, int idx, T val) { return upd(ver[root], idx, val, 0, n - 1); }
  T qry(int root, int a, int b) { return qry(ver[root], a, b, 0, n - 1); }
};