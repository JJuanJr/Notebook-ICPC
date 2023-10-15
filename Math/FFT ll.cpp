typedef long double ld;
const ld PI = acos((ld)-1);
 
namespace FFT {
	struct com {
		ld x, y;
 
		com(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}
 
		inline com operator + (const com &c) const {
			return com(x + c.x, y + c.y);
		}
		inline com operator - (const com &c) const {
			return com(x - c.x, y - c.y);
		}
		inline com operator * (const com &c) const {
			return com(x * c.x - y * c.y, x * c.y + y * c.x);
		}
		inline com conj() const {
			return com(x, -y);
		}
	};
 
	const static int maxk = 19, maxn = (1 << maxk) + 1;
	com ws[maxn];
	int dp[maxn];
	com rs[maxn];
	int n, k;
	int lastk = -1;
 
	void fft(com *a, bool torev = 0) {
		if (lastk != k) {
			lastk = k;
			dp[0] = 0;
 
			for (int i = 1, g = -1; i < n; ++i) {
				if (!(i & (i - 1))) {
					++g;
				}
				dp[i] = dp[i ^ (1 << g)] ^ (1 << (k - 1 - g));
			}
 
			ws[1] = com(1, 0);
			forn(two, k - 1) {
				ld alf = PI / n * (1 << (k - 1 - two));
				com cur = com(cos(alf), sin(alf));
 
				int p2 = (1 << two), p3 = p2 * 2;
				forab(j, p2, p3) {
					ws[j * 2 + 1] = (ws[j * 2] = ws[j]) * cur;
				}
			}
		}
		forn(i, n) {
			if (i < dp[i]) {
				swap(a[i], a[dp[i]]);
			}
		}
		if (torev) {
			forn(i, n) {
				a[i].y = -a[i].y;
			}
		}
		for (int len = 1; len < n; len <<= 1) {
			for (int i = 0; i < n; i += len) {
				int wit = len;
				for (int it = 0, j = i + len; it < len; ++it, ++i, ++j) {
					com tmp = a[j] * ws[wit++];
					a[j] = a[i] - tmp;
					a[i] = a[i] + tmp;
				}
			}
		}
	}

	com a[maxn];
	vector<ll> multiply(vector<ll> &_a, vector<ll> &_b) {
		int na = sz(_a), nb = sz(_b);
		
		for (k = 0, n = 1; n < na + nb - 1; n <<= 1, ++k);
		forn(i, n) {
			a[i] = com(i < na ? _a[i] : 0, i < nb ? _b[i] : 0);
		}
		fft(a);
		a[n] = a[0];
		forne(i, n - i) {
			a[i] = (a[i] * a[i] - (a[n - i] * a[n - i]).conj()) * com(0, (ld)-1 / n / 4);
			a[n - i] = a[i].conj();
		}
		fft(a, 1);
		int res = 0;

		vector<ll> ans(n);
		forn(i, n) {
			ll val = (ll) round(a[i].x);
			ans[i] = val;//only for multiply poly

			/*if (val) {//only for multiply long integers
				while (res < i) {
					ans[res++] = 0;
				}
				ans[res++] = val;
			}*/
		}
		return ans;
	}
};