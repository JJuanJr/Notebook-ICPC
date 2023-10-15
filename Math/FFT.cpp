typedef complex<double> base;
const double PI = acos(-1);

struct FFT {
	vector<int> rev;
	FFT(){ }
 
	void calc_rev(int n, int log_n){
		forn(i, n) {
			rev.pb(0);
			forn(j, log_n)
				if(i & (1<<j))
					rev[i] |= 1<<(log_n-1-j);
		}
	}
 
	void computeFFT(vector<base> &a, bool invert) {
		int n = (int) a.size();
 
		forn(i, n)
			if (i < rev[i])
				swap (a[i], a[rev[i]]);
 
		for(int len=2; len<=n; len<<=1) {
			double ang = 2*PI/len * (invert ? -1 : 1);
			base wlen (cos(ang), sin(ang));
			for (int i=0; i<n; i+=len) {
				base w(1);
				for (int j=0; j<len/2; ++j) {
					base u = a[i+j],  v = a[i+j+len/2] * w;
					a[i+j] = u + v;
					a[i+j+len/2] = u - v;
					w *= wlen;
				}
			}
		}
		if(invert)
			forn(i, n)
				a[i] /= n;
	}
	
	vector<int> multiply(vector<int> &a, vector<int> &b) {
		int n;  for(n = 1; n < sz(a) + sz(b); n <<= 1);
		calc_rev(n, round(log2(n)));

		vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
		fa.resize(n);  fb.resize(n);
 
		computeFFT(fa, false),  computeFFT(fb, false);
		forn(i, n) fa[i] *= fb[i];
		computeFFT(fa, true);
 
		vector<int> res(n);
		forn(i, n) res[i] = int(fa[i].real() + 0.5);
 
		//Carries for integer multiplication
		/*int carry = 0;
		forn(i, n) {
			res[i] += carry;
			carry = res[i] / 10;
			res[i] %= 10;
		}*/
		return res;
	}
};