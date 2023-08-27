template<typename T>
struct BIT {
  int n, m;
  vector<vector<T>> ft;
  
  BIT(int n, int m): n(n), m(m), ft(n + 1, vector<T>(m + 1)) {} 
  
  void upd(int i0, int j0, T v) {
    for(int i = i0 + 1; i <= n; i += i & -i)
      for(int j = j0 + 1; j <= m; j += j & -j)
        ft[i][j] += v;
  }
  
  T get(int i0, int j0) {
    T r = 0;
    for(int i = i0; i; i -= i & -i)
      for(int j = j0; j; j -= j & -j)
        r += ft[i][j];
    return r;
  }

  T qry(int i0, int j0, int i1, int j1) { // [i0, j0] (i1, j1)
    return get(i1, j1) - get(i1, j0) - get(i0, j1) + get(i0,j0);
  }
};