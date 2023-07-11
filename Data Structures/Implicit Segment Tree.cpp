const int SZ = int(1e9);
template<typename T>
struct STree {
  STree<T>* c[2];
	T val = 0;

	STree() { c[0] = c[1] = NULL; }
  
	void upd(int ind, T v, int L = 0, int R = SZ - 1) {
    if (L == ind && R == ind) { val += v; return; }
		int M = (L + R) / 2;
		if (ind <= M) {
			if (!c[0]) c[0] = new STree();
			c[0]->upd(ind, v, L, M);
		} else {
			if (!c[1]) c[1] = new STree();
			c[1]->upd(ind, v, M + 1, R);
		}
		val = 0; forn(i, 2) if (c[i]) val += c[i]->val;
	}
  
	T query(int lo, int hi, int L = 0, int R = SZ - 1) {
		if (hi < L || R < lo) return 0;
		if (lo <= L && R <= hi) return val;
		int M = (L + R) / 2; T res = 0;
		if (c[0]) res += c[0]->query(lo, hi, L, M);
		if (c[1]) res += c[1]->query(lo, hi, M + 1, R);
		return res;
	}
};