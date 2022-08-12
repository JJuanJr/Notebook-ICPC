int S, n, q;

struct query {
  int l, r, idx;
  query(int l, int r, int idx): l(l), r(r), idx(idx) {}

  bool operator < (const query &x) const {
    if (l / S != x.l / S) return l / S < x.l / S;
    return (l / S & 1) ?  r < x.r: r > x.r;
  }
};

vector<query> qu;
vector<int> ans;

void add(int x) {

}

void del(int x) {

}

int get_ans() {
  return -1;
}

void mo_s() {
  S = sqrt(n);
  sort(all(qu));
  ans.resize(q);
  int l = 0, r = -1;
  for (query &it: qu) {
    while (r < it.r) add(++r);
    while (l > it.l) add(--l);
    while (r > it.r) del(r--);
    while (l < it.l) del(l++);
    ans[it.idx] = get_ans();
  }
}