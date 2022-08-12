struct SegmentTree {
  vector<int> st;
  int n;

  SegmentTree(const vector<int> &arr) {
    n = sz(arr);
    st.assign(n << 2, 0);
    build(arr, 1, 0, n - 1);
  }

  int left(int v) { return v << 1; }

  int right(int v) { return (v << 1) | 1; }

  int operation(int a, int b) {
    return a + b;
  }

  void build(const vector<int> &arr, int v, int tl, int tr) {
    if (tl == tr) {
      st[v] = arr[tl];
    } else {
      int tm = (tl + tr) >> 1;
      build(arr, left(v), tl, tm);
      build(arr, right(v), tm + 1, tr);
      st[v] = operation(st[left(v)], st[right(v)]);
    }
  }

  void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
      st[v] = new_val;
    } else {
      int tm = (tl + tr) >> 1;
      if (pos <= tm) update(left(v), tl, tm, pos, new_val);
      else update(right(v), tm + 1, tr, pos, new_val);
      st[v] = operation(st[left(v)], st[right(v)]);
    }
  }

  void update(int pos, int new_val) {
    update(1, 0, n - 1, pos, new_val);
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0; // Nuetro
    if (l == tl && r == tr) return st[v];
    int tm = (tl + tr) >> 1;
    return operation(query(left(v), tl, tm, l, min(r, tm)), query(right(v), tm + 1, tr, max(l, tm + 1), r));
  }

  int query(int l, int r) {
    return query(1, 0, n - 1, l, r);
  }
};
