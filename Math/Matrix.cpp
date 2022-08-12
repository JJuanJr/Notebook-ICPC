struct matrix {
  int n, m;
  vector<vector<int>> v;

  matrix(int n, int m, bool ones = false) : n(n), m(m), v(n, vector<int>(m)) {
    if (ones) forn (i, n) v[i][i] = 1;
  }

  matrix operator * (const matrix &o) {
    matrix ans(n, o.m);
    forn (i, n)
      forn (k, m) if (v[i][k])
        forn (j, o.m)
          ans[i][j] = (1ll * v[i][k] * o.v[k][j] + ans[i][j]) % MOD;
    return ans;
  }

  vector<int> & operator [] (int i) {
    return v[i];
  }
};

matrix binpow(matrix b, ll e) {
  matrix ans(b.n, b.m, true);
  while (e) {
    if (e & 1) ans = ans * b;
    b = b * b;
    e >>= 1;
  }
  return ans;
}