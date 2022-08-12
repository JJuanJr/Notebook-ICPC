const int MAX = 1e5 + 5;
const int K = 17; //log2(MAX) + 1
int st[MAX][K];
int arr[MAX];
int n;

void build() {
  forn (i, n) st[i][0] = arr[i];
  forn (j, K - 1) {
    form (i, 0, i + (1 << (j + 1)), 1) {
      st[i][j + 1] = min(st[i][j], st[i + (1 << j)][j]);
    }
  }
}

int rmq(int l, int r) {
  int j = 31 - __builtin_clz(r - l + 1);
  return min(st[l][j], st[r - (1 << j) + 1][j]);
}
