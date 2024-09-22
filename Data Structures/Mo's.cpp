void add(int x) {}
void del(int x) {}
int get_ans() {}

vector<int> mo(const vector<ii> &q) {
  int l = 0, r = -1, blk = 350; // sqrt(n)
  vector<int> inx(sz(q)), ans(sz(q));
  auto K = [&](const ii &x) -> ii {
    return ii(x.ff / blk, x.ss ^ -(x.ff / blk & 1));
  };
  iota(all(inx), 0);
  sort(all(inx), [&](int a, int b) -> bool {
    return K(q[a]) < K(q[b]);
  });
  for (int nxt : inx) {
    ii it = q[nxt];
    while (r < it.ss) add(++r);
    while (l > it.ff) add(--l);
    while (r > it.ss) del(r--);
    while (l < it.ff) del(l++);
    ans[nxt] = get_ans();
  }
  return ans;
}