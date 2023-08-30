//zx^n+...+cx^2+bx+a
typedef int tp; // type of polynomial
template<class T=tp>
struct poly {  // poly<> : 1 variable, poly<poly<>>: 2 variables, etc.
	vector<T> c;
	T& operator[](int k){return c[k];}
	poly(vector<T>& c):c(c){}
	poly(initializer_list<T> c):c(c){}
	poly(int k):c(k){}
	poly(){}
	poly operator+(poly<T> o){
		int m=c.size(),n=o.c.size();
		poly res(max(m,n));
		forn(i,m)res[i]=res[i]+c[i];
		forn(i,n)res[i]=res[i]+o.c[i];
		return res;
	}
	poly operator*(tp k){
		poly res(c.size());
		forn(i,c.size())res[i]=c[i]*k;
		return res;
	}
	poly operator*(poly o){
		int m=c.size(),n=o.c.size();
		poly res(m+n-1);
		forn(i,m)forn(j,n)res[i+j]=res[i+j]+c[i]*o.c[j];
		return res;
	}
	poly operator-(poly<T> o){return *this+(o*-1);}
	T operator()(tp v){
		T sum(0);
		for(int i=c.size()-1;i>=0;--i)sum=sum*v+c[i];
		return sum;
	}
};
// example: p(x,y)=2*x^2+3*x*y-y+4
// poly<poly<>> p={{4,-1},{0,3},{2}}
// printf("%d\n",p(2)(3)) // 27 (p(2,3))
set<tp> roots(poly<> p){ // only for integer polynomials
	set<tp> r;
	while(!p.c.empty()&&!p.c.back())p.c.pop_back();
	if(!p(0))r.insert(0);
	if(p.c.empty())return r;
	tp a0=0,an=abs(p[p.c.size()-1]);
	for(int k=0;!a0;a0=abs(p[k++]));
	vector<tp> ps,qs;
	forab(i,1,sqrt(a0)+1)if(a0%i==0)ps.pb(i),ps.pb(a0/i);
	forab(i,1,sqrt(an)+1)if(an%i==0)qs.pb(i),qs.pb(an/i);
	for(auto pt:ps)for(auto qt:qs)if(pt%qt==0){
		tp x=pt/qt;
		if(!p(x))r.insert(x);
		if(!p(-x))r.insert(-x);
	}
	return r;
}
pair<poly<>,tp> ruffini(poly<> p, tp r){ // returns pair (result,rem)
	int n=p.c.size()-1;
	vector<tp> b(n);
	b[n-1]=p[n];
	for(int k=n-2;k>=0;--k)b[k]=p[k+1]+r*b[k+1];
	return {poly<>(b),p[0]+r*b[0]};
}
// only for double polynomials
pair<poly<>,poly<> > polydiv(poly<> p, poly<> q){ // returns pair (result,rem)
	int n=p.c.size()-q.c.size()+1;
	vector<tp> b(n);
	for(int k=n-1;k>=0;--k){
		b[k]=p.c.back()/q.c.back();
		forn(i,q.c.size())p[i+k]-=b[k]*q[i];
		p.c.pop_back();
	}
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	return {poly<>(b),p};
}
// only for double polynomials
poly<> interpolate(vector<tp> x, vector<tp> y){ //TODO TEST
	poly<> q={1},S={0};
	for(tp a:x)q=poly<>({-a,1})*q;
	forn(i,x.size()){
		poly<> Li=ruffini(q,x[i]).ff;
		Li=Li*(1.0/Li(x[i])); // change for int polynomials
		S=S+Li*y[i];
	}
	return S;
}
vector<ll> coef(vector<ll> roots, bool first = true){
    int l = roots.size() + 1;
    vector<ll> c(10002, 0), m(10002, 0);
	c[0] = 1;
	forn(k, roots.size()) {
		forab(i, 1, l) m[i] = c[i] + c[i-1]*roots[k];
		forab(i, 1, l) c[i] = m[i];
	}
	ll sign = first? 1 : -1;
	forn(i, roots.size()) {
        sign *= -1LL;
        m[i + 1] *= sign;
    }
	return m;
}
