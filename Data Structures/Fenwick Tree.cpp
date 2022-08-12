template<typename T>
struct BIT {
  vector<T> ft;

  BIT(int n): ft(n + 1) {}

  BIT(const vector<T> &a): ft(sz(a) + 1) {
    forn (i, sz(a)) { upd(i + 1, a[i]); }
  }

  T qry(int i) {
    T ans = 0;
    for (; i; i -= i & -i) ans += ft[i];
    return ans;
  }

  T qry(int l, int r) {
    return qry(r) - qry(l - 1);
  }

  void upd(int i, T v) {
    for (; i < sz(ft); i += i & -i) ft[i] += v;
  }
};
