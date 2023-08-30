template<typename T>
struct STree {
	int n, m;
	T neutro = T(0);
	vector<vector<T>> st;

	STree(vector<vector<T>> &a) {
    n = sz(a);
    m = sz(a[0]);
		st = vector<vector<T>>(2 * n, vector<T>(2 * m, neutro));
		build(a);
	}

	inline T oper(T a, T b) { return a + b; }

	void build(vector<vector<T>> &a) {
    forn (i, n) forn (j, m)
		  st[i + n][j + m] = a[i][j];

    forn (i, n) rform (j, m - 1, 1, 1)    
		  st[i + n][j] = oper(st[i + n][j << 1], st[i + n][j << 1 | 1]);

    rform (i, n - 1, 1, 1) forn (j, 2 * m)
      st[i][j] = oper(st[i << 1][j], st[i << 1 | 1][j]);
	}

	T qry(int x1, int y1, int x2, int y2) { // [x1, y1] (x2, y2)
		T ans = neutro;
		for(int i0 = x1 + n, i1 = x2 + n; i0 < i1; i0 >>= 1, i1 >>= 1) {
      int t[4], q = 0;
      if (i0 & 1) t[q++] = i0++;
      if (i1 & 1) t[q++] = --i1;
      forn (k, q)
        for (int j0 = y1 + m, j1 = y2 + m; j0 < j1; j0 >>= 1, j1 >>= 1) {
          if(j0 & 1) ans = oper(ans,st[t[k]][j0++]);
          if(j1 & 1) ans = oper(ans,st[t[k]][--j1]);
      }
    }
		return ans;
	}

	void upd(int l, int r, T val) {
		st[l + n][r + m] = val;
		for (int j = r + m; j > 1; j >>= 1)
			st[l + n][j >> 1] = oper(st[l + n][j], st[l + n][j ^ 1]);

		for (int i = l + n; i > 1; i >>= 1)
			for (int j = r + m; j; j >>= 1)
				st[i >> 1][j] = oper(st[i][j], st[i ^ 1][j]);
	}
};